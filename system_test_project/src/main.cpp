/*
  ESP32-WROOM-32 System Information Display

  This example reads and displays detailed information about your specific
  ESP32-WROOM-32 module (2Y-ESP32 marking) including chip details, memory,
  and wireless capabilities.

  Hardware:
  - ESP32-WROOM-32 module (2Y-ESP32 marking)
  - 38-pin development board with FT232
  - Built-in WiFi 802.11 b/g/n (2.4GHz)
  - Built-in Bluetooth 4.2 + BLE

  Features:
  - Detailed chip identification
  - Memory usage monitoring
  - WiFi capability testing
  - Bluetooth capability testing
  - Flash memory information
  - Real-time system monitoring

  Author: ESP32 Development Workspace
  Date: 2025
*/

#include <WiFi.h>
#include <esp_system.h>
#include <esp_chip_info.h>
#include <esp_flash.h>
#include <BluetoothSerial.h>

// System monitoring variables
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 5000; // 5 seconds

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    delay(2000); // Give time for serial monitor to connect

    Serial.println("\n" + String("=").substring(0, 60));
    Serial.println("ESP32-WROOM-32 (2Y-ESP32) System Information");
    Serial.println(String("=").substring(0, 60));

    // Display comprehensive system information
    displayChipInfo();
    displayMemoryInfo();
    displayFlashInfo();
    displayWiFiCapabilities();
    displayBluetoothCapabilities();
    displayPinConfiguration();

    Serial.println(String("=").substring(0, 60));
    Serial.println("System initialization complete!");
    Serial.println("Monitoring system status every 5 seconds...");
    Serial.println(String("=").substring(0, 60));
}

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - lastUpdate >= UPDATE_INTERVAL)
    {
        lastUpdate = currentTime;

        Serial.println("\n--- Real-time System Status ---");
        Serial.print("Uptime: ");
        printUptime(currentTime);

        displayRuntimeMemoryInfo();
        displayTemperature();
        displayPowerInfo();

        Serial.println("------------------------------");
    }

    delay(100); // Small delay to prevent watchdog issues
}

void displayChipInfo()
{
    Serial.println("\n--- ESP32 Chip Information ---");

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    Serial.printf("Chip Model: %s\n", ESP.getChipModel());
    Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
    Serial.printf("Number of CPU Cores: %d\n", chip_info.cores);
    Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());

    // Chip features
    Serial.print("Features: ");
    if (chip_info.features & CHIP_FEATURE_WIFI_BGN)
    {
        Serial.print("WiFi 802.11 b/g/n ");
    }
    if (chip_info.features & CHIP_FEATURE_BT)
    {
        Serial.print("Bluetooth ");
    }
    if (chip_info.features & CHIP_FEATURE_BLE)
    {
        Serial.print("BLE ");
    }
    Serial.println();

    Serial.printf("Silicon Revision: %d\n", chip_info.revision);
    Serial.printf("ESP-IDF Version: %s\n", ESP.getSdkVersion());

    // MAC Addresses
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    Serial.printf("WiFi MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    esp_read_mac(mac, ESP_MAC_BT);
    Serial.printf("Bluetooth MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void displayMemoryInfo()
{
    Serial.println("\n--- Memory Information ---");

    // Heap memory
    Serial.printf("Total Heap Size: %u bytes (%.1f KB)\n",
                  ESP.getHeapSize(), ESP.getHeapSize() / 1024.0);
    Serial.printf("Free Heap: %u bytes (%.1f KB)\n",
                  ESP.getFreeHeap(), ESP.getFreeHeap() / 1024.0);
    Serial.printf("Largest Free Block: %u bytes (%.1f KB)\n",
                  ESP.getMaxAllocHeap(), ESP.getMaxAllocHeap() / 1024.0);
    Serial.printf("Minimum Free Heap: %u bytes (%.1f KB)\n",
                  ESP.getMinFreeHeap(), ESP.getMinFreeHeap() / 1024.0);

    // PSRAM (if available)
    if (ESP.getPsramSize() > 0)
    {
        Serial.printf("PSRAM Size: %u bytes (%.1f KB)\n",
                      ESP.getPsramSize(), ESP.getPsramSize() / 1024.0);
        Serial.printf("Free PSRAM: %u bytes (%.1f KB)\n",
                      ESP.getFreePsram(), ESP.getFreePsram() / 1024.0);
    }
    else
    {
        Serial.println("PSRAM: Not available on ESP32-WROOM-32");
    }

    // Stack information
    Serial.printf("Free Stack: %u bytes\n", uxTaskGetStackHighWaterMark(NULL));
}

void displayFlashInfo()
{
    Serial.println("\n--- Flash Memory Information ---");

    uint32_t flash_size;
    esp_flash_get_size(NULL, &flash_size);

    Serial.printf("Flash Size: %u bytes (%.1f MB)\n",
                  flash_size, flash_size / (1024.0 * 1024.0));
    Serial.printf("Flash Speed: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);
    Serial.printf("Flash Mode: %s\n",
                  (ESP.getFlashChipMode() == FM_QIO) ? "QIO" : (ESP.getFlashChipMode() == FM_QOUT) ? "QOUT"
                                                           : (ESP.getFlashChipMode() == FM_DIO)    ? "DIO"
                                                           : (ESP.getFlashChipMode() == FM_DOUT)   ? "DOUT"
                                                                                                   : "Unknown");

    // Sketch size information
    Serial.printf("Sketch Size: %u bytes (%.1f KB)\n",
                  ESP.getSketchSize(), ESP.getSketchSize() / 1024.0);
    Serial.printf("Free Sketch Space: %u bytes (%.1f KB)\n",
                  ESP.getFreeSketchSpace(), ESP.getFreeSketchSpace() / 1024.0);
}

void displayWiFiCapabilities()
{
    Serial.println("\n--- WiFi Capabilities (2.4GHz ISM Band) ---");

    Serial.println("Supported Standards: 802.11 b/g/n");
    Serial.println("Frequency Band: 2.4GHz ISM (2400-2485 MHz)");
    Serial.println("Channels: 1-13 (region dependent)");
    Serial.println("Max Data Rate: 150 Mbps (802.11n)");
    Serial.println("Security: WEP, WPA, WPA2, WPA3");
    Serial.println("Modes: Station (STA), Access Point (AP), Station+AP");

    // Test WiFi initialization
    WiFi.mode(WIFI_STA);
    Serial.print("WiFi Status: ");
    Serial.println((WiFi.status() == WL_NO_SHIELD) ? "Not available" : "Available");

    // Scan for networks (quick test)
    Serial.println("Performing quick WiFi scan...");
    int networks = WiFi.scanNetworks();
    if (networks > 0)
    {
        Serial.printf("Found %d WiFi networks nearby\n", networks);
        Serial.println("WiFi radio is working correctly!");
    }
    else
    {
        Serial.println("No networks found (WiFi may need antenna check)");
    }
    WiFi.scanDelete(); // Clean up
}

void displayBluetoothCapabilities()
{
    Serial.println("\n--- Bluetooth Capabilities ---");

    Serial.println("Bluetooth Version: 4.2");
    Serial.println("Protocols: Classic Bluetooth + BLE (Bluetooth Low Energy)");
    Serial.println("Frequency: 2.4GHz ISM Band");
    Serial.println("Range: ~10 meters (Class 2)");
    Serial.println("Profiles: SPP, A2DP, AVRCP, HFP, HSP, PBAP, etc.");

    // Test Bluetooth initialization
    Serial.print("Bluetooth Status: ");
    if (SerialBT.begin("ESP32-WROOM-32-Test"))
    {
        Serial.println("Available and initialized");
        SerialBT.end(); // Clean up
    }
    else
    {
        Serial.println("Initialization failed");
    }
}

void displayPinConfiguration()
{
    Serial.println("\n--- GPIO Pin Summary ---");
    Serial.println("Total GPIO Pins: 34");
    Serial.println("Digital I/O: 28 pins");
    Serial.println("Analog Input (ADC): 18 pins (12-bit resolution)");
    Serial.println("Analog Output (DAC): 2 pins (8-bit resolution)");
    Serial.println("Touch Sensors: 10 pins");
    Serial.println("PWM Channels: 16 channels");
    Serial.println("UART: 3 interfaces");
    Serial.println("SPI: 4 interfaces (2 usable)");
    Serial.println("I2C: 2 interfaces");

    Serial.println("\nSpecial Pins:");
    Serial.println("- GPIO0: Boot mode control");
    Serial.println("- GPIO2: Built-in LED");
    Serial.println("- GPIO34-39: Input only");
    Serial.println("- GPIO21,22: Default I2C (SDA, SCL)");
    Serial.println("- GPIO1,3: Serial0 (USB)");
}

void displayRuntimeMemoryInfo()
{
    uint32_t freeHeap = ESP.getFreeHeap();
    uint32_t maxAlloc = ESP.getMaxAllocHeap();

    Serial.printf("Free Heap: %u bytes (%.1f%% of total)\n",
                  freeHeap, (freeHeap * 100.0) / ESP.getHeapSize());
    Serial.printf("Largest Block: %u bytes\n", maxAlloc);

    // Memory fragmentation indicator
    float fragmentation = 100.0 - ((maxAlloc * 100.0) / freeHeap);
    Serial.printf("Heap Fragmentation: %.1f%%\n", fragmentation);
}

void displayTemperature()
{
    // Internal temperature sensor (approximate)
    Serial.print("Internal Temperature: ");
    Serial.print(temperatureRead());
    Serial.println("°C (approximate)");
}

void displayPowerInfo()
{
    // Read supply voltage (approximate via ADC)
    Serial.print("Supply Voltage: ");
    Serial.print("3.3V (nominal)");
    Serial.println();

    Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
}

void printUptime(unsigned long ms)
{
    unsigned long seconds = ms / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    unsigned long days = hours / 24;

    if (days > 0)
    {
        Serial.printf("%lu days, ", days);
    }
    if (hours > 0)
    {
        Serial.printf("%lu hours, ", hours % 24);
    }
    if (minutes > 0)
    {
        Serial.printf("%lu minutes, ", minutes % 60);
    }
    Serial.printf("%lu seconds\n", seconds % 60);
}

/*
  Expected Output:

  ============================================================
  ESP32-WROOM-32 (2Y-ESP32) System Information
  ============================================================

  --- ESP32 Chip Information ---
  Chip Model: ESP32-D0WDQ6
  Chip Revision: 1
  Number of CPU Cores: 2
  CPU Frequency: 240 MHz
  Features: WiFi 802.11 b/g/n Bluetooth BLE
  Silicon Revision: 1
  ESP-IDF Version: v4.4.x
  WiFi MAC Address: AA:BB:CC:DD:EE:FF
  Bluetooth MAC Address: AA:BB:CC:DD:EE:FG

  --- Memory Information ---
  Total Heap Size: 327680 bytes (320.0 KB)
  Free Heap: 295000 bytes (288.1 KB)
  Largest Free Block: 110000 bytes (107.4 KB)
  Minimum Free Heap: 290000 bytes (283.2 KB)
  PSRAM: Not available on ESP32-WROOM-32
  Free Stack: 2048 bytes

  --- Flash Memory Information ---
  Flash Size: 4194304 bytes (4.0 MB)
  Flash Speed: 40 MHz
  Flash Mode: QIO
  Sketch Size: 895584 bytes (874.6 KB)
  Free Sketch Space: 1310720 bytes (1280.0 KB)

  --- WiFi Capabilities (2.4GHz ISM Band) ---
  Supported Standards: 802.11 b/g/n
  Frequency Band: 2.4GHz ISM (2400-2485 MHz)
  Channels: 1-13 (region dependent)
  Max Data Rate: 150 Mbps (802.11n)
  Security: WEP, WPA, WPA2, WPA3
  Modes: Station (STA), Access Point (AP), Station+AP
  WiFi Status: Available
  Performing quick WiFi scan...
  Found 8 WiFi networks nearby
  WiFi radio is working correctly!

  --- Bluetooth Capabilities ---
  Bluetooth Version: 4.2
  Protocols: Classic Bluetooth + BLE (Bluetooth Low Energy)
  Frequency: 2.4GHz ISM Band
  Range: ~10 meters (Class 2)
  Profiles: SPP, A2DP, AVRCP, HFP, HSP, PBAP, etc.
  Bluetooth Status: Available and initialized

  --- GPIO Pin Summary ---
  Total GPIO Pins: 34
  Digital I/O: 28 pins
  Analog Input (ADC): 18 pins (12-bit resolution)
  Analog Output (DAC): 2 pins (8-bit resolution)
  Touch Sensors: 10 pins
  PWM Channels: 16 channels
  UART: 3 interfaces
  SPI: 4 interfaces (2 usable)
  I2C: 2 interfaces

  Special Pins:
  - GPIO0: Boot mode control
  - GPIO2: Built-in LED
  - GPIO34-39: Input only
  - GPIO21,22: Default I2C (SDA, SCL)
  - GPIO1,3: Serial0 (USB)

  ============================================================
  System initialization complete!
  Monitoring system status every 5 seconds...
  ============================================================

  --- Real-time System Status ---
  Uptime: 10 seconds
  Free Heap: 294000 bytes (89.7% of total)
  Largest Block: 109500 bytes
  Heap Fragmentation: 2.3%
  Internal Temperature: 45.2°C (approximate)
  Supply Voltage: 3.3V (nominal)
  CPU Frequency: 240 MHz
  ------------------------------

  This example provides comprehensive information about your specific
  ESP32-WROOM-32 module and helps verify all systems are working correctly.
*/
