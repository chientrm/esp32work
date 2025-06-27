/*
  ESP32-WROOM-32 WiFi Scanner

  Scans for available WiFi networks and displays information
  about signal strength, encryption, and channels.
*/

#include <Arduino.h>
#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("ESP32 WiFi Scanner");
    Serial.println("==================");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

void loop()
{
    Serial.println("Scanning for WiFi networks...");

    int networkCount = WiFi.scanNetworks();

    if (networkCount == 0)
    {
        Serial.println("No networks found");
    }
    else
    {
        Serial.printf("Found %d networks:\n\n", networkCount);

        // Print header
        Serial.println(" # | SSID                 | RSSI | Ch | Encryption");
        Serial.println("---|----------------------|------|----|-----------");

        for (int i = 0; i < networkCount; i++)
        {
            String encryption = "";
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                encryption = "Open";
                break;
            case WIFI_AUTH_WEP:
                encryption = "WEP";
                break;
            case WIFI_AUTH_WPA_PSK:
                encryption = "WPA";
                break;
            case WIFI_AUTH_WPA2_PSK:
                encryption = "WPA2";
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                encryption = "WPA/WPA2";
                break;
            default:
                encryption = "Unknown";
                break;
            }

            Serial.printf("%2d | %-20s | %4d | %2d | %s\n",
                          i + 1,
                          WiFi.SSID(i).c_str(),
                          WiFi.RSSI(i),
                          WiFi.channel(i),
                          encryption.c_str());
        }
    }

    WiFi.scanDelete();

    Serial.println("\nNext scan in 10 seconds...\n");
    delay(10000);
}
