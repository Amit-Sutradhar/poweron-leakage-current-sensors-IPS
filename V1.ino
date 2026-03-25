#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// ================= I2C =================
#define SDA_PIN 20
#define SCL_PIN 21

// ================= TCA / ADS ===========
#define TCA_ADDR 0x70
#define ADS_ADDR 0x48
Adafruit_ADS1115 ads;

// ================= TCA SELECT ==========
void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

// ================= LEAKAGE CAL =========
const float voltTable[] = {
  0.000, 0.124, 0.135, 0.148, 0.186, 0.213,
  0.250, 0.300, 0.367, 0.449, 0.480
};

const float currTable[] = {
  0.0, 0.2, 0.4, 0.6, 0.8, 1.0,
  1.2, 1.4, 1.6, 1.8, 2.0
};

const int tableSize = sizeof(voltTable) / sizeof(voltTable[0]);

float voltageToCurrent(float v) {
  if (v <= voltTable[0]) return currTable[0];
  if (v >= voltTable[tableSize - 1]) return currTable[tableSize - 1];

  for (int i = 0; i < tableSize - 1; i++) {
    if (v >= voltTable[i] && v <= voltTable[i + 1]) {
      float slope =
        (currTable[i + 1] - currTable[i]) /
        (voltTable[i + 1] - voltTable[i]);
      return currTable[i] + slope * (v - voltTable[i]);
    }
  }
  return 0.0;
}

// ================= SETUP ===============
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ADC VOLTAGE + LEAKAGE");

  Wire.begin(SDA_PIN, SCL_PIN);

  // TCA check
  Wire.beginTransmission(TCA_ADDR);
  if (Wire.endTransmission() != 0) {
    Serial.println("TCA9548A NOT FOUND");
    while (1);
  }

  tcaSelect(0);

  if (!ads.begin(ADS_ADDR)) {
    Serial.println("ADS1115 NOT FOUND");
    while (1);
  }

  // 🔥 Better for your low voltage range
  ads.setGain(GAIN_EIGHT);   // ±0.512V (HIGH resolution)
}

// ================= LOOP =================
void loop() {

  tcaSelect(0);

  for (int ch = 0; ch < 4; ch++) {

    int16_t raw = ads.readADC_SingleEnded(ch);
    if (raw < 0) raw = 0;

    float voltage = ads.computeVolts(raw);
    float leakage = voltageToCurrent(voltage);

    Serial.print("CH");
    Serial.print(ch);

    Serial.print(" | V: ");
    Serial.print(voltage, 4);
    Serial.print(" V");

    Serial.print(" | Leakage: ");
    Serial.print(leakage, 3);
    Serial.println(" A");
  }

  Serial.println("-----------------------------");
  delay(1000);
},, I WANT TO UPLOAD THAT CIDE ON GITHUB ,, SO CAN YOU WRITE READ ME FILE FOR THAT CODE ,, 