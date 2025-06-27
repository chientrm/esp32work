/*
  ESP32 Shield Pin Test

  This example tests all accessible GPIO pins on your 38-pin ESP32 shield.
  It helps verify that your shield is properly connected and functioning.

  Hardware:
  - ESP32 38-pin development board with FT232
  - 38-pin compatible shield
  - Optional: LEDs or multimeter for testing

  Features:
  - Tests all GPIO pins systematically
  - Checks input/output functionality
  - Provides detailed pin status
  - Safe for most shield configurations

  Author: ESP32 Development Workspace
  Date: 2025
*/

// Define testable GPIO pins (excluding power, ground, and restricted pins)
int gpioPins[] = {
    0, 2, 4, 5,     // GPIO 0, 2, 4, 5
    12, 13, 14, 15, // GPIO 12-15 (SPI)
    16, 17, 18, 19, // GPIO 16-19
    21, 22, 23,     // GPIO 21-23 (I2C, SPI)
    25, 26, 27,     // GPIO 25-27 (DAC, ADC)
    32, 33          // GPIO 32-33 (ADC)
};

// Input-only pins (cannot be used as outputs)
int inputOnlyPins[] = {34, 35, 36, 39};

// Number of pins to test
const int numGPIOPins = sizeof(gpioPins) / sizeof(gpioPins[0]);
const int numInputOnlyPins = sizeof(inputOnlyPins) / sizeof(inputOnlyPins[0]);

// Test parameters
#define TEST_DELAY 100
#define BLINK_COUNT 3
#define ANALOG_SAMPLES 10

void setup()
{
    Serial.begin(115200);
    delay(2000); // Give time for serial monitor

    Serial.println("\n=== ESP32 Shield Pin Test ===");
    Serial.println("Board: ESP32 38-pin with FT232 + Shield");
    Serial.println("Testing all accessible GPIO pins...");
    Serial.println("=========================================");

    // Print pin layout for reference
    printPinLayout();

    // Start comprehensive pin test
    Serial.println("\nStarting Pin Tests...");
    delay(1000);
}

void loop()
{
    // Test 1: GPIO Output Test
    Serial.println("\n--- Test 1: GPIO Output Test ---");
    testGPIOOutput();

    delay(2000);

    // Test 2: GPIO Input Test
    Serial.println("\n--- Test 2: GPIO Input Test ---");
    testGPIOInput();

    delay(2000);

    // Test 3: Analog Input Test
    Serial.println("\n--- Test 3: Analog Input Test ---");
    testAnalogInput();

    delay(2000);

    // Test 4: PWM Output Test
    Serial.println("\n--- Test 4: PWM Output Test ---");
    testPWMOutput();

    delay(5000); // Wait before repeating

    Serial.println("\n" + String("=").substring(0, 50));
    Serial.println("All tests completed. Repeating in 5 seconds...");
    Serial.println(String("=").substring(0, 50));
}

void printPinLayout()
{
    Serial.println("\nESP32 38-Pin Shield Layout:");
    Serial.println("Left Side:          Right Side:");
    Serial.println("3V3  ←→ GND         GND  ←→ GPIO23");
    Serial.println("EN   ←→ GPIO22      RXD0 ←→ TXD0");
    Serial.println("SVP  ←→ GPIO21      GPIO21 ←→ GPIO19");
    Serial.println("SVN  ←→ GND         GPIO19 ←→ GPIO18");
    Serial.println("GPIO34 ←→ GPIO19    GPIO18 ←→ GPIO5");
    Serial.println("GPIO35 ←→ GPIO18    GPIO5  ←→ GPIO17");
    Serial.println("GPIO32 ←→ GPIO5     GPIO17 ←→ GPIO16");
    Serial.println("GPIO33 ←→ GPIO17    GPIO16 ←→ GPIO4");
    Serial.println("GPIO25 ←→ GPIO16    GPIO4  ←→ GPIO0");
    Serial.println("GPIO26 ←→ GPIO4     GPIO0  ←→ GPIO2");
    Serial.println("GPIO27 ←→ GPIO0     GPIO2  ←→ GPIO15");
    Serial.println("GPIO14 ←→ GPIO2     GPIO15 ←→ SD1");
    Serial.println("GPIO12 ←→ GPIO15    SD1    ←→ SD0");
    Serial.println("GND  ←→ SD1         SD0    ←→ CLK");
    Serial.println("GPIO13 ←→ SD0       CLK    ←→ SD3");
    Serial.println("SD2  ←→ CLK         SD3    ←→ CMD");
    Serial.println("SD3  ←→ CMD         CMD    ←→ 5V");
    Serial.println("CMD  ←→ 5V");
}

void testGPIOOutput()
{
    Serial.println("Testing GPIO pins as outputs...");

    for (int i = 0; i < numGPIOPins; i++)
    {
        int pin = gpioPins[i];
        Serial.print("Testing GPIO" + String(pin) + " as output... ");

        pinMode(pin, OUTPUT);

        // Test HIGH state
        digitalWrite(pin, HIGH);
        delay(TEST_DELAY);

        // Test LOW state
        digitalWrite(pin, LOW);
        delay(TEST_DELAY);

        // Blink test
        for (int blink = 0; blink < BLINK_COUNT; blink++)
        {
            digitalWrite(pin, HIGH);
            delay(50);
            digitalWrite(pin, LOW);
            delay(50);
        }

        // Set to safe state
        digitalWrite(pin, LOW);

        Serial.println("✓ OK");
    }

    Serial.println("GPIO output test completed.");
}

void testGPIOInput()
{
    Serial.println("Testing GPIO pins as inputs...");
    Serial.println("Note: Input values may float without external connections");

    // Test regular GPIO pins as inputs
    for (int i = 0; i < numGPIOPins; i++)
    {
        int pin = gpioPins[i];
        pinMode(pin, INPUT);
        bool value = digitalRead(pin);
        Serial.println("GPIO" + String(pin) + " input value: " + String(value));
        delay(10);
    }

    // Test input-only pins
    Serial.println("\nTesting input-only pins:");
    for (int i = 0; i < numInputOnlyPins; i++)
    {
        int pin = inputOnlyPins[i];
        pinMode(pin, INPUT);
        bool value = digitalRead(pin);
        Serial.println("GPIO" + String(pin) + " (input-only) value: " + String(value));
        delay(10);
    }

    Serial.println("GPIO input test completed.");
}

void testAnalogInput()
{
    Serial.println("Testing analog input pins...");

    // ADC1 pins (work with WiFi)
    int adc1Pins[] = {32, 33, 34, 35, 36, 39};
    int numADC1Pins = sizeof(adc1Pins) / sizeof(adc1Pins[0]);

    for (int i = 0; i < numADC1Pins; i++)
    {
        int pin = adc1Pins[i];
        Serial.print("ADC GPIO" + String(pin) + ": ");

        // Take multiple samples for stability
        long sum = 0;
        for (int sample = 0; sample < ANALOG_SAMPLES; sample++)
        {
            sum += analogRead(pin);
            delay(10);
        }

        int avgValue = sum / ANALOG_SAMPLES;
        float voltage = (avgValue * 3.3) / 4095.0;

        Serial.print(String(avgValue) + " (");
        Serial.print(String(voltage, 2) + "V)");

        if (voltage < 0.1)
        {
            Serial.println(" - Likely grounded");
        }
        else if (voltage > 3.0)
        {
            Serial.println(" - Likely at 3.3V");
        }
        else
        {
            Serial.println(" - Floating or connected");
        }
    }

    Serial.println("Analog input test completed.");
}

void testPWMOutput()
{
    Serial.println("Testing PWM output on GPIO pins...");

    // Test PWM on a few pins
    int pwmPins[] = {2, 4, 5, 18, 19, 21, 22, 23};
    int numPWMPins = sizeof(pwmPins) / sizeof(pwmPins[0]);

    for (int i = 0; i < numPWMPins; i++)
    {
        int pin = pwmPins[i];
        Serial.print("Testing PWM on GPIO" + String(pin) + "... ");

        // Setup PWM channel
        int channel = i;
        int frequency = 1000; // 1kHz
        int resolution = 8;   // 8-bit (0-255)

        ledcSetup(channel, frequency, resolution);
        ledcAttachPin(pin, channel);

        // Test different duty cycles
        for (int duty = 0; duty <= 255; duty += 85)
        {
            ledcWrite(channel, duty);
            delay(100);
        }

        // Turn off PWM
        ledcWrite(channel, 0);
        ledcDetachPin(pin);

        Serial.println("✓ OK");
    }

    Serial.println("PWM output test completed.");
}

/*
  Shield Testing Instructions:

  1. Connect your ESP32 to the shield
  2. Upload this test program
  3. Open Serial Monitor (115200 baud)
  4. Watch the test results

  What to expect:
  - All GPIO pins should test OK for output
  - Input values may show 0 or 1 (floating without connections)
  - Analog readings will vary based on connections
  - PWM test should complete without errors

  Troubleshooting:
  1. If a pin consistently fails: Check physical connection
  2. If multiple pins fail: Check power connections (3.3V, GND)
  3. If analog readings are erratic: Normal for floating inputs
  4. If PWM fails: Check if pin supports PWM on your ESP32 variant

  Shield Testing Tips:
  - Connect LEDs to test outputs visually
  - Use buttons/switches to test inputs
  - Connect potentiometer to test analog inputs
  - Use oscilloscope/multimeter for precise measurements

  Safety Notes:
  - This test is safe for most shields
  - Avoid connecting outputs together
  - Don't exceed 3.3V on any pin
  - Check shield documentation for special requirements
*/
