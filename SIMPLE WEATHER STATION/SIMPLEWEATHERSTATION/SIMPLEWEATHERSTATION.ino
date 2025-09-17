#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTSENSOR 2
#define DHTTYPE DHT11

#define RAINSENSOR A0

DHT dht(DHTSENSOR,DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  
  dht.begin();

  lcd.init();
  lcd.backlight();
  
  
 
}

void loop() {

  float RAINRAWREADING = analogRead(RAINSENSOR);
  float rainINprecentage = map(RAINRAWREADING, 0, 1023, 100, 0);

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

  lcd.setCursor(0,0);
  lcd.print("RAIN: ");
  lcd.setCursor(0,1);
  lcd.print(rainINprecentage);
  lcd.setCursor(4,1);
  lcd.print("%");

  delay(3000);
  lcd.clear();

}