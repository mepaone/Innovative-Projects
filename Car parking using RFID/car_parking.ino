//project by PAVAN KUMAR 
//for more visit https://github.com/mepaone/Innovative-Projects
//pin configuration

//LCD                              //IR                      //Servo
                             
//Analog Pin 4 - SDA               VCC - 5V                  BROWN ->GND   
//Analog pin 5 - SCL               GND - GND                 RED ->VCC
//5V - Vcc                         OUT - D2                  ORANGE->D3
//GND - GND

//RFID
 
//SDA - Digital 10
//SCK - Digital 13
//MOSI - Digital 11
//MISO - Digital 12
//IRQ - unconnected
//GND - GND
//RST - Digital 9
//3.3V - 3.3V


//program starts
#include <LCD_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <RFID.h>

LCD_I2C lcd(0x27, 16, 2);
RFID rfid(10, 9);

//change your card serial id
byte kart[5] = {98,247,76,58,227};
Servo myservo;
int IR = 2;
int slots=0;
boolean card;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing..");
  lcd.setCursor(0,1);
  lcd.print("RFID ONLINE");
  rfid.init();
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("SENSORS ONLINE");
  pinMode (IR, INPUT);
  delay(2000);
  lcd.clear();
  myservo.attach(3);
  myservo.write(100);
  
}

void loop()
{
  lcd.setCursor(0,0);
      lcd.print("PLACE CARD");
      delay(2000); 
      lcd.clear();
  if (rfid.isCard())
  {
    if (rfid.readCardSerial())
    {
//      open serial monitor and check your card serial number
      lcd.setCursor(0,1);
      lcd.print(rfid.serNum[0]);
      lcd.print(",");
      lcd.print(rfid.serNum[1]);
      lcd.print(",");
      lcd.print(rfid.serNum[2]);
      lcd.print(",");
      lcd.print(rfid.serNum[3]);
      lcd.print(",");
      lcd.println(rfid.serNum[4]);
      
      Serial.print("Found ID: ");
      Serial.print(rfid.serNum[0]);
      Serial.print(",");
      Serial.print(rfid.serNum[1]);
      Serial.print(",");
      Serial.print(rfid.serNum[2]);
      Serial.print(",");
      Serial.print(rfid.serNum[3]);
      Serial.print(",");
      Serial.println(rfid.serNum[4]);

    }
    
    for (int i = 1; i < 5; i++)
    {
      if (rfid.serNum[0] == kart[0] && rfid.serNum[1] == kart[1] && rfid.serNum[2] == kart[2] && rfid.serNum[3] == kart[3] && rfid.serNum[4] == kart[4])
      {
        card = true;
      }
      else {
        card = false;
      }
    }
    if (card == true && !digitalRead(IR) && slots<=4)
    {
      lcd.setCursor(0,0);
      lcd.print("WELCOME");
      Serial.println("Correct Card");
      slots++;
      myservo.write(0);
      delay(1000);
      myservo.write(100);
      lcd.clear();
    }
    else
    {
    
      if(slots>4){
      lcd.setCursor(0,0);
      lcd.print("Sorry! NO SLOTS");
      delay(3000);
      lcd.clear();
      }
      else if(digitalRead(IR)){
          lcd.setCursor(5,0);
          lcd.print("NO");
          lcd.setCursor(0,1);
          lcd.print("VEHICAL DETECTED");
          delay(3000);          
          lcd.clear();
      }
      else{
      lcd.setCursor(0,1);
      lcd.print("Wrong Card");
      delay(2000);
      lcd.clear();
    }
    }
    rfid.halt();
  }
}
