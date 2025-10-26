//Meerab Zahra
//23-NTU-CS-1049
//Assignment1Q3_PartB

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
#define BUTTON_PIN 36
#define LED_PIN 18
#define BUZZER_PIN 19

// Variables
bool ledState = false;
unsigned long pressStart = 0;
bool buttonPressed = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT);   // external pull-down or use INPUT_PULLUP
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) for(;;);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.print("Ready");
  display.display();
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // When button is pressed
  if (buttonState == HIGH && !buttonPressed) {
    buttonPressed = true;
    pressStart = millis();  // mark time
  }

  // When button is released
  if (buttonState == LOW && buttonPressed) {
    unsigned long pressDuration = millis() - pressStart;
    buttonPressed = false;

    if (pressDuration < 1500) {
      // Short press → Toggle LED
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);

      if (ledState) {
        // LED turned ON
        display.print("Short Hold");
        display.display();
      } else {
        // LED turned OFF
        display.print("Short Hold");
        display.display();
        delay(1000); 

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.print("Ready");
        display.display();
      }

    } else {
      // Long press → Play buzzer tone
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("Long Hold");
      display.display();

      tone(BUZZER_PIN, 1000, 3000); // buzzer ON for 3 seconds
      delay(2000);                  // wait until buzzer finishes

      // After buzzer stops, return to "Ready"
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("Ready");
      display.display();
    }
  }
}
