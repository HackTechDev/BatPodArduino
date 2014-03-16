/*
   BatPod

   - Envoyeur IR
   - Bot

 */

#include <Shieldbot.h>
#include <SoftwareSerial.h>
#include <IRSendRev.h>

// Infrarouge

//the first parameter(15): the data that needs to be sent;
//the next 2 parameter(70,70): the logic high and low duration of "Start";
//the next 2 parameter(20,60): the logic "short" and "long"duration in the communication
//                             that to say:  if "0", the high duration is 20ms and  low is 20 ms; while logic "1",
//                              the high duration is 20 ms and low is 60 ms;
//the next 2 parameter(10): number of data you will sent;
//the next parameter(1, 2, 3, 4,5,6,7,8,9,10): data you will sent ;

unsigned char d[] = {15,    70, 70,    20, 60,    10,    1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Serial

byte byteRead;

// Bluetooth
#define RxD 4
#define TxD 5
SoftwareSerial blueToothSerial(RxD,TxD);

// Bot
Shieldbot shieldbot = Shieldbot();

void setup(){
    
    // Bot
    Serial.begin(38400);
    shieldbot.setMaxSpeed(128); //255 is max

    // Bluetooth
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);  
    setupBlueToothConnection(); 
}

void loop(){

    char recvChar;

    while(1) {

        // Série

        if (Serial.available()) {
          byteRead = Serial.read();
          
          switch (byteRead) {
            case 56: { // 8
                        Serial.println("Avancer Droit");                      
                        shieldbot.drive(127,127);    
                        break;        
                      }
            case 50: { // 2
                         Serial.println("Reculer Droit");
                         shieldbot.drive(-128,-128);
                         break;
                      }      
            case 53: { // 5
                         Serial.println("Arret");
                         shieldbot.drive(0,0);
                         break;
                      }   
            case 113: { // q
                        Serial.println("Servo Gauche Avant");                      
                     // 4
                     unsigned char d[] = {15, 70, 70, 20, 60, 10, 1, 2, 3,    4,    5, 6, 7, 8, 9, 10};
                     IR.Send(d, 38);                    
                   
                        break;        
                      }     
            case 115: { // s
                        Serial.println("Servo Gauche Arriere");                      
                     // 5
                     unsigned char d[] = {15, 70, 70, 20, 60, 10, 1, 2, 3,    5,   5, 6, 7, 8, 9, 10};
                     IR.Send(d, 38);       
                        break;        
                      }                         
                      
          }
        }      
      
        // Bluetooth
        if (blueToothSerial.available()) {
            recvChar = blueToothSerial.read();
            switch (recvChar) {

                /* Mouvement  */
                case '8' : {
                               blueToothSerial.println("Avancer Droit");
                               Serial.println("Avancer Droit");
                               shieldbot.drive(127,127);
                               delay(100);
                               break;
                           }

                case '2' : {
                               blueToothSerial.println("Reculer Droit");
                               Serial.println("Reculer Droit");
                               shieldbot.drive(-128,-128);
                               delay(100);                     
                               break;
                           }

                case '7' : {
                               blueToothSerial.println("Avancer Gauche");
                               Serial.println("Avancer Gauche");
                               shieldbot.drive(0,127);
                               delay(100);                     
                               break;
                           }

                case '9' : {
                               blueToothSerial.println("Avancer Droite");
                               Serial.println("Avancer Droite");
                               shieldbot.drive(127,0);
                               delay(100);                      
                               break;
                           }

                case '1' : {
                               blueToothSerial.println("Reculer Droit");
                               Serial.println("Reculer Droit");
                               shieldbot.drive(0,-128);
                               delay(100);
                               break;
                           }

                case '3' : {
                               blueToothSerial.println("Reculer Droit");
                               Serial.println("Reculer Droit");
                               shieldbot.drive(-128,0);
                               delay(100);                     
                               break;
                           }

                /* Vitesse */

                case 'a' : {
                               blueToothSerial.println("Vitesse 64");
                               Serial.println("Vitesse 64");
                               shieldbot.setMaxSpeed(64); 
                               break;
                           }

                case 'z' : {
                               blueToothSerial.println("Vitesse 128");
                               Serial.println("Vitesse 128");
                               shieldbot.setMaxSpeed(128);                     
                               break;
                           }

                case 'e' : {
                               blueToothSerial.println("Vitesse 196");
                               Serial.println("Vitesse 196");
                               shieldbot.setMaxSpeed(196);                    
                               break;
                           }

                case 'r' : {
                               blueToothSerial.println("Vitesse 255");
                               Serial.println("Vitesse 255");
                               shieldbot.setMaxSpeed(255);                    
                               break;
                           }

                /* Stop */

                case '5' : {
                               blueToothSerial.println("Stop");
                               Serial.println("Stop");
                               shieldbot.drive(0,0);
                               delay(100);                       
                               break;
                           }

                /* IR */

                case 'q' : {
                               blueToothSerial.println("Servo Gauche Avant");
                               Serial.println("Servo Gauche Avant");
                                 // 4
                                 unsigned char d[] = {15, 70, 70, 20, 60, 10, 1, 2, 3,    4,    5, 6, 7, 8, 9, 10};
                                 IR.Send(d, 38);  
                               break;
                           }

                 case 's' : {
                               blueToothSerial.println("Servi Gauche Arriere");
                               Serial.println("Servo Gauche Avant");
                                 // 5
                                 unsigned char d[] = {15, 70, 70, 20, 60, 10, 1, 2, 3,    5,   5, 6, 7, 8, 9, 10};
                                 IR.Send(d, 38); 
                               break;
                           }
   

            }

        }

    } 
}

void setupBlueToothConnection() {
    blueToothSerial.begin(38400);
    blueToothSerial.print("\r\n+STWMOD=0\r\n");
    blueToothSerial.print("\r\n+STNA=BatPod\r\n");
    blueToothSerial.print("\r\n+STPIN=6666\r\n");
    blueToothSerial.print("\r\n+STOAUT=1\r\n");
    blueToothSerial.print("\r\n+STAUTO=0\r\n");
    delay(2000);
    blueToothSerial.print("\r\n+INQ=1\r\n");
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);
    blueToothSerial.flush();
} 

