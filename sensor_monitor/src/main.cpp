/*
  ESP32-WROOM-32 Sensor Monitor

  Comprehensive sensor monitoring program that reads:
  - Analog inputs (ADC)
  - Touch sensors
  - System temperature
  - Memory usage
  - System health
*/

#include <Arduino.h>
#include <WiFi.h>

// Pin definitions for 38-pin ESP32 board
const int ANALOG_PIN_1 = 36; // VP - ADC1_CH0
const int ANALOG_PIN_2 = 39; // VN - ADC1_CH3
const int TOUCH_PIN_1 = 4;   // Touch sensor
const int TOUCH_PIN_2 = 15;  // Touch sensor

// Timing variables
unsigned long lastSensorRead = 0;
unsigned long lastSystemCheck = 0;
const unsigned long SENSOR_INTERVAL = 2000;  // 2 seconds
const unsigned long SYSTEM_INTERVAL = 10000; // 10 seconds

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("=====================================");
    Serial.println("ESP32-WROOM-32 Sensor Monitor");
    Serial.println("=====================================");

    // Display system info
    displaySystemInfo();

    Serial.println("\nStarting sensor monitoring...");
    Serial.println("-------------------------------------");
}

void loop()
{
    unsigned long currentTime = millis();

    // Read sensors every 2 seconds
    if (currentTime - lastSensorRead >= SENSOR_INTERVAL)
    {
        readSensors();
        lastSensorRead = currentTime;
    }

    // System health check every 10 seconds
    if (currentTime - lastSystemCheck >= SYSTEM_INTERVAL)
    {
        displaySystemHealth();
        lastSystemCheck = currentTime;
    }

    delay(100);
}

void displaySystemInfo()
{
    Serial.println("\n=== System Information ===");
    Serial.printf("Chip Model: %s\n", ESP.getChipModel());
    Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
    Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("Total Heap: %d KB\n", ESP.getHeapSize() / 1024);

    // MAC Address
    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.printf("WiFi MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    Serial.println("============================");
}

void readSensors()
{
    Serial.println("\n--- Sensor Readings ---");

    // Read analog sensors
    int analog1 = analogRead(ANALOG_PIN_1);
    int analog2 = analogRead(ANALOG_PIN_2);
    float voltage1 = (analog1 * 3.3) / 4095.0;
    float voltage2 = (analog2 * 3.3) / 4095.0;

    Serial.printf("Analog 1 (GPIO36): %d (%.2fV)\n", analog1, voltage1);
    Serial.printf("Analog 2 (GPIO39): %d (%.2fV)\n", analog2, voltage2);

    // Read touch sensors
    int touch1 = touchRead(TOUCH_PIN_1);
    int touch2 = touchRead(TOUCH_PIN_2);

    Serial.printf("Touch 1 (GPIO4):  %d %s\n", touch1, touch1 < 20 ? "(TOUCHED)" : "");
    Serial.printf("Touch 2 (GPIO15): %d %s\n", touch2, touch2 < 20 ? "(TOUCHED)" : "");

    // Internal temperature
    float temperature = temperatureRead();
    Serial.printf("Internal Temp: %.1f°C\n", temperature);

    Serial.println("-----------------------");
}

void displaySystemHealth()
{
    Serial.println("\n=== System Health ===");
    Serial.printf("Uptime: %lu seconds (%.1f minutes)\n",
                  millis() / 1000, millis() / 60000.0);

    Serial.printf("Free Heap: %d KB (%.1f%%)\n",
                  ESP.getFreeHeap() / 1024,
                  (ESP.getFreeHeap() * 100.0) / ESP.getHeapSize());

    Serial.printf("Min Free Heap: %d KB\n", ESP.getMinFreeHeap() / 1024);

    // Memory warning
    if (ESP.getFreeHeap() < 50000)
    {
        Serial.println("⚠️  WARNING: Low memory!");
    }

    Serial.println("======================");
}
