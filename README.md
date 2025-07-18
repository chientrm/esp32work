# ESP32 Development Workspace

Welcome to your ESP32 development environment! This workspace is set up for **professional ESP32 development using PlatformIO** with your **38-pin ESP32 development board with FT232 USB-to-serial converter** and compatible shield.

## 🛠️ Hardware Setup

### Your ESP32 Board

- **Model**: 38-pin ESP32 Development Board
- **ESP32 Module**: ESP32-WROOM-32 (2Y-ESP32 marking)
- **USB Converter**: FT232 (FTDI)
- **Shield**: 38-pin expansion shield
- **Microcontroller**: ESP32 (Dual-core Xtensa LX6, 240MHz)
- **Memory**: 520KB SRAM, 4MB Flash
- **Connectivity**: WiFi 802.11 b/g/n (2.4GHz ISM band), Bluetooth 4.2 + BLE

## 📁 Project Structure

- `basic_blink/` - Simple LED blinking test project
- `wifi_scanner/` - WiFi network scanning and analysis
- `sensor_monitor/` - Comprehensive sensor monitoring system
- `system_test_project/` - System information and hardware testing
- `platformio_examples/` - Additional PlatformIO project examples
- `docs/` - Hardware documentation and guides

### Pin Configuration

See `docs/ESP32_38PIN_PINOUT.md` for detailed pin mapping and shield compatibility.

## 🚀 Quick Start

### 1. Install Required Software

#### Arduino IDE Method

```bash
# Install Arduino IDE
sudo apt update
sudo apt install arduino

# Add ESP32 board manager URL in Arduino IDE:
# File → Preferences → Additional Board Manager URLs
# Add: https://dl.espressif.com/dl/package_esp32_index.json
```

#### PlatformIO Method (Recommended)

```bash
# Install PlatformIO Core
pip install platformio

# Or use VS Code extension (will be installed automatically)
```

### 2. Driver Setup (FT232)

```bash
# Check if device is detected
lsusb | grep FTDI

# If not detected, install FT232 drivers
sudo apt install libftdi1-2 libftdi1-dev
```

### 3. Build and Upload Your First Program

1. Connect your ESP32 board via USB
2. Navigate to any project directory (e.g., `basic_blink/`)
3. Build and upload:

```bash
cd basic_blink/
pio run -t upload
pio device monitor  # To see serial output
```

## � Available Projects

```
esp32work/
├── basic_blink/              # Simple LED blinking test
├── wifi_scanner/             # WiFi network analysis
├── sensor_monitor/           # Comprehensive sensor monitoring
├── system_test_project/      # System information display
├── platformio_examples/       # PlatformIO projects
│   ├── basic_project/        # PlatformIO basic setup
│   └── advanced_features/    # Advanced ESP32 features
├── shield_examples/          # Shield-specific examples
│   ├── shield_test/          # Test all shield pins
│   └── shield_projects/      # Projects using shield
├── docs/                     # Documentation
│   ├── ESP32_38PIN_PINOUT.md # Pin mapping reference
│   ├── FT232_SETUP.md        # Driver and troubleshooting
│   └── SHIELD_GUIDE.md       # Shield usage guide
└── README.md                 # This file
```

## 🔧 Development Tools

### VS Code Extensions (Auto-installed)

- **PlatformIO IDE**: Complete embedded development
- **Arduino**: Arduino IDE integration
- **C/C++**: Language support
- **Serial Monitor**: Serial communication

### Useful Commands

```bash
# List connected devices
ls /dev/ttyUSB*

# Monitor serial output
screen /dev/ttyUSB0 115200

# PlatformIO commands
pio run                    # Build project
pio run -t upload         # Upload to board
pio device monitor        # Serial monitor
```

## 🌐 ESP32 Features

### WiFi Capabilities

- Station mode (connect to existing WiFi)
- Access Point mode (create WiFi hotspot)
- WiFi Direct and mesh networking

### Bluetooth Features

- Bluetooth Classic
- Bluetooth Low Energy (BLE)
- Serial over Bluetooth

### Peripheral Interfaces

- **GPIO**: 34 programmable pins
- **ADC**: 2 × 12-bit SAR ADCs
- **DAC**: 2 × 8-bit DACs
- **SPI**: 4 × SPI interfaces
- **I2C**: 2 × I2C interfaces
- **UART**: 3 × UART interfaces
- **PWM**: 16 × PWM channels
- **Touch**: 10 × capacitive touch pins

## 📖 Getting Started Examples

1. **Blink LED**: `arduino_examples/01_blink/`
2. **WiFi Connection**: `arduino_examples/02_wifi_connect/`
3. **Sensor Reading**: `arduino_examples/03_sensor_reading/`
4. **Shield Test**: `shield_examples/shield_test/`

## 🔍 Troubleshooting

### Common Issues

1. **Board not detected**: Check USB cable and drivers
2. **Upload failed**: Press and hold BOOT button during upload
3. **Serial monitor blank**: Check baud rate (115200)
4. **Permission denied**: Add user to dialout group

### Useful Links

- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/)
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [PlatformIO ESP32 Guide](https://docs.platformio.org/en/latest/platforms/espressif32.html)

## 🎯 Next Steps

1. **Test your board**: Run the blink example
2. **Explore the shield**: Check pin compatibility
3. **Connect to WiFi**: Try the WiFi examples
4. **Build your project**: Use the examples as templates

Happy coding with your ESP32! 🚀
