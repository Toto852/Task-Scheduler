#include <TaskScheduler.h>
#include <stdio.h>
#include <avr/io.h>

#define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST     // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only

#define PERIOD1 500
#define PERIOD2 1000
#define DURATION 10000

void toggleLED1();
void toggleLED2();

Scheduler ts;

Task t1(PERIOD1 * TASK_MILLISECOND, DURATION / PERIOD1, &toggleLED1, &ts, true);
Task t2(PERIOD2 * TASK_MILLISECOND, DURATION / PERIOD2, &toggleLED2, &ts, false);

void toggleLED1() {
  PORTB ^= (1<<PORTB5);
  if ( t1.isLastIteration() ) {
    t2.restartDelayed(2 * TASK_SECOND);
    PORTB &= ~(1 << PORTB5);
  }
  
}

void toggleLED2() {
  PORTB ^= (1<<PORTB5);
  if ( t2.isLastIteration() ) {
    t1.restartDelayed(2 * TASK_SECOND);
    PORTB &= ~(1 << PORTB5);
  }
}

int main(void) {
  Serial.begin(115200);
  // Configure PB5 as output (LED)
  DDRB |= (1 << DDB5);
  pinMode(LED_PIN, OUTPUT);
  //PORTB &= ~(1 << PORTB5);  // Ensure the LED is off initially

  while (1) {        
    ts.execute(); 
  }
}