/*
BatPod.

* Matériels : 

- Grove seriel bluetooth : http://www.seeedstudio.com/wiki/Grove_-_Serial_Bluetooth
- Shield Bot V0.9b : https://www.seeedstudio.com/wiki/Shield_Bot_V0.9b
- Seeeduino v3.0, Atmega328 based : http://www.seeedstudio.com/wiki/Seeeduino_v3.0

* Etapes : 

- Eteindre le pc
- Brancher la carte sur le pc
- Rallumer le pc
- Mettre la carte sur le bot
- Lancer l'IDE 

* IDE Arduino : v1.0.5

* Configuration IDE : 

- Type de carte : Duemilanove w/ ATMega 328
- Port série : /dev/tts0

*/

#include <Shieldbot.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Servo
Servo ServoDroit;
Servo ServoGauche;

int posServoDroit = 0;
int posServoGauche = 0;

// Bluetooth
#define RxD 4
#define TxD 5
SoftwareSerial blueToothSerial(RxD,TxD);

Shieldbot shieldbot = Shieldbot();

void setup(){

    // Servo
    ServoDroit.attach(2);
    ServoGauche.write(posServoDroit);    
    
    ServoGauche.attach(3); 
    ServoGauche.write(posServoGauche);  

    // Bot  
    Serial.begin(9600);
    shieldbot.setMaxSpeed(128); //255 is max

    // Bluetooth  
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);  
    setupBlueToothConnection(); 
}

void loop(){

 char recvChar;
 
    while(1) {
     
          if (blueToothSerial.available()) {
             recvChar = blueToothSerial.read();
             switch (recvChar) {

                /* Mouvement de base */
                 case '8' : {
                     blueToothSerial.println("Avancer Droit");
                     Serial.println("Avancer Droit");
                     shieldbot.drive(127,127);
                     delay(750);
                     break;
                     }

                 case '2' : {
                     blueToothSerial.println("Reculer Droit");
                     Serial.println("Reculer Droit");
                     shieldbot.drive(-128,-128);
                     delay(750);                     
                     break;
                     }

                 case '7' : {
                     blueToothSerial.println("Avancer Gauche");
                     Serial.println("Avancer Gauche");
                     shieldbot.drive(0,127);
                     delay(750);                     
                     break;
                     }

                 case '9' : {
                     blueToothSerial.println("Avancer Droite");
                     Serial.println("Avancer Droite");
                     shieldbot.drive(127,0);
                     delay(750);                      
                     break;
                     }

              /* Mouvement avancée*/

                 case '1' : {
                     blueToothSerial.println("Reculer Droit");
                     Serial.println("Reculer Droit");
                     shieldbot.drive(0,-128);
                     delay(750);
                     break;
                     }

                 case '3' : {
                     blueToothSerial.println("Reculer Droit");
                     Serial.println("Reculer Droit");
                     shieldbot.drive(-128,0);
                     delay(750);                     
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
                     delay(750);                       
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

