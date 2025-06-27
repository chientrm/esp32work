/*
  ESP32-WROOM-32 Basic Blink

  Simple LED blinking program for testing ESP32 functionality.
  Uses GPIO2 (built-in LED on most ESP32 boards).
*/

#include <Arduino.h>

// Built-in LED is usually on GPIO2
const int LED_PIN = 2;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    Serial.println("ESP32 Basic Blink Test Starting...");
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
    delay(1000);

    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
    delay(1000);
}
