/*
  ESP32 Blink Example

  This example demonstrates basic GPIO control on the ESP32.
  It blinks the built-in LED and an external LED.

  Hardware:
  - ESP32 38-pin development board with FT232
  - Built-in LED on GPIO2
  - Optional: External LED on GPIO23 with 220Ω resistor

  Author: ESP32 Development Workspace
  Date: 2025
*/

// LED pins
#define BUILTIN_LED 2   // Built-in LED (blue)
#define EXTERNAL_LED 23 // External LED pin

// Timing
#define BLINK_DELAY 1000 // 1 second

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);
    delay(1000); // Give time for serial monitor to connect

    Serial.println("ESP32 Blink Example Starting...");
    Serial.println("Board: ESP32 38-pin with FT232");
    Serial.println("Built-in LED: GPIO2");
    Serial.println("External LED: GPIO23");

    // Initialize LED pins as outputs
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(EXTERNAL_LED, OUTPUT);

    // Start with LEDs off
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(EXTERNAL_LED, LOW);

    Serial.println("Setup complete!");
    Serial.println("LEDs will blink every " + String(BLINK_DELAY) + "ms");
    Serial.println("---");
}

void loop()
{
    // Turn LEDs on
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(EXTERNAL_LED, HIGH);
    Serial.println("LEDs ON  - Uptime: " + String(millis() / 1000) + "s");

    delay(BLINK_DELAY);

    // Turn LEDs off
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(EXTERNAL_LED, LOW);
    Serial.println("LEDs OFF - Uptime: " + String(millis() / 1000) + "s");

    delay(BLINK_DELAY);
}

/*
  Expected Output:
  ESP32 Blink Example Starting...
  Board: ESP32 38-pin with FT232
  Built-in LED: GPIO2
  External LED: GPIO23
  Setup complete!
  LEDs will blink every 1000ms
  ---
  LEDs ON  - Uptime: 1s
  LEDs OFF - Uptime: 2s
  LEDs ON  - Uptime: 3s
  LEDs OFF - Uptime: 4s
  ...

  Troubleshooting:
  1. If built-in LED doesn't blink: Check if GPIO2 is correct for your board
  2. If external LED doesn't work: Check wiring and resistor value
  3. If no serial output: Check baud rate (115200) and USB connection
  4. If upload fails: Hold BOOT button during upload
*/
