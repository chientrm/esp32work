# ESP32-WROOM-32 Connection and Test Guide

## 📱 Quick Connection Steps

### 1. Connect Your ESP32 Board

1. **Get your USB cable** - Make sure it's a data cable, not just power
2. **Connect ESP32 to computer**:
   - USB-C or Micro-USB end → Your ESP32 board
   - USB-A end → Your computer
3. **Check power LED** - Should light up on the ESP32 board

### 2. Verify Connection

Run this command to check if detected:

```bash
lsusb | grep -i ftdi
ls /dev/ttyUSB*
```

Expected output:

```
Bus 001 Device 003: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC
/dev/ttyUSB0
```

### 3. Upload System Test

Once connected, you can upload in several ways:

#### Method 1: PlatformIO (Recommended)

```bash
cd system_test_project
pio run --target upload
pio device monitor
```

#### Method 2: VS Code Tasks

- Press `Ctrl+Shift+P`
- Type "Tasks: Run Task"
- Select "PlatformIO: Upload to ESP32"
- Then "PlatformIO: Serial Monitor"

#### Method 3: Arduino IDE

- Open `arduino_examples/03_system_info/system_info.ino`
- Select Board: "ESP32 Dev Module"
- Select Port: "/dev/ttyUSB0"
- Click Upload

## 🔍 What to Expect

### System Information Output

The program will display:

- **Chip identification**: ESP32-D0WDQ6 (your 2Y-ESP32)
- **Memory info**: ~320KB heap, 4MB flash
- **WiFi test**: Scan for nearby networks
- **Bluetooth test**: Initialize BT radio
- **Pin configuration**: All 34 GPIO details

### Real-time Monitoring

Every 5 seconds you'll see:

- Current uptime
- Free memory percentage
- Internal temperature
- System health status

## 🚨 Troubleshooting

### Board Not Detected

1. **Try different USB port**
2. **Check cable** - Must support data transfer
3. **Install drivers**:
   ```bash
   sudo apt install libftdi1-2 libftdi1-dev
   ```
4. **Add user to dialout group**:
   ```bash
   sudo usermod -a -G dialout $USER
   ```
   Then log out and back in.

### Upload Failed

1. **Hold BOOT button** during upload start
2. **Press EN button** to reset, then try upload
3. **Lower upload speed**: Change 921600 to 115200 in platformio.ini
4. **Check permissions**:
   ```bash
   sudo chmod 666 /dev/ttyUSB0
   ```

### No Serial Output

1. **Check baud rate**: Must be 115200
2. **Press EN button** after opening monitor
3. **Try different terminal**: screen, minicom, or PlatformIO monitor

## 📊 Success Indicators

✅ **Hardware Working** if you see:

- Chip model detected correctly
- 4MB flash memory reported
- WiFi networks found nearby
- Bluetooth initializes successfully
- Temperature reading appears

✅ **Development Environment Ready** if:

- Upload completes without errors
- Serial monitor shows output
- Real-time updates every 5 seconds
- No compilation errors

## 🎯 Next Steps After Success

Once the system test passes:

1. **Try the blink example** to test GPIO
2. **Test WiFi connection** with your network
3. **Run shield compatibility test**
4. **Start your own projects**

## 💡 Tips

- Keep this test project - it's useful for troubleshooting
- The system info helps identify counterfeit boards
- Monitor temperature during heavy WiFi/BT usage
- Use this as a baseline for performance comparison

---

**Ready to connect your ESP32-WROOM-32? Let's see what this powerful little board can do!** 🚀
