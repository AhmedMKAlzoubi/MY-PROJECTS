#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define SENSOR 2
#define DHTTYPE DHT11

DHT dht(SENSOR,DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  
  dht.begin();

  lcd.init();
  lcd.backlight();
  
  
 
}

void loop() {

  lcd.setCursor(0,0);
  lcd.print("Temp: ");

  float TEMP = dht.readTemperature();
  
  lcd.setCursor(9,0);
  lcd.print(TEMP);

  lcd.setCursor(14,0);
  lcd.print("C");


  lcd.setCursor(0,1);
  lcd.print("Humidity: ");

  float HUMI = dht.readHumidity();

  lcd.setCursor(9,1);
  lcd.print(HUMI);

  lcd.setCursor(14,1);
  lcd.print("%");

  delay(3000);
  lcd.clear();
}