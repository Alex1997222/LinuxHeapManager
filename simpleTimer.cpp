#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

// Timer structure
struct Timer {
    uint32_t duration_ms;
    time_point<steady_clock> expired_time;
    bool is_active;
    bool is_periodic;
    function<void()> callback;
    Timer* next;
};

// Head of the linked list of timerg
Timer* TimerListHead = nullptr;
mutex mtx;

// Add a timer
void add_timer(uint32_t duration_ms, bool is_periodic, function<void()> callback) {
    lock_guard<mutex> lock(mtx);
    Timer* new_timer = new Timer();
    new_timer->duration_ms = duration_ms;
    new_timer->expired_time = steady_clock::now() + milliseconds(duration_ms);
    new_timer->is_active = true;
    new_timer->is_periodic = is_periodic;
    new_timer->callback = callback;
    new_timer->next = TimerListHead;
    
    TimerListHead = new_timer;
}

// Check and handle expired timers
void check_timers() {
    lock_guard<mutex> lock(mtx);
    auto current_time = steady_clock::now();
    Timer* prev = nullptr;
    Timer* current = TimerListHead;

    while (current != nullptr) {
        if (current->is_active && current->expired_time <= current_time) {
            current->callback();
            if (current->is_periodic) {
                current->expired_time = current_time + milliseconds(current->duration_ms);
            } else {
                if (prev) {
                    prev->next = current->next;
                } else {
                    TimerListHead = current->next;
                }
                Timer* temp = current;
                current = current->next;
                delete temp;
                continue;
            }
            

        }
        prev = current;
        current = current->next;
    }
}

// Remove a timer based on the callback function
void remove_timer(function<void()> callback) {
    lock_guard<mutex> lock(mtx);
    Timer* prev = nullptr;
    Timer* current = TimerListHead;

    while (current != nullptr) {
        if (current->callback.target<void()>() == callback.target<void()>()) {
            if (prev) {
                prev->next = current->next;
            } else {
                TimerListHead = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Test function
void test_callback() {
    cout << "Timer expired!" << endl;
}

int main() {
    // Example to add a periodic timer
    add_timer(2000, true, test_callback);

    // Continuously check timers every 100 ms
    while (true) {
        check_timers();
        this_thread::sleep_for(milliseconds(100));
    }

    return 0;
}