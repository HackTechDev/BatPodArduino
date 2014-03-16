/*

Arduino Uno

*/

#include <IRSendRev.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Servo
Servo ServoGauche;
Servo servoD5; 
Servo servoD6;                
 
int posServoD5 = 0;   
int posServoD6 = 0;


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
    servoD5.attach(5);
    servoD6.attach(6); 
  
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

 
             // Servo D5
            case 119: { // w
                    Serial.println("Serie : ServoD5 baisser");
                        if (posServoD5 > 20) {
                              posServoD5 -= 20;
                              servoD5.write(posServoD5);
                              Serial.print("Serie : posServoD5 :" );
                              Serial.println(posServoD5);
                              delay(15);
                        }
                        break;
                      }
            case 120: { // x
                    Serial.println("Serie : ServoD5 lever");
                        if (posServoD5 < 160) {
                              posServoD5 += 20;
                               servoD5.write(posServoD5);  
                               Serial.print("Serie : posServoD5 :" );
                              Serial.println(posServoD5);                           
                              delay(15);
                        }
                        break;
                      }
  
             // Servo D6                    
             case 99: { // c
                    Serial.println("Serie : ServoD6 baisser");
                        if (posServoD6 > 20) {
                              posServoD6 -= 20;
                              servoD6.write(posServoD6);
                              Serial.print("Serie : posServoD6 :" );
                              Serial.println(posServoD6);
                              delay(15);
                        }
                        break;
                      }
            case 118: { // v
                    Serial.println("Serie : ServoD6 lever");
                        if (posServoD6 < 160) {
                              posServoD6 += 20;
                               servoD6.write(posServoD6);  
                               Serial.print("Serie : posServoD6 :" );
                              Serial.println(posServoD6);                           
                              delay(15);
                        }
                        break;
                      }                     

            
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
