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

    // Test analog input capabilities
    Serial.println("Testing analog input (GPIO36)...");
    for (int i = 0; i < 5; i++)
    {
        int analogValue = analogRead(36); // VP pin
        float voltage = (analogValue * 3.3) / 4095.0;
        Serial.printf("  Reading %d: %d (%.2fV)\n", i + 1, analogValue, voltage);
        delay(500);
    }
    Serial.println("Analog input test complete!");

    // Test touch sensor
    Serial.println("Testing touch sensor (GPIO15)...");
    for (int i = 0; i < 5; i++)
    {
        int touchValue = touchRead(15);
        Serial.printf("  Touch reading %d: %d %s\n", i + 1, touchValue,
                      touchValue < 20 ? "(TOUCHED)" : "(NOT TOUCHED)");
        delay(500);
    }
    Serial.println("Touch sensor test complete!");

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
    // Show system status without LED blinking
    Serial.printf("Uptime: %d seconds | Free Heap: %d KB\n",
                  millis() / 1000, ESP.getFreeHeap() / 1024);

    // Read analog and touch sensors periodically
    int analogValue = analogRead(36);
    int touchValue = touchRead(15);
    float voltage = (analogValue * 3.3) / 4095.0;

    Serial.printf("Sensors - Analog: %d (%.2fV) | Touch: %d %s\n",
                  analogValue, voltage, touchValue,
                  touchValue < 20 ? "(TOUCHED)" : "");

    delay(3000); // Update every 3 seconds
}
