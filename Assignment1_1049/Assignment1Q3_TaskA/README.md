Wokwi Project Link:
https://wokwi.com/projects/445713792228976641

Pin Mapping:
In the designed circuit, an OLED display has been connected to ESP32 with its ground wire connected to ground, voltage wire connected to voltage (3V3), SCL connected to pin 22 and SDA connected to pin 21. Red LED has been connected in such a way that its negative side is grounded and on positive side, 1 kilo ohm resistor is connected and that resistor is connected to pin 18. Green and Yellow LEDs are connected to ESP32 the same way but they use pins 5 and 19 respectively. There are two push buttons in the circuit also. One acts as mode button and the other as reset button. To connect button, take any of two pairs and use both pins. One pin is attached to voltage and to the other pin, 10 kilo ohm resistor is attached. The resistor side connected to button pin is then connected to GPIO and the other side of resistor is grounded. For mode button, GPIO 36 is used and for reset button, GPIO 34 is used. 

Note:
PWM fading on hardware is more obvious as compared to Wokwi project simulating PWM fading.
