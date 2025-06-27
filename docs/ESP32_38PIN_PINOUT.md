# ESP32 38-Pin Development Board Pinout

This document provides the complete pin mapping for your 38-pin ESP32 development board with FT232 USB-to-serial converter.

## Board Layout

```
ESP32 38-Pin Development Board
┌─────────────────────────────────────┐
│  [USB]                          [EN]│ ← Reset button
│                                     │
│  [BOOT]                             │ ← Boot/Flash button
│                                     │
│                                     │
│  ┌─────────────────────────────┐    │
│  │                             │    │
│  │        ESP32-WROOM-32       │    │
│  │                             │    │
│  └─────────────────────────────┘    │
│                                     │
│ 3V3  ○○ GND                         │
│ EN   ○○ GPIO23                      │
│ SVP  ○○ GPIO22                      │
│ SVN  ○○ TXD0                        │
│ GPIO34 ○○ RXD0                      │
│ GPIO35 ○○ GPIO21                    │
│ GPIO32 ○○ GND                       │
│ GPIO33 ○○ GPIO19                    │
│ GPIO25 ○○ GPIO18                    │
│ GPIO26 ○○ GPIO5                     │
│ GPIO27 ○○ GPIO17                    │
│ GPIO14 ○○ GPIO16                    │
│ GPIO12 ○○ GPIO4                     │
│ GND  ○○ GPIO0                       │
│ GPIO13 ○○ GPIO2                     │
│ SD2  ○○ GPIO15                      │
│ SD3  ○○ SD1                         │
│ CMD  ○○ SD0                         │
│ 5V   ○○ CLK                         │
└─────────────────────────────────────┘
```

## Pin Definitions

### Power Pins

| Pin | Description         | Voltage | Max Current |
| --- | ------------------- | ------- | ----------- |
| 3V3 | 3.3V Power Supply   | 3.3V    | 600mA       |
| 5V  | 5V Power (from USB) | 5V      | 500mA       |
| GND | Ground              | 0V      | -           |
| EN  | Enable (Reset)      | 3.3V    | -           |

### GPIO Pins (Digital I/O)

| GPIO   | Pin Label | Features                      | Notes                |
| ------ | --------- | ----------------------------- | -------------------- |
| GPIO0  | GPIO0     | Boot Mode, Touch0, ADC2_CH1   | Pull-up, Boot button |
| GPIO2  | GPIO2     | Touch2, ADC2_CH2, LED_BUILTIN | Internal LED         |
| GPIO4  | GPIO4     | Touch0, ADC2_CH0              |                      |
| GPIO5  | GPIO5     | Touch5, ADC1_CH5              |                      |
| GPIO12 | GPIO12    | Touch5, ADC2_CH5, HSPI_MISO   | Boot voltage         |
| GPIO13 | GPIO13    | Touch4, ADC2_CH4, HSPI_MOSI   |                      |
| GPIO14 | GPIO14    | Touch6, ADC2_CH6, HSPI_CLK    |                      |
| GPIO15 | GPIO15    | Touch3, ADC2_CH3, HSPI_SS     | Boot voltage         |
| GPIO16 | GPIO16    |                               |                      |
| GPIO17 | GPIO17    |                               |                      |
| GPIO18 | GPIO18    | VSPI_CLK                      |                      |
| GPIO19 | GPIO19    | VSPI_MISO                     |                      |
| GPIO21 | GPIO21    | I2C_SDA                       |                      |
| GPIO22 | GPIO22    | I2C_SCL                       |                      |
| GPIO23 | GPIO23    | VSPI_MOSI                     |                      |
| GPIO25 | GPIO25    | DAC1, ADC2_CH8                |                      |
| GPIO26 | GPIO26    | DAC2, ADC2_CH9                |                      |
| GPIO27 | GPIO27    | Touch7, ADC2_CH7              |                      |

### ADC Pins (Analog Input)

| GPIO         | ADC Channel | Max Voltage | Resolution |
| ------------ | ----------- | ----------- | ---------- |
| GPIO32       | ADC1_CH4    | 3.3V        | 12-bit     |
| GPIO33       | ADC1_CH5    | 3.3V        | 12-bit     |
| GPIO34       | ADC1_CH6    | 3.3V        | 12-bit     |
| GPIO35       | ADC1_CH7    | 3.3V        | 12-bit     |
| SVP (GPIO36) | ADC1_CH0    | 3.3V        | 12-bit     |
| SVN (GPIO39) | ADC1_CH3    | 3.3V        | 12-bit     |

### Serial Communication

| Pin  | Function | Description             |
| ---- | -------- | ----------------------- |
| TXD0 | UART0 TX | Serial transmit (GPIO1) |
| RXD0 | UART0 RX | Serial receive (GPIO3)  |

### SPI Interface Pins

| Interface | CLK    | MISO   | MOSI   | SS     |
| --------- | ------ | ------ | ------ | ------ |
| HSPI      | GPIO14 | GPIO12 | GPIO13 | GPIO15 |
| VSPI      | GPIO18 | GPIO19 | GPIO23 | GPIO5  |

### I2C Interface Pins

| Function | Default Pin | Alternative Pins |
| -------- | ----------- | ---------------- |
| SDA      | GPIO21      | Any GPIO         |
| SCL      | GPIO22      | Any GPIO         |

## Shield Compatibility

### 38-Pin Shield Connector

Your shield should align with the ESP32 board's 38-pin layout. Ensure proper orientation before connecting.

### Shield Pin Usage Guidelines

1. **Power Supply**: Shield can use 3.3V or 5V depending on requirements
2. **GPIO Conflicts**: Check shield schematic for pin usage conflicts
3. **Pull-up/Pull-down**: Some pins have internal pull-ups (GPIO0, GPIO2, etc.)
4. **Boot Pins**: Avoid using GPIO0, GPIO2, GPIO12, GPIO15 for shield inputs during boot

### Common Shield Features

- **LED Arrays**: Use GPIO2, GPIO4, GPIO5, GPIO16-19, GPIO21-23
- **Sensors**: Use ADC pins (GPIO32-36, GPIO39) for analog sensors
- **Motors**: Use PWM-capable pins for motor control
- **Displays**: Use SPI (GPIO18, GPIO19, GPIO23) or I2C (GPIO21, GPIO22)

## Programming Notes

### Pin Configuration Examples

```cpp
// Digital Output
pinMode(GPIO2, OUTPUT);
digitalWrite(GPIO2, HIGH);

// Digital Input with Pull-up
pinMode(GPIO4, INPUT_PULLUP);
bool state = digitalRead(GPIO4);

// Analog Input
int value = analogRead(GPIO32);

// PWM Output
ledcSetup(0, 5000, 8);  // Channel 0, 5kHz, 8-bit
ledcAttachPin(GPIO2, 0);
ledcWrite(0, 128);  // 50% duty cycle
```

### Important Considerations

1. **Input-only pins**: GPIO34, GPIO35, GPIO36, GPIO39 are input-only
2. **Boot behavior**: Some pins affect boot mode; use carefully
3. **ADC2 limitation**: ADC2 pins cannot be used when WiFi is active
4. **Touch pins**: Can be used for capacitive touch sensing

## FT232 USB Interface

### USB-to-Serial Converter

- **Chip**: FT232RL (FTDI)
- **Baud Rates**: 300 to 3,000,000 bps
- **Default**: 115200 bps
- **Data Bits**: 7 or 8
- **Stop Bits**: 1 or 2
- **Parity**: None, Even, Odd

### Auto-Reset Circuit

The FT232 provides automatic reset functionality:

- DTR → EN (Reset)
- RTS → GPIO0 (Boot mode)

This allows seamless programming without manual button pressing.

## Troubleshooting

### Common Pin Issues

1. **Pin not responding**: Check if it's input-only or has boot constraints
2. **Analog reading unstable**: Use averaging or check for noise
3. **I2C not working**: Verify pull-up resistors (usually 4.7kΩ)
4. **SPI communication issues**: Check wiring and clock polarity

### Pin Testing Code

```cpp
// Test all GPIO pins
void testAllPins() {
  int testPins[] = {0, 2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27};

  for (int i = 0; i < sizeof(testPins)/sizeof(testPins[0]); i++) {
    pinMode(testPins[i], OUTPUT);
    digitalWrite(testPins[i], HIGH);
    delay(100);
    digitalWrite(testPins[i], LOW);
    delay(100);
  }
}
```
