#include <DHT.h>

// === Pin Definitions ===
#define DHTPIN 32
#define DHTTYPE DHT11

// === Sensor Object ===
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT11 Test Initialized");
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  if (!isnan(temp) && !isnan(humid)) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humid);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(2000);  // Update every 2 seconds
}
