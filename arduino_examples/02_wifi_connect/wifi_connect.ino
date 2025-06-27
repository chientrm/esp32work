/*
  ESP32 WiFi Connection Example

  This example demonstrates how to connect to a WiFi network
  and perform basic network operations.

  Hardware:
  - ESP32 38-pin development board with FT232
  - Built-in WiFi capability

  Features:
  - WiFi connection with retry logic
  - Network information display
  - Connection status monitoring
  - WiFi signal strength monitoring

  Author: ESP32 Development Workspace
  Date: 2025
*/

#include <WiFi.h>

// WiFi credentials - CHANGE THESE!
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

// Connection settings
#define MAX_WIFI_RETRIES 20
#define WIFI_RETRY_DELAY 500
#define STATUS_LED 2

// Timing
unsigned long previousMillis = 0;
const long interval = 10000; // Check status every 10 seconds

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n=== ESP32 WiFi Connection Example ===");
    Serial.println("Board: ESP32 38-pin with FT232");
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    // Initialize status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, LOW);

    // Start WiFi connection
    connectToWiFi();
}

void loop()
{
    unsigned long currentMillis = millis();

    // Check WiFi status periodically
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        checkWiFiStatus();
    }

    // Keep LED on if connected, blink if disconnected
    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(STATUS_LED, HIGH);
    }
    else
    {
        // Blink LED to indicate disconnection
        digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
        delay(250);
    }

    delay(100);
}

void connectToWiFi()
{
    WiFi.mode(WIFI_STA); // Station mode
    WiFi.begin(ssid, password);

    Serial.print("Connecting");
    int retries = 0;

    while (WiFi.status() != WL_CONNECTED && retries < MAX_WIFI_RETRIES)
    {
        delay(WIFI_RETRY_DELAY);
        Serial.print(".");
        retries++;

        // Blink LED during connection attempt
        digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWiFi Connected!");
        printNetworkInfo();
        digitalWrite(STATUS_LED, HIGH);
    }
    else
    {
        Serial.println("\nWiFi Connection Failed!");
        Serial.println("Please check your WiFi credentials and try again.");
        digitalWrite(STATUS_LED, LOW);
    }
}

void printNetworkInfo()
{
    Serial.println("\n--- Network Information ---");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("DNS: ");
    Serial.println(WiFi.dnsIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.print("Channel: ");
    Serial.println(WiFi.channel());
    Serial.println("---------------------------");
}

void checkWiFiStatus()
{
    Serial.print("WiFi Status Check - ");
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.print("s - ");

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("Connected to ");
        Serial.print(WiFi.SSID());
        Serial.print(" | IP: ");
        Serial.print(WiFi.localIP());
        Serial.print(" | RSSI: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    }
    else
    {
        Serial.print("Disconnected (Status: ");
        Serial.print(getWiFiStatusText(WiFi.status()));
        Serial.println(")");

        // Try to reconnect
        Serial.println("Attempting to reconnect...");
        connectToWiFi();
    }
}

String getWiFiStatusText(wl_status_t status)
{
    switch (status)
    {
    case WL_IDLE_STATUS:
        return "Idle";
    case WL_NO_SSID_AVAIL:
        return "No SSID Available";
    case WL_SCAN_COMPLETED:
        return "Scan Completed";
    case WL_CONNECTED:
        return "Connected";
    case WL_CONNECT_FAILED:
        return "Connection Failed";
    case WL_CONNECTION_LOST:
        return "Connection Lost";
    case WL_DISCONNECTED:
        return "Disconnected";
    default:
        return "Unknown";
    }
}

/*
  How to use this example:

  1. Change the WiFi credentials at the top of the file:
     const char* ssid = "YourWiFiName";
     const char* password = "YourWiFiPassword";

  2. Upload the code to your ESP32

  3. Open Serial Monitor (115200 baud)

  Expected Output:
  === ESP32 WiFi Connection Example ===
  Board: ESP32 38-pin with FT232
  Connecting to WiFi: YourWiFiName
  Connecting..........
  WiFi Connected!

  --- Network Information ---
  SSID: YourWiFiName
  IP Address: 192.168.1.100
  Subnet Mask: 255.255.255.0
  Gateway: 192.168.1.1
  DNS: 192.168.1.1
  MAC Address: AA:BB:CC:DD:EE:FF
  Signal Strength (RSSI): -45 dBm
  Channel: 6
  ---------------------------

  WiFi Status Check - Uptime: 10s - Connected to YourWiFiName | IP: 192.168.1.100 | RSSI: -45 dBm

  LED Behavior:
  - Blinking during connection attempt
  - Solid ON when connected
  - Blinking fast when disconnected

  Troubleshooting:
  1. Check WiFi credentials
  2. Ensure WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
  3. Check signal strength (closer to router)
  4. Verify network allows new devices
  5. Try different WiFi channel on your router
*/
