/*
HW timer: given HW timer build an API system which can set any num of timers
This API will allow the creation and management of multiple software timers, 
each with its own expiration time and callback, using a single hardware timer.
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  // for sleep function
#include <stdbool.h>

typedef struct Timer{
    uint32_t duration_ms;
    uint32_t expired_time;
    bool is_active;
    bool is_periodic;
    void (*callback)(void);   //function to call when function expired
    struct Timer* next;     // Pointer to next pointer
}Timer;

Timer* TimerListHead = NULL;

Timer* timer_create(uint32_t duration_ms, bool is_periodic, void (*callback)(void)){
    Timer* newTimer = (Timer*)malloc(sizeof(Timer));
    if(!newTimer) return NULL;

    // initialize
    newTimer->duration_ms = duration_ms;
    newTimer->expired_time = duration_ms;
    newTimer->is_active = true;
    newTimer->is_periodic = true;
    newTimer->callback = callback;
    newTimer->next = NULL;

    timer_add_to_list(newTimer);

    return newTimer;
}

//We must initialize the hardware timer to tick at regular intervals
void hw_timer_init(uint32_t tick_interval_ms){
/*
Initialize the hardware timer with the specified tick interval
This typically involves configuring a hardware timer register
and enabling the interrupt.
*/
}


void timer_add_to_list(Timer* new_timer){
    if(!TimerListHead){
        TimerListHead = new_timer;
    }else{
         Timer* current = TimerListHead;
         while(current->next){
            current = current->next;
         }
         current->next =new_timer;
    }
}

// stop a timer
void timer_stop(Timer* timer) {
    timer->is_active = false;
}


//Delete Timer: Removes a timer from the list and frees the memory.
void timer_delete(Timer* timer){
    if (timer == NULL) return;

    Timer* current = TimerListHead;
    Timer* previous = NULL;
    
    while(current){
        if(current == timer){
            // delete the timer here
            if(previous){
                previous->next = current->next;
            }else{
                TimerListHead = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void hw_timer_interrupt_handler(void){
    Timer* current = TimerListHead;
    while(current){
        if(current->is_active){
            if(current->expired_time > 0){
                current->expired_time--;
            }
            if(current->expired_time == 0){
                if(current->is_periodic){
                    current->expired_time = current->duration_ms;
                }else{
                    current->is_active = false;
                    timer_delete(current);
                }
            }
        }
        current = current->next;
    }
}

// based on expired time
void timer_add_sorted(Timer* new_timer) {
    if (TimerListHead == NULL || TimerListHead->expired_time >= new_timer->expired_time) {
        new_timer->next = TimerListHead;
        TimerListHead = new_timer;
    } else {
        Timer* current = TimerListHead;
        while (current->next != NULL && current->next->expired_time < new_timer->expired_time) {
            current = current->next;
        }
        new_timer->next = current->next;
        current->next = new_timer;
    }
}