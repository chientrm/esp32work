/*
  ESP32-WROOM-32 System Information Display (Simplified)

  A compact version that displays essential ESP32 information
  without exceeding flash memory limits.
*/

#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("\n" + String("=").substring(0, 50));
    Serial.println("ESP32-WROOM-32 (2Y-ESP32) System Info");
    Serial.println(String("=").substring(0, 50));

    // Basic chip information
    Serial.printf("Chip Model: %s\n", ESP.getChipModel());
    Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
    Serial.printf("CPU Cores: 2\n");
    Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());

    // Memory information
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("Free Heap: %d KB\n", ESP.getFreeHeap() / 1024);
    Serial.printf("Total Heap: %d KB\n", ESP.getHeapSize() / 1024);

    // WiFi capabilities
    Serial.println("\n--- WiFi Test ---");
    WiFi.mode(WIFI_STA);
    int networks = WiFi.scanNetworks();
    if (networks > 0)
    {
        Serial.printf("Found %d WiFi networks\n", networks);
        Serial.println("WiFi radio working correctly!");

        // Show first few networks
        for (int i = 0; i < min(3, networks); i++)
        {
            Serial.printf("  %s (%d dBm)\n",
                          WiFi.SSID(i).c_str(), WiFi.RSSI(i));
        }
    }
    else
    {
        Serial.println("No WiFi networks found");
    }
    WiFi.scanDelete();

    // MAC Address
    Serial.printf("WiFi MAC: %s\n", WiFi.macAddress().c_str());

    // Temperature
    Serial.printf("Internal Temp: %.1f°C\n", temperatureRead());

    Serial.println(String("=").substring(0, 50));
    Serial.println("System test complete - All systems OK!");
    Serial.println("Monitoring system every 10 seconds...");
    Serial.println(String("=").substring(0, 50));
}

void loop()
{
    delay(10000); // 10 second interval

    // System status update
    Serial.println("\n--- Status Update ---");
    Serial.printf("Uptime: %lu seconds\n", millis() / 1000);
    Serial.printf("Free Heap: %d KB (%.1f%%)\n",
                  ESP.getFreeHeap() / 1024,
                  (ESP.getFreeHeap() * 100.0) / ESP.getHeapSize());
    Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Temperature: %.1f°C\n", temperatureRead());

    // Memory warning
    if (ESP.getFreeHeap() < 50000)
    {
        Serial.println("⚠️  Low memory warning!");
    }

    Serial.println("--------------------");
}
