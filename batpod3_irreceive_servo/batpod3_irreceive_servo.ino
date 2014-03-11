/*

Arduino Uno

*/

#include <IRSendRev.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Servo
Servo ServoGauche;

int posServoGauche = 180;

// Infrarouge
unsigned char dta[20];

// Serial

byte byteRead;

void setup()
{
  
    Serial.println("Init Servo"); 
    ServoGauche.attach(7);
    ServoGauche.write(posServoGauche); 
    
    Serial.println("Init IR"); 
    Serial.begin(38400);
    IR.Init(A3);

}

void loop() {
     while(1) { 
       
       
         // Série

        if (Serial.available()) {
          byteRead = Serial.read();
          
          switch (byteRead) {
           
            case 113: { // q
                        Serial.println("Serie : Servo Gauche Avant");                      
                        for(posServoGauche = 0; posServoGauche < 180; posServoGauche += 1){
                               ServoGauche.write(posServoGauche);
                               delay(15);
                        }            
                        break;        
                      }     
            case 115: { // s
                        Serial.println("Serie : Servo Gauche Arriere");                      
                        for(posServoGauche = 180; posServoGauche>=1; posServoGauche-=1) {
                             ServoGauche.write(posServoGauche);
                            delay(15);
                         }               
                        break;        
                      }                         
                      
          }
        }            
       
       
       
       
        if(IR.IsDta()) {
  
          int length= IR.Recv(dta);
          Serial.println(dta[9]);
          if(dta[9] == 4) {
             Serial.println("IR : Servo Gauche Avant"); 
             for(posServoGauche = 0; posServoGauche < 180; posServoGauche += 1){
                 ServoGauche.write(posServoGauche);
                 delay(15);
             }             
          }
  
          if(dta[9] == 5) {
              Serial.println("IR : Servo Gauche Arriere");    
               for(posServoGauche = 180; posServoGauche>=1; posServoGauche-=1) {
                   ServoGauche.write(posServoGauche);
                   delay(15);
               }                
          }

  
        }
     }
 }
