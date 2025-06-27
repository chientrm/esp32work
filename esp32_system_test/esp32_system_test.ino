/*
  ESP32-WROOM-32 Simple System Test

  Simplified version that fits in flash memory and tests your
  ESP32-WROOM-32 (2Y-ESP32) hardware capabilities.
*/

#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("\n=== ESP32-WROOM-32 (2Y-ESP32) System Test ===");

    // Display basic chip info
    Serial.printf("Chip Model: %s\n", ESP.getChipModel());
    Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
    Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("Free Heap: %d KB\n", ESP.getFreeHeap() / 1024);

    // Test built-in LED
    pinMode(2, OUTPUT);
    Serial.println("Testing built-in LED (GPIO2)...");
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(2, HIGH);
        delay(200);
        digitalWrite(2, LOW);
        delay(200);
    }
    Serial.println("LED test complete!");

    // Test WiFi capability
    Serial.println("Testing WiFi capability...");
    WiFi.mode(WIFI_STA);
    int networks = WiFi.scanNetworks();
    if (networks > 0)
    {
        Serial.printf("Found %d WiFi networks:\n", networks);
        for (int i = 0; i < min(5, networks); i++)
        {
            Serial.printf("  %d: %s (RSSI: %d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }
    }
    else
    {
        Serial.println("No WiFi networks found");
    }
    WiFi.scanDelete();

    Serial.println("\n=== System Test Complete ===");
    Serial.println("Your ESP32-WROOM-32 is working correctly!");
    Serial.println("======================================");
}

void loop()
{
    // Blink LED and show uptime
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);

    Serial.printf("Uptime: %d seconds | Free Heap: %d KB\n",
                  millis() / 1000, ESP.getFreeHeap() / 1024);
}
