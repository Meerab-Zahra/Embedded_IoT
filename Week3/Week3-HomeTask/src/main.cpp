#include <Arduino.h>

#define LED1_PIN      5   
#define LED2_PIN      16       
#define BUTTON1_PIN   14  
#define BUTTON2_PIN   13  
#define DEBOUNCE_MS   50        
#define DEBOUNCE_US   (DEBOUNCE_MS * 1000UL)

hw_timer_t* debounceTimer1 = nullptr;
hw_timer_t* debounceTimer2 = nullptr;
volatile bool debounceActive1 = false;   
volatile bool debounceActive2 = false;  

void ARDUINO_ISR_ATTR onDebounceTimer1() {

  if (digitalRead(BUTTON1_PIN) == LOW) {
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));  
  }
  debounceActive1 = false; 
}

void ARDUINO_ISR_ATTR onDebounceTimer2() {

  if (digitalRead(BUTTON2_PIN) == LOW) {
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));  
  }
  debounceActive2 = false; 
}


void ARDUINO_ISR_ATTR onButton1ISR() {
  if (!debounceActive1) {
    debounceActive1 = true;
    timerAlarm(debounceTimer1, DEBOUNCE_US, false, 0);
  }
}

void ARDUINO_ISR_ATTR onButton2ISR() {
  if (!debounceActive2) {
    debounceActive2 = true;
    timerAlarm(debounceTimer2, DEBOUNCE_US, false, 0);
  }
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON1_PIN, onButton1ISR, FALLING);

  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON2_PIN, onButton2ISR, FALLING);

  debounceTimer1 = timerBegin(1000000);
  debounceTimer2 = timerBegin(1000000);
  timerAttachInterrupt(debounceTimer1, &onDebounceTimer1);
  timerAttachInterrupt(debounceTimer2, &onDebounceTimer2);
}

void loop() {
  // Nothing to do. Interrupts handle everything.
}