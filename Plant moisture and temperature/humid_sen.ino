#include <LiquidCrystal.h>
#include <dht.h>

#define dht_apin A0 
dht DHT;
 
//moisture
int sensorPin = A1; 
int sensorValue;
//Threshold values
int lowtemp=20;
int hightemp=30;
int lowwater=1010;
int highwater=400;
//LCD  
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte eye1[] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110
};
byte eye2[] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110
};
byte sm1[] = {
  B10000,
  B10000,
  B11000,
  B01100,
  B00111,
  B00011,
  B00001,
  B00000
};
byte sm2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000
};
byte sm3[] = {
  B00001,
  B00001,
  B00011,
  B00011,
  B00110,
  B11100,
  B11000,
  B00000
};

void setup(){
 
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(500);
  lcd.createChar(5, eye1);
  lcd.createChar(6, eye2);
  lcd.createChar(7, sm1);
  lcd.createChar(8, sm2);
  lcd.createChar(9, sm3);
  lcd.home();
  
 
}
void loop(){
  lcd.clear();
  //Start of Program 
    DHT.read11(dht_apin);
    sensorValue = analogRead(sensorPin);

  //For serial print purpose
    Serial.println("-------------------");
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.println("% ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature);
    Serial.println("C");
    Serial.print("Analog Value:");
    Serial.print(sensorValue);

    
  //For actual sensor value reading
    if(sensorValue<lowwater && sensorValue>highwater){
            if(DHT.temperature>lowtemp && DHT.temperature<hightemp){
                  lcd.setCursor(6,0);
                  lcd.write(5);
                  lcd.setCursor(8,0);
                  lcd.write(6);
                  //smile
                  lcd.setCursor(6,1);
                  lcd.write(7);
                  lcd.setCursor(7,1);
                  lcd.write(8);
                  lcd.setCursor(8,1);
                  lcd.write(9); 
                  delay(1000);
            }
            else{
                  if(DHT.temperature>hightemp){
                      lcd.clear();
                      lcd.setCursor(5,0);
                      lcd.print("WARNING");
                      lcd.setCursor(0,1);
                      lcd.print("HIGH TEMPERATURE");
                      lcd.print("!");
                      delay(1000);
                  }
                  else{
                      lcd.clear();
                      lcd.setCursor(5,0);
                      lcd.print("WARNING");
                      lcd.setCursor(0,1);
                      lcd.print("LOW TEMPERATURE");
                      lcd.print("!");
                      delay(1000);
                  }
        }
       }
    else{
              if(sensorValue<highwater){
                    lcd.clear();
                    lcd.setCursor(5,0);
                    lcd.print("WARNING");
                    lcd.setCursor(4,1);
                    lcd.print("MORE WATER");
                    lcd.print("!");
                    delay(1000);
                    
                  }
            else{
                    lcd.clear();
                    lcd.setCursor(5,0);
                    lcd.print("WARNING");
                    lcd.setCursor(4,1);
                    lcd.print("LESS WATER");
                    lcd.print("!");
                    delay(1000);
                 }
    }
    
    delay(4000);
}
