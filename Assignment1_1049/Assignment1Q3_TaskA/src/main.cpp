//Meerab Zahra
//23-NTU-CS-1049
//Assignment1Q3_PartA

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define MODE_BUTTON 36
#define RESET_BUTTON 34

#define LED1_PIN 18
#define LED2_PIN 19
#define LED3_PIN 5  

// PWM Channels
#define LED1_CH 1
#define LED2_CH 2
#define LED3_CH 3

// PWM Settings
#define FREQ 5000
#define RESOLUTION 10

// Variables
int mode = 0;
unsigned long previousMillis = 0;
bool blinkState = false;
int fadeValue = 0;
int fadeDir = 1;

// Forward declaration
void updateDisplay();

void setup() {
  pinMode(MODE_BUTTON, INPUT);    // Using external resistors
  pinMode(RESET_BUTTON, INPUT);

  // Setup PWM channels
  ledcSetup(LED1_CH, FREQ, 8);   
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, FREQ, 8);  
  ledcAttachPin(LED2_PIN, LED2_CH);

  ledcSetup(LED3_CH, FREQ, 8); 
  ledcAttachPin(LED3_PIN, LED3_CH);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { for(;;); }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.print("Initializing...");
  display.display();

  mode = 0; // Start in initializing mode
  previousMillis = millis();
}

void loop() {
  // --- Mode button ---
  if (digitalRead(MODE_BUTTON) == HIGH) {
    delay(200); // debounce
    if (mode == 0) mode = 1;   // Go from initializing to first mode
    else {
      mode++;
      if (mode > 4) mode = 1;
    }
    updateDisplay();
    while (digitalRead(MODE_BUTTON) == HIGH); // wait for release
  }

  if (digitalRead(RESET_BUTTON) == HIGH) {
  delay(200); 
  mode = 99;  
  ledcWrite(LED1_CH, 0);
  ledcWrite(LED2_CH, 0);
  ledcWrite(LED3_CH, 0);

  // Display "Circuit Reset" on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Circuit Reset");
  display.display();

  while (digitalRead(RESET_BUTTON) == HIGH); 
}

  // --- Mode behavior ---
  switch (mode) {
    case 0: // Initializing
      ledcWrite(LED1_CH, 0);
      ledcWrite(LED2_CH, 0);
      ledcWrite(LED3_CH, 0);
      break;

    case 1: // All OFF
      ledcWrite(LED1_CH, 0);
      ledcWrite(LED2_CH, 0);
      ledcWrite(LED3_CH, 0);
      break;

    case 2: // Alternate Blink
      if (millis() - previousMillis > 500) {
        previousMillis = millis();
        blinkState = !blinkState;
        ledcWrite(LED1_CH, blinkState ? 255 : 0);
        ledcWrite(LED2_CH, blinkState ? 0 : 179);
        ledcWrite(LED3_CH, blinkState ? 128 : 0);
      }
      break;

    case 3: // All ON
      ledcWrite(LED1_CH, 255);
      ledcWrite(LED2_CH, 179);
      ledcWrite(LED3_CH, 128);
      break;

    case 4: // PWM Fade
      ledcWrite(LED1_CH, fadeValue);
      ledcWrite(LED2_CH, 255 - fadeValue);
      ledcWrite(LED3_CH, fadeValue / 2);
      fadeValue += fadeDir;
      if (fadeValue <= 0 || fadeValue >= 255) fadeDir = -fadeDir;
      delay(10);
      break;
  }
}

void updateDisplay() {
  display.clearDisplay();

  if (mode == 0) {
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.print("Initializing");
  } else {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Current Mode:");

    display.setTextSize(2);
    display.setCursor(0, 20);
    if (mode == 1) display.print("All OFF");
    else if (mode == 2) display.print("Blinking");
    else if (mode == 3) display.print("All ON");
    else if (mode == 4) display.print("PWM Fade");
  }

  display.display();
}

