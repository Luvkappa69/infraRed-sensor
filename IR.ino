#include <IRremote.hpp>
#include <afstandssensor.h>
#include <Servo.h>
#include <LiquidCrystal.h> //-------------------------------
#define led A5
LiquidCrystal lcd1 (12,11,5,4,3,2);//-------------------------------
#define pinServo 9
#define pinrele 7

Servo servo1;
int position = 0;
AfstandsSensor afstandssensor(10, 13);



void setup() 
{
  Serial.begin(9600);
  IrReceiver.begin(6); 
  pinMode(led, OUTPUT); 
  pinMode(pinrele, OUTPUT);
  lcd1.begin(16,2);//-------------------------------
  servo1.attach(pinServo);

}

void loop() {
  int valor =afstandssensor.afstandCM();
  Serial.println(afstandssensor.afstandCM());
  delay(500);
  

  if(valor>30){
    digitalWrite(led, 1);
    lcd1.clear();//-------------------------------
    lcd1.setCursor(0, 0);//-------------------------------
    lcd1.print("LED - ON");//-------------------------------
    digitalWrite(pinrele, 1);  
  }
  if(valor<=30){
    digitalWrite(led, 0);
    lcd1.clear();//-------------------------------
    lcd1.setCursor(0, 1);//-------------------------------
    lcd1.print("LED - OFF");//-------------------------------
    digitalWrite(pinrele, 0);  
  }
  
  


  if(position<0){
  position =0;
  }
  if (position>180){
    position=180;
  }
  
  if (IrReceiver.decode()) {
      int comando=0;
      comando=IrReceiver.decodedIRData.decodedRawData;
      Serial.println(comando);

          

      if (comando == 6181 || comando == 4133) {
        digitalWrite(led, 1);
        lcd1.clear();//-------------------------------
        lcd1.setCursor(0, 0);//-------------------------------
        lcd1.print("LED - ON");//-------------------------------
        digitalWrite(pinrele, 1);
      }
      else if (comando == 4108 || comando==6156){
        digitalWrite(led, 0);
        lcd1.clear();//-------------------------------
        lcd1.setCursor(0, 1);//-------------------------------
        lcd1.print("LED - OFF");//-------------------------------
        digitalWrite(pinrele, 0);
      }
      else if(comando == 6160 || comando==4112){
        position=position+5;
        servo1.write(position);
        IrReceiver.resume();
        lcd1.clear();//-------------------------------
        lcd1.setCursor(0, 0);
        lcd1.print("Servo position");
        lcd1.setCursor(0, 1);//-------------------------------
        if (position>180){
          lcd1.print("180");
        }
        else{
          lcd1.print(position);
        }
      }
      
      else if(comando == 6161 || comando==4113){
        position=position+5;
        servo1.write(position);
        IrReceiver.resume();
        lcd1.clear();//-------------------------------
        lcd1.setCursor(0, 0);
        lcd1.print("Servo position");
        lcd1.setCursor(0, 1);//-------------------------------
        if (position<0){
          lcd1.print("0");
        }
        else{
          lcd1.print(position);
        }
        
      }
      if (comando== 4109 || comando ==6157){
        position=0;
      }
      
      
      // USE NEW 3.x FUNCTIONS
      //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      IrReceiver.resume(); // Enable receiving of the next value
  }
}
