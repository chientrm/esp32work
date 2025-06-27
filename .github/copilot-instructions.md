# ESP32 Development Instructions

<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

## Project Context

This is an ESP32 development workspace for a 38-pin ESP32 development board with FT232 USB-to-serial converter and compatible shield.

## Hardware Specifications

- **ESP32 Module**: ESP32-WROOM-32 (marked as "2Y-ESP32")
- **Board**: 38-pin ESP32 development board
- **USB Converter**: FT232 (FTDI)
- **Shield**: 38-pin compatible expansion shield
- **WiFi**: 802.11 b/g/n, 2.4GHz ISM band
- **Bluetooth**: 4.2 + BLE (Bluetooth Low Energy)
- **Flash**: 4MB
- **SRAM**: 520KB
- **Development Environment**: Arduino IDE + PlatformIO

- **Board**: 38-pin ESP32 development board
- **USB Converter**: FT232 (FTDI)
- **Shield**: 38-pin compatible expansion shield
- **Development Environment**: Arduino IDE + PlatformIO

## Code Generation Guidelines

When generating code for this workspace:

1. **Target Platform**: Use ESP32-specific libraries and functions
2. **Pin Mapping**: Refer to the 38-pin ESP32 pinout (documented in docs/)
3. **Serial Communication**: Use FT232-compatible baud rates (typically 115200)
4. **Libraries**: Prefer ESP32 native libraries over generic Arduino libraries when available
5. **Power Management**: Consider ESP32 sleep modes and power optimization
6. **WiFi/Bluetooth**: Utilize ESP32's built-in wireless capabilities
7. **Shield Compatibility**: Ensure GPIO usage is compatible with the 38-pin shield

## Development Practices

- Use proper error handling for WiFi connections
- Implement watchdog timers for stability
- Follow ESP32 best practices for interrupt handling
- Use appropriate delay functions (delay() vs vTaskDelay())
- Consider memory management (heap fragmentation)

## Common Libraries to Use

- WiFi.h (for WiFi functionality)
- BluetoothSerial.h (for Bluetooth)
- SPIFFS.h or LittleFS.h (for file system)
- ESP32Servo.h (for servo control)
- AsyncTCP.h and ESPAsyncWebServer.h (for web servers)
