/*
BatPod

- Recepteur IR
- Servo

*/

#include <IRSendRev.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Servo

Servo servoD5; 
Servo servoD6;                
Servo servoD7; 
Servo servoD8;  

int posServoD5 = 0;   
int posServoD6 = 0;
int posServoD7 = 0;   
int posServoD8 = 0;

// Infrarouge
unsigned char dta[20];

// Serial

byte byteRead;

void setup()
{
  
    Serial.println("Init Servo"); 
    servoD5.attach(5);
    servoD6.attach(6); 
    servoD7.attach(7);
    servoD8.attach(8); 
  
    Serial.println("Init IR"); 
    Serial.begin(38400);
    IR.Init(A3);

}

void loop() {
     while(1) { 
       
       // Infra-rouge
       
        if(IR.IsDta()) {
  
          int length= IR.Recv(dta);
          Serial.println(dta[9]);
          
          /****************************************************/
          
          if(dta[9] == 1) {
             Serial.println("Servo arriere-bras gauche baisser");  
  
              if (posServoD5 > 20) {
                  posServoD5 -= 20;
                  servoD5.write(posServoD5);
                  delay(15);
              }
          }
  
          if(dta[9] == 2) {
              Serial.println("Servo arriere-bras gauche lever");    
              if (posServoD5 < 160) {
                    posServoD5 += 20;
                     servoD5.write(posServoD5);                          
                    delay(15);
              }              
          }


          /****************************************************/
          
          if(dta[9] == 3) {
             Serial.println("Servo avant-bras gauche baisser");  
  
              if (posServoD6 > 20) {
                  posServoD6 -= 20;
                  servoD5.write(posServoD5);
                  delay(15);
              }
          }
  
          if(dta[9] == 4) {
              Serial.println("Servo avant-bras gauche lever");    
              if (posServoD6 < 160) {
                    posServoD6 += 20;
                     servoD5.write(posServoD5);                          
                    delay(15);
              }              
          }


          /****************************************************/
          
          if(dta[9] == 5) {
             Serial.println("Servo arriere-bras droit baisser");  
  
              if (posServoD7 > 20) {
                  posServoD7 -= 20;
                  servoD7.write(posServoD7);
                  delay(15);
              }
          }
  
          if(dta[9] == 6) {
              Serial.println("Servo arriere-bras droit lever");    
              if (posServoD7 < 160) {
                    posServoD7 += 20;
                     servoD7.write(posServoD7);  
                          
                    delay(15);
              }              
          }


          /****************************************************/
          
          if(dta[9] == 7) {
             Serial.println("Servo avant-bras droit baisser");  
  
              if (posServoD8 > 20) {
                  posServoD8 -= 20;
                  servoD8.write(posServoD8);
                  delay(15);
              }
          }
  
          if(dta[9] == 8) {
              Serial.println("Servo avant-bras droit lever");    
              if (posServoD8 < 160) {
                    posServoD8 += 20;
                     servoD8.write(posServoD8);                          
                    delay(15);
              }              
          }
  
        }
     }
 }
