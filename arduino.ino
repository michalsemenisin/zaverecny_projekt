#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

// Pozice nyní
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; 
// Původní pozice
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; 
// Pole pro ukládání pozice
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50]; 
String dataIn = "";
void setup() {
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);
 
  delay(20);
  // Počáteční pozice 
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 150;
  servo02.write(servo2PPos);
  servo3PPos = 35;
  servo03.write(servo3PPos);
  servo4PPos = 140;
  servo04.write(servo4PPos);
  servo5PPos = 85;
  servo05.write(servo5PPos);
  servo6PPos = 80;
  servo06.write(servo6PPos);
}

void loop() {
    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo1Pos = dataInS.toInt(); 
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {  
          servo01.write(j);
          delay(20);  
        }
      }
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;
    }
}
