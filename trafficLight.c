#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  // for sleep function

#define GREEN_TIME  10  // 10 seconds for green light
#define YELLOW_TIME 3   // 3 seconds for yellow light
#define RED_TIME    10  // 10 seconds for red light

typedef enum{
    NS_GREEN_EW_RED,
    NS_YELLOW_EW_RED,
    NS_RED_EW_GREEN,
    NS_RED_EW_YELLOW
}TrafficState;

void trafficLightControl(TrafficState* currentState) {
    switch (*currentState) {
        case NS_GREEN_EW_RED:
            printf("North-South: GREEN, East-West: RED\n");
            sleep(GREEN_TIME);  // Simulate the green light duration
            *currentState = NS_YELLOW_EW_RED;
            break;

        case NS_YELLOW_EW_RED:
            printf("North-South: YELLOW, East-West: RED\n");
            sleep(YELLOW_TIME);  // Simulate the yellow light duration
            *currentState = NS_RED_EW_GREEN;
            break;

        case NS_RED_EW_GREEN:
            printf("North-South: RED, East-West: GREEN\n");
            sleep(GREEN_TIME);  // Simulate the green light duration
            *currentState = NS_RED_EW_YELLOW;
            break;

        case NS_RED_EW_YELLOW:
            printf("North-South: RED, East-West: YELLOW\n");
            sleep(YELLOW_TIME);  // Simulate the yellow light duration
            *currentState = NS_GREEN_EW_RED;
            break;
    }
}

int main(){
    TrafficState currentState = NS_GREEN_EW_RED;  // Initial state

    while (1) {
        trafficLightControl(&currentState);  // Update traffic lights based on state
    }

    return 0;
}