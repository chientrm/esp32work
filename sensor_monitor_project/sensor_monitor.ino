/*
  ESP32-WROOM-32 Sensor Monitor & GPIO Test

  This program demonstrates various ESP32 capabilities without LED blinking:
  - Analog sensor readings (ADC)
  - Digital input monitoring
  - Touch sensor detection
  - Temperature monitoring
  - Serial data output
  - WiFi network analysis

  Hardware:
  - ESP32-WROOM-32 (2Y-ESP32) module
  - 38-pin development board with FT232
  - Optional: Connect sensors to GPIO pins for testing
*/

#include <WiFi.h>

// Pin definitions for different sensor types
#define ANALOG_PIN_1 32  // ADC1_CH4 - for analog sensor
#define ANALOG_PIN_2 33  // ADC1_CH5 - for analog sensor
#define DIGITAL_PIN_1 34 // Input-only pin
#define DIGITAL_PIN_2 35 // Input-only pin
#define TOUCH_PIN_1 4    // Touch sensor pin
#define TOUCH_PIN_2 27   // Touch sensor pin

// Variables for sensor monitoring
unsigned long lastReading = 0;
const unsigned long READING_INTERVAL = 2000; // 2 seconds
int readingCount = 0;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("\n" + String("=").substring(0, 50));
    Serial.println("ESP32-WROOM-32 Sensor Monitor & GPIO Test");
    Serial.println(String("=").substring(0, 50));

    // Initialize pins
    pinMode(DIGITAL_PIN_1, INPUT);
    pinMode(DIGITAL_PIN_2, INPUT);
    pinMode(TOUCH_PIN_1, INPUT);
    pinMode(TOUCH_PIN_2, INPUT);

    // Display system info
    displaySystemInfo();

    // Initialize WiFi for network scanning
    WiFi.mode(WIFI_STA);

    Serial.println("\nStarting sensor monitoring...");
    Serial.println("Reading sensors every 2 seconds");
    Serial.println(String("-").substring(0, 50));
}

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - lastReading >= READING_INTERVAL)
    {
        lastReading = currentTime;
        readingCount++;

        // Header for this reading cycle
        Serial.printf("\n--- Reading #%d (Uptime: %d seconds) ---\n",
                      readingCount, currentTime / 1000);

        // Read analog sensors
        readAnalogSensors();

        // Read digital inputs
        readDigitalInputs();

        // Read touch sensors
        readTouchSensors();

        // Monitor system health
        monitorSystemHealth();

        // WiFi environment scan (every 5th reading)
        if (readingCount % 5 == 0)
        {
            scanWiFiEnvironment();
        }

        Serial.println(String("-").substring(0, 40));
    }

    delay(100); // Small delay for system stability
}

void displaySystemInfo()
{
    Serial.println("\n--- System Information ---");
    Serial.printf("Chip: %s (Revision %d)\n", ESP.getChipModel(), ESP.getChipRevision());
    Serial.printf("CPU: %d MHz, Cores: 2\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("RAM: %d KB total, %d KB free\n",
                  ESP.getHeapSize() / 1024, ESP.getFreeHeap() / 1024);
    Serial.printf("MAC Address: %s\n", WiFi.macAddress().c_str());
    Serial.println("------------------------");
}

void readAnalogSensors()
{
    Serial.println("Analog Sensors (12-bit ADC, 0-4095):");

    // Read multiple samples for accuracy
    int samples = 10;

    // Analog Pin 1 (GPIO32)
    long sum1 = 0;
    for (int i = 0; i < samples; i++)
    {
        sum1 += analogRead(ANALOG_PIN_1);
        delay(10);
    }
    int avg1 = sum1 / samples;
    float voltage1 = (avg1 * 3.3) / 4095.0;

    // Analog Pin 2 (GPIO33)
    long sum2 = 0;
    for (int i = 0; i < samples; i++)
    {
        sum2 += analogRead(ANALOG_PIN_2);
        delay(10);
    }
    int avg2 = sum2 / samples;
    float voltage2 = (avg2 * 3.3) / 4095.0;

    Serial.printf("  GPIO32: %d (%.2fV) ", avg1, voltage1);
    Serial.printf("  GPIO33: %d (%.2fV)\n", avg2, voltage2);

    // Interpret readings
    if (voltage1 > 3.0)
        Serial.println("    GPIO32: High voltage detected");
    else if (voltage1 < 0.5)
        Serial.println("    GPIO32: Low/Ground detected");
    else
        Serial.println("    GPIO32: Floating or intermediate voltage");

    if (voltage2 > 3.0)
        Serial.println("    GPIO33: High voltage detected");
    else if (voltage2 < 0.5)
        Serial.println("    GPIO33: Low/Ground detected");
    else
        Serial.println("    GPIO33: Floating or intermediate voltage");
}

void readDigitalInputs()
{
    Serial.println("Digital Inputs (Input-only pins):");

    bool pin34 = digitalRead(DIGITAL_PIN_1);
    bool pin35 = digitalRead(DIGITAL_PIN_2);

    Serial.printf("  GPIO34: %s  GPIO35: %s\n",
                  pin34 ? "HIGH" : "LOW",
                  pin35 ? "HIGH" : "LOW");

    // Count state changes (simple activity detection)
    static bool lastPin34 = false;
    static bool lastPin35 = false;
    static int changes34 = 0;
    static int changes35 = 0;

    if (pin34 != lastPin34)
        changes34++;
    if (pin35 != lastPin35)
        changes35++;

    if (changes34 > 0 || changes35 > 0)
    {
        Serial.printf("    Activity: GPIO34 changed %d times, GPIO35 changed %d times\n",
                      changes34, changes35);
    }

    lastPin34 = pin34;
    lastPin35 = pin35;
}

void readTouchSensors()
{
    Serial.println("Touch Sensors (Lower values = touched):");

    int touch1 = touchRead(TOUCH_PIN_1);
    int touch2 = touchRead(TOUCH_PIN_2);

    Serial.printf("  GPIO4: %d  GPIO27: %d\n", touch1, touch2);

    // Touch detection threshold (typical baseline ~40-80, touched ~10-30)
    int threshold = 30;

    if (touch1 < threshold)
    {
        Serial.println("    Touch detected on GPIO4!");
    }
    if (touch2 < threshold)
    {
        Serial.println("    Touch detected on GPIO27!");
    }

    // Baseline calibration info
    static int maxTouch1 = 0, maxTouch2 = 0;
    if (touch1 > maxTouch1)
        maxTouch1 = touch1;
    if (touch2 > maxTouch2)
        maxTouch2 = touch2;

    if (readingCount % 10 == 0)
    {
        Serial.printf("    Baseline calibration: GPIO4 max=%d, GPIO27 max=%d\n",
                      maxTouch1, maxTouch2);
    }
}

void monitorSystemHealth()
{
    Serial.println("System Health:");

    // Memory usage
    uint32_t freeHeap = ESP.getFreeHeap();
    uint32_t totalHeap = ESP.getHeapSize();
    float memoryUsage = ((totalHeap - freeHeap) * 100.0) / totalHeap;

    Serial.printf("  Memory: %.1f%% used (%d KB free)\n",
                  memoryUsage, freeHeap / 1024);

    // Temperature (internal sensor)
    float temp = temperatureRead();
    Serial.printf("  Internal Temperature: %.1f°C\n", temp);

    if (temp > 60.0)
    {
        Serial.println("    Warning: High temperature detected!");
    }

    // CPU frequency
    Serial.printf("  CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());

    // Stack usage
    Serial.printf("  Free Stack: %d bytes\n", uxTaskGetStackHighWaterMark(NULL));

    // Power supply stability indicator (rough estimate)
    int vccReading = analogRead(36); // SVP pin
    Serial.printf("  Power Supply Indicator: %d\n", vccReading);
}

void scanWiFiEnvironment()
{
    Serial.println("WiFi Environment Scan:");

    int networks = WiFi.scanNetworks(false, false, false, 300);

    if (networks > 0)
    {
        Serial.printf("  Found %d networks:\n", networks);

        // Show top 3 strongest signals
        for (int i = 0; i < min(3, networks); i++)
        {
            String security = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured";
            Serial.printf("    %d: %s (Ch:%d, RSSI:%d dBm, %s)\n",
                          i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i),
                          WiFi.RSSI(i), security.c_str());
        }

        // Analyze signal environment
        int strongSignals = 0;
        int channel24Count = 0;

        for (int i = 0; i < networks; i++)
        {
            if (WiFi.RSSI(i) > -50)
                strongSignals++;
            if (WiFi.channel(i) <= 13)
                channel24Count++;
        }

        Serial.printf("    Analysis: %d strong signals, %d on 2.4GHz\n",
                      strongSignals, channel24Count);

        if (strongSignals > 5)
        {
            Serial.println("    Note: Dense WiFi environment detected");
        }
    }
    else
    {
        Serial.println("  No WiFi networks detected");
    }

    WiFi.scanDelete();
}

/*
  Expected Output Example:

  ==================================================
  ESP32-WROOM-32 Sensor Monitor & GPIO Test
  ==================================================

  --- System Information ---
  Chip: ESP32-D0WDQ6 (Revision 1)
  CPU: 240 MHz, Cores: 2
  Flash: 4 MB
  RAM: 320 KB total, 285 KB free
  MAC Address: AA:BB:CC:DD:EE:FF
  ------------------------

  Starting sensor monitoring...
  Reading sensors every 2 seconds
  --------------------------------------------------

  --- Reading #1 (Uptime: 5 seconds) ---
  Analog Sensors (12-bit ADC, 0-4095):
    GPIO32: 2048 (1.65V)  GPIO33: 0 (0.00V)
      GPIO32: Floating or intermediate voltage
      GPIO33: Low/Ground detected
  Digital Inputs (Input-only pins):
    GPIO34: LOW  GPIO35: HIGH
  Touch Sensors (Lower values = touched):
    GPIO4: 65  GPIO27: 42
  System Health:
    Memory: 15.2% used (285 KB free)
    Internal Temperature: 42.3°C
    CPU Frequency: 240 MHz
    Free Stack: 1952 bytes
    Power Supply Indicator: 1890
  ----------------------------------------

  This program demonstrates:
  - Continuous sensor monitoring without blinking LEDs
  - Multi-pin analog and digital reading
  - Touch sensor capability
  - System health monitoring
  - WiFi environment analysis
  - Real-time data interpretation
*/
