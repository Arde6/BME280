#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Own stuff
#include "Identification.h"

#define SEALEVELPRESSURE_HPA (1013.25)

// Initialize the LCD with the I2C address 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_BME280 bme; // I2C

int id = -1;

void setup() {
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize the BME280 sensor
  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    lcd.print("Sensor Error");
    while (1);
  }

  id = idSetup();
}

void loop() {
  // Read values from the BME280 sensor
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  id =  idSetup();

  // Display the values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000); // Wait for 2 seconds

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P:");
  lcd.print(pressure);
  lcd.print("hPa");

  lcd.setCursor(0, 1);
  lcd.print("ID:");
  lcd.print(id);

  delay(2000); // Wait for 2 seconds
}
