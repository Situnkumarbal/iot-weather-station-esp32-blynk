#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === I2C Pins ===
#define LCD_SDA 21
#define LCD_SCL 22

// === LCD Object ===
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16x2 display

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize LCD
  lcd.begin(16, 2);  // 16 columns, 2 rows
  lcd.backlight();   // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("LCD Test Started");

  delay(2000); // Give time for the user to see the initialization message
  lcd.clear();
}

void loop() {
  // Display text on LCD
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  // Serial output
  Serial.println("Displaying on LCD: Hello, World!");
  
  delay(1000);  // Update every second
}
