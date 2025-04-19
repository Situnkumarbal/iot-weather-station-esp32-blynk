# iot-weather-station-esp32-blynk
# 🌦️ ESP32-Based IoT Weather Station with Blynk and LCD Display

This project demonstrates a complete IoT-enabled weather monitoring system using the **ESP32**, **DHT11**, **BMP280**, and a **16x2 I2C LCD**. Sensor data is displayed locally on the LCD and remotely on the **Blynk IoT app** in real-time.

## 📌 Features
- Reads temperature and humidity using DHT11
- Measures pressure and altitude using BMP280
- Displays data on 16x2 LCD (I2C)
- Sends live data to Blynk IoT Dashboard
- Controls a relay based on temperature threshold
- Efficient update strategy with minimal network overhead

## 🔧 Hardware Components
| Component         | Quantity |
|------------------|----------|
| ESP32            | 1        |
| DHT11 Sensor     | 1        |
| BMP280 Sensor    | 1        |
| 16x2 LCD (I2C)   | 1        |
| Relay Module     | 1        |
| Jumper Wires     | As needed |

## 🧠 Circuit Connections

### DHT11
- **VCC** → 3.3V  
- **DATA** → GPIO 32  
- **GND** → GND  

### BMP280 (I2C - Wire1)
- **SDA** → GPIO 18  
- **SCL** → GPIO 19  

### LCD (I2C - default Wire)
- **SDA** → GPIO 21  
- **SCL** → GPIO 22  

### Relay
- **IN** → GPIO 5

## 🧪 Virtual Pins (Blynk)
| Data       | Virtual Pin |
|------------|-------------|
| Temperature | V0         |
| Humidity    | V1         |
| Altitude    | V3         |
| Pressure    | V4         |

## 🛠️ Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Situnkumarbal/iot-weather-station-esp32-blynk.git
   cd iot-weather-station-esp32-blynk
