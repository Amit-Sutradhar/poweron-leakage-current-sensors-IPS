📊 ADS1115 Multi-Channel Voltage & Leakage Current Measurement

This project uses an ESP32 + ADS1115 ADC + TCA9548A I2C Multiplexer to measure low-level analog voltages and convert them into leakage current values using a calibration lookup table.

🚀 Features
✅ Reads 4 analog channels using ADS1115
✅ Supports multiple ADCs via TCA9548A I2C multiplexer
✅ High-resolution measurement using GAIN_EIGHT (±0.512V)
✅ Converts voltage → leakage current using linear interpolation
✅ Serial output for real-time monitoring
✅ Designed for low-voltage sensing applications (0–0.5V range)
🧠 Working Principle
ESP32 communicates with ADS1115 via I2C
TCA9548A selects the active I2C channel
ADS1115 reads analog voltage (high resolution mode)
Voltage is mapped to leakage current using a calibration table
Data is printed on Serial Monitor
🔌 Hardware Required
ESP32 (S3 / WROOM / any variant)
ADS1115 (16-bit ADC)
TCA9548A (I2C Multiplexer)
Leakage current sensor / analog voltage source
Connecting wires
🧩 Circuit Connections
I2C Connections
ESP32	TCA9548A
SDA (GPIO 20)	SDA
SCL (GPIO 21)	SCL
ADS1115 (via TCA Channel 0)
ADS1115	Connection
VCC	3.3V
GND	GND
SDA	TCA Channel SDA
SCL	TCA Channel SCL
⚙️ Configuration
I2C Addresses
#define TCA_ADDR 0x70
#define ADS_ADDR 0x48
Gain Setting
ads.setGain(GAIN_EIGHT); // ±0.512V

✔ Best for low voltage signals (0–0.5V)
✔ Resolution ≈ 0.015625 mV per bit

📈 Calibration Table

Voltage is converted to leakage current using predefined lookup tables:

const float voltTable[] = { ... };
const float currTable[] = { ... };
Uses linear interpolation
Easily customizable for your sensor
🖥️ Serial Output Example
CH0 | V: 0.1352 V | Leakage: 0.401 A
CH1 | V: 0.2481 V | Leakage: 1.198 A
CH2 | V: 0.3675 V | Leakage: 1.602 A
CH3 | V: 0.4800 V | Leakage: 2.000 A
-----------------------------
🛠️ Installation
Install Arduino IDE / PlatformIO
Install required library:
Adafruit ADS1X15
Upload the code to ESP32
📌 Important Notes
⚠️ Maximum measurable voltage = 0.512V (due to gain setting)
⚠️ Higher voltage will saturate and clamp at ~0.512V
⚠️ Ensure proper signal conditioning before ADC input
⚠️ TCA channel must be selected before accessing ADS
🔧 Customization

You can:

Add multiple ADS1115 modules using different TCA channels
Modify calibration table for different sensors
Change gain based on voltage range
💡 Future Improvements
SD card data logging
Cloud integration (MQTT / HTTP)
Real-time dashboard
Auto calibratio
