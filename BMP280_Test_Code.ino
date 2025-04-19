#include <Wire.h>
#include <Adafruit_BMP280.h>

// === BMP280 I2C Pins (custom Wire1) ===
#define BMP_SDA 18
#define BMP_SCL 19

// === Create I2C Bus and Sensor Object ===
TwoWire I2C_BMP = TwoWire(1);
Adafruit_BMP280 bmp(&I2C_BMP);

void setup() {
  Serial.begin(115200);

  // Initialize I2C for BMP280
  I2C_BMP.begin(BMP_SDA, BMP_SCL);
  
  // Initialize BMP280 sensor
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found! Check wiring or I2C address.");
    while (1);
  }

  Serial.println("BMP280 initialized successfully.");
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  float pressure = bmp.readPressure() / 100.0F;         // hPa
  float altitude = bmp.readAltitude(1013.25);           // meters (adjust sea-level pressure if needed)

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa\t");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  delay(2000);  // Update every 2 seconds
}
