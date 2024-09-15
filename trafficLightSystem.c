/*
Sender (Transmitter): Responsible for preparing, encoding, and sending packets.
Receiver: Responsible for receiving and decoding packets.
Communication Channel: Physical medium or protocol 
(e.g., UART, SPI, I2C, CAN, Ethernet, wireless) used to transmit packets.
Packet Structure: Defines the format of the packet, including headers, payload, and error-checking fields like checksums.
*/

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_MAX 1024
#define PACKET_MAX_SIZE  64
#define HEADER_SIZE      4
#define PAYLOAD_SIZE     (PACKET_MAX_SIZE - HEADER_SIZE - 2)  // 2 bytes for CRC
#define CRC_SIZE         2

typedef struct{
    uint8_t header[HEADER_SIZE];
    uint8_t payload[PAYLOAD_SIZE];
    uint16_t crc;    //error checking field
}Package;

uint8_t* ringbuffer[BUFFER_MAX];
sem_t empty_slots;   //intialize with 1024
sem_t full_slots;   //initialize with 0
pthread_mutex_t mutex;

int in = 0;
int out = 0;

//CRC correction code, calculate CRC: API function here
uint16_t calculateCRC(uint8_t *data, size_t length){}

int sendPacketWithAck(Package *packet);

void sendPacket(Package* packet){
    // prepare the packet
    uint8_t* buffer = (uint8_t*)malloc(PACKET_MAX_SIZE);
    if (!buffer) {
        return;
    }


    memcpy(buffer,packet->header,HEADER_SIZE);
    memcpy(buffer+HEADER_SIZE,packet->payload,PAYLOAD_SIZE);
    
    packet->crc = calculateCRC(buffer, HEADER_SIZE + PAYLOAD_SIZE);
    buffer[HEADER_SIZE + PAYLOAD_SIZE] = packet->crc & 0xFF;          // Lower byte of CRC
    buffer[HEADER_SIZE + PAYLOAD_SIZE + 1] = (packet->crc >> 8) & 0xFF;  // Upper byte of CRC

    //send to ring buffer
    sem_wait(&empty_slots);
    pthread_mutex_lock(&mutex);
    // should allocate space here
    ringbuffer[in] = (uint8_t*)malloc(PACKET_MAX_SIZE);
    if(!ringbuffer[in]){
        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);
        free(buffer);
        return;
    }

    memcpy(ringbuffer[in],buffer,PACKET_MAX_SIZE);
    in = (in + 1) % BUFFER_MAX;

    pthread_mutex_unlock(&mutex);
    sem_post(&full_slots);

    free(buffer);
}

void receivePacket(Package* packet){
    uint8_t* buffer = (uint8_t*)malloc(PACKET_MAX_SIZE);
    //receive 
    sem_wait(&full_slots);
    pthread_mutex_lock(&mutex);

    memcpy(buffer,ringbuffer[out],PACKET_MAX_SIZE);
    free(ringbuffer[out]);
    ringbuffer[out] = NULL;
    out = (out + 1) % BUFFER_MAX;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty_slots);

    memcpy(packet->header, buffer, HEADER_SIZE);
    memcpy(packet->payload, buffer + HEADER_SIZE, PAYLOAD_SIZE);

    uint16_t receivedCRC = buffer[HEADER_SIZE + PAYLOAD_SIZE] | (buffer[HEADER_SIZE + PAYLOAD_SIZE + 1] << 8);
    uint16_t calculatedCRC = calculateCRC(buffer, HEADER_SIZE + PAYLOAD_SIZE);

    free(buffer);
    if (calculatedCRC == receivedCRC) {
        // Packet received correctly
        return 0;  // Success
    } else {
        // CRC mismatch, packet corrupted
        return -1;  // Error
    }
}

/*
For a robust system, you should implement a timeout 
and retransmission mechanism to handle cases where the packet is lost or corrupted.
*/
/*
Sender sends a packet and waits for an acknowledgment (ACK).
If the sender doesn’t receive an ACK within a timeout, it retransmits the packet.
If the receiver detects a corrupted packet (CRC mismatch), it discards the packet and does not send an ACK.
*/

int waitForAck(){
    return 0;
}
int sendPacketWithAck(Package *packet){
    int retries = 3;
    for(int i = 0; i < retries; ++i){
        sendPacket(packet);

        int status = waitForAck();
        if(status == 1) return 0;
    }
    return -1;
}