/*
  ESP32 PlatformIO Basic Project

  This is a basic template for ESP32 development using PlatformIO.
  It demonstrates the project structure and basic ESP32 functionality.

  Hardware:
  - ESP32 38-pin development board with FT232
  - Built-in LED on GPIO2

  Features:
  - Serial output with system information
  - LED blinking with timing control
  - Memory usage monitoring
  - WiFi capability check (without connecting)

  Author: ESP32 Development Workspace
  Date: 2025
*/

#include <Arduino.h>
#include <WiFi.h>

// Pin definitions
#define LED_PIN 2
#define BLINK_INTERVAL 1000

// Global variables
unsigned long previousMillis = 0;
bool ledState = false;
unsigned long bootTime = 0;

// Function prototypes
void printSystemInfo();
void printMemoryInfo();
void blinkLED();

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);
    delay(1000);

    bootTime = millis();

    Serial.println("\n=== ESP32 PlatformIO Basic Project ===");
    Serial.println("Initializing system...");

    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Print system information
    printSystemInfo();

    Serial.println("Setup completed successfully!");
    Serial.println("System ready for operation.");
    Serial.println("=====================================\n");
}

void loop()
{
    // Blink LED
    blinkLED();

    // Print status every 10 seconds
    static unsigned long lastStatusPrint = 0;
    if (millis() - lastStatusPrint >= 10000)
    {
        lastStatusPrint = millis();

        Serial.println("\n--- System Status ---");
        Serial.print("Uptime: ");
        Serial.print((millis() - bootTime) / 1000);
        Serial.println(" seconds");

        printMemoryInfo();

        Serial.print("LED State: ");
        Serial.println(ledState ? "ON" : "OFF");
        Serial.println("--------------------\n");
    }

    // Small delay to prevent watchdog issues
    delay(10);
}

void printSystemInfo()
{
    Serial.println("\n--- System Information ---");

    // Chip information
    Serial.print("Chip Model: ");
    Serial.println(ESP.getChipModel());
    Serial.print("Chip Revision: ");
    Serial.println(ESP.getChipRevision());
    Serial.print("Number of Cores: ");
    Serial.println(ESP.getChipCores());

    // Frequency information
    Serial.print("CPU Frequency: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");

    // Flash information
    Serial.print("Flash Size: ");
    Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
    Serial.println(" MB");
    Serial.print("Flash Speed: ");
    Serial.print(ESP.getFlashChipSpeed() / (1000 * 1000));
    Serial.println(" MHz");

    // SDK information
    Serial.print("ESP-IDF Version: ");
    Serial.println(ESP.getSdkVersion());

    // MAC Address
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

    // Memory information
    printMemoryInfo();

    Serial.println("-------------------------");
}

void printMemoryInfo()
{
    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    Serial.print("Largest Free Block: ");
    Serial.print(ESP.getMaxAllocHeap());
    Serial.println(" bytes");

    Serial.print("Min Free Heap: ");
    Serial.print(ESP.getMinFreeHeap());
    Serial.println(" bytes");

    // PSRAM information (if available)
    if (ESP.getPsramSize() > 0)
    {
        Serial.print("PSRAM Size: ");
        Serial.print(ESP.getPsramSize());
        Serial.println(" bytes");
        Serial.print("Free PSRAM: ");
        Serial.print(ESP.getFreePsram());
        Serial.println(" bytes");
    }
    else
    {
        Serial.println("PSRAM: Not available");
    }
}

void blinkLED()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= BLINK_INTERVAL)
    {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);

        Serial.print("LED: ");
        Serial.println(ledState ? "ON" : "OFF");
    }
}

/*
  PlatformIO Commands:

  Build project:
    pio run

  Upload to board:
    pio run --target upload

  Serial monitor:
    pio device monitor

  Clean build:
    pio run --target clean

  Upload and monitor:
    pio run --target upload && pio device monitor

  List devices:
    pio device list

  Expected Output:
  === ESP32 PlatformIO Basic Project ===
  Initializing system...

  --- System Information ---
  Chip Model: ESP32-D0WDQ6
  Chip Revision: 1
  Number of Cores: 2
  CPU Frequency: 240 MHz
  Flash Size: 4 MB
  Flash Speed: 40 MHz
  ESP-IDF Version: v4.4.2
  MAC Address: AA:BB:CC:DD:EE:FF
  Free Heap: 295000 bytes
  Largest Free Block: 110000 bytes
  Min Free Heap: 290000 bytes
  PSRAM: Not available
  -------------------------

  Setup completed successfully!
  System ready for operation.
  =====================================

  LED: ON
  LED: OFF
  LED: ON
  ...

  --- System Status ---
  Uptime: 10 seconds
  Free Heap: 294000 bytes
  ...

  Project Structure:
  basic_project/
  ├── platformio.ini    # Project configuration
  ├── src/
  │   └── main.cpp      # Main source file
  ├── lib/              # Private libraries
  ├── include/          # Header files
  └── test/             # Unit tests
*/
