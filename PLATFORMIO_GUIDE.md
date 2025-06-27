# PlatformIO ESP32 Development Commands

## 🚀 Quick Start Commands

### Build Project

```bash
cd project_name/
pio run
```

### Upload to ESP32

```bash
pio run -t upload
```

### Serial Monitor

```bash
pio device monitor
```

### Build + Upload + Monitor (All in one)

```bash
pio run -t upload && pio device monitor
```

## 📁 Available Projects

### 1. basic_blink/

Simple LED blinking test for GPIO2

```bash
cd basic_blink/
pio run -t upload
```

### 2. wifi_scanner/

WiFi network scanner with detailed information

```bash
cd wifi_scanner/
pio run -t upload
pio device monitor
```

### 3. sensor_monitor/

Comprehensive sensor monitoring (analog, touch, temperature)

```bash
cd sensor_monitor/
pio run -t upload
pio device monitor
```

### 4. system_test_project/

System information and hardware testing

```bash
cd system_test_project/
pio run -t upload
pio device monitor
```

## 🔧 Useful PlatformIO Commands

```bash
# Clean build files
pio run -t clean

# List connected devices
pio device list

# Update platforms and libraries
pio update

# Show project info
pio project data

# Install library
pio lib install "library_name"

# Show available boards
pio boards esp32
```

## 🛠️ Development Workflow

1. **Connect ESP32** via USB cable
2. **Choose project** directory
3. **Build**: `pio run`
4. **Upload**: `pio run -t upload`
5. **Monitor**: `pio device monitor` (Ctrl+C to exit)

## 📝 Notes

- All projects use ESP32-WROOM-32 configuration
- Serial baud rate: 115200
- Upload port: Usually `/dev/ttyUSB0`
- Press Ctrl+C to exit serial monitor
- GPIO2 is typically the built-in LED pin
