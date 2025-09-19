#include <LiquidCrystal_I2C.h>

#define RIPSENSOR 2
#define INDICATORLEDRED 3
#define INDICATORLEDGREEN 4
#define BUZZERPIN 5
#define PUSHBUTTON 6

LiquidCrystal_I2C lcd(0x27, 16, 2);

int motion = 0;
int RESET = LOW; 

void setup() {
 
 pinMode(RIPSENSOR, INPUT);
 pinMode(INDICATORLEDRED, OUTPUT); 
 pinMode(INDICATORLEDGREEN, OUTPUT);
 pinMode(BUZZERPIN, OUTPUT);
 pinMode(PUSHBUTTON, INPUT);

 lcd.init();
 lcd.backlight();
 lcd.clear();

}

void loop() {

 RESET = digitalRead(PUSHBUTTON);

 motion = digitalRead(RIPSENSOR);

 if (motion == HIGH && RESET == LOW)
 {
//warning mode
 

 digitalWrite(INDICATORLEDGREEN, LOW);
 digitalWrite(INDICATORLEDRED, HIGH);
 digitalWrite(BUZZERPIN, HIGH);

 lcd.clear();

 lcd.setCursor(0,0);
 lcd.print("Warning!");
 lcd.setCursor(0,1);
 lcd.print("Motion Detected!");

 }
 else if(RESET == HIGH)
 {
  //safe mode

 digitalWrite(INDICATORLEDGREEN, HIGH);
 digitalWrite(INDICATORLEDRED, LOW);
 digitalWrite(BUZZERPIN, LOW);

 lcd.clear();

 lcd.setCursor(0,0);
 lcd.print("SAFE");
 lcd.setCursor(0,1);
 lcd.print("No Motion Detected!");

 }
 delay(300);
}
