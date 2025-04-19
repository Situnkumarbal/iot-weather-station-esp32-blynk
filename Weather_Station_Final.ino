// === Blynk IoT Template Settings ===
#define BLYNK_TEMPLATE_ID "TMPL3XYhfHBGx"
#define BLYNK_TEMPLATE_NAME "Simple Weather Station"
#define BLYNK_AUTH_TOKEN "hYARpjigLBexbseP77cGQ4h-v6eIZjI3"

// === Include Libraries ===
#include <WiFi.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// === I2C Buses ===
TwoWire I2C_BMP = TwoWire(1);  // BMP280 uses Wire1

// === Pin Definitions ===
#define DHTPIN 32
#define DHTTYPE DHT11
#define RELAY_PIN 5

// BMP280 I2C Pins (Wire1)
#define BMP_SDA 18
#define BMP_SCL 19

// LCD I2C Pins (default Wire)
#define LCD_SDA 21
#define LCD_SCL 22

// === Create Sensor Objects ===
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp(&I2C_BMP);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust address if needed

BlynkTimer timer;

// === WiFi Credentials ===
char ssid[] = "iQOO Neo7";
char pass[] = "7205970715";

// === Virtual Pins ===
#define VPIN_TEMP V0
#define VPIN_HUMIDITY V1
#define VPIN_ALTITUDE V3
#define VPIN_PRESSURE V4

// === Cache Values ===
float lastTemp = 0, lastHumidity = 0;
float lastPressure = 0, lastAltitude = 0;

// === Sensor Setup Function ===
void setupSensors() {
  dht.begin();
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
  } else {
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
    Serial.println("BMP280 ready.");
  }
}

// === DHT11 Data Sending Function ===
void sendDHTData() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  if (!isnan(temp) && !isnan(humid)) {
    if (abs(temp - lastTemp) > 0.1 || abs(humid - lastHumidity) > 0.1) {
      lastTemp = temp;
      lastHumidity = humid;

      Blynk.virtualWrite(VPIN_TEMP, temp);
      Blynk.virtualWrite(VPIN_HUMIDITY, humid);

      lcd.setCursor(0, 0);
      lcd.print("T:");
      lcd.print(temp, 1);
      lcd.print("C H:");
      lcd.print(humid, 0);
      lcd.print("%  ");

      digitalWrite(RELAY_PIN, temp > 30 ? HIGH : LOW);
    }
  }
}

// === BMP280 Data Sending Function ===
void sendBMPData() {
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);

  if (abs(pressure - lastPressure) > 0.1 || abs(altitude - lastAltitude) > 0.1) {
    lastPressure = pressure;
    lastAltitude = altitude;

    Blynk.virtualWrite(VPIN_PRESSURE, pressure);
    Blynk.virtualWrite(VPIN_ALTITUDE, altitude);

    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(pressure, 1);
    lcd.print(" A:");
    lcd.print(altitude, 0);
    lcd.print("m ");
  }
}

// === Read All Sensors ===
void readSensors() {
  sendDHTData();
  sendBMPData();
  Serial.println("Sensor data sent.");
}

// === Setup ===
void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);

  // Start LCD I2C (default Wire, on pins 21 & 22)
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Start BMP I2C (Wire1)
  I2C_BMP.begin(BMP_SDA, BMP_SCL);

  setupSensors();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, readSensors);
}

// === Main Loop ===
void loop() {
  Blynk.run();
  timer.run();
}
