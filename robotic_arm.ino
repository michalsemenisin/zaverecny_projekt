#include <Servo.h>        


String inStringValue = "";    // String na uchovani predaneho VALUE inputu
String inStringComma = "";    // String na uchovani predaneho COMMA inputu
String inStringCode = "";     // String na uchovani predaneho CODE inputu
int dataValue = 999;          // Inicializace hodnoty Value predane z Pythonu (pouzito po konverzi stringu do integeru)
int dataCode = 999;           // Inicializace hodnoty Code predane z Pythonu (pouzito po konverzi stringu do integeru)
int oldBaseVal = 90;          // Inicializace zakladni polohy ve stupnich 
int oldShoulderVal = 165;     // Inicializace zakladni polohy ve stupnich 
int oldElbowVal = 0;          // Inicializace zakladni polohy ve stupnich 
int oldWrist1Val = 0;         // Inicializace zakladni polohy ve stupnich 
int oldWrist2Val = 90;        // Inicializace zakladni polohy ve stupnich 

// Nastaveni serv podle jmena
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {

  Serial.begin(9600);           // Nastavi baudrate 9600 - pocet bitu za vterinu 

  while (!Serial) {
    ;                           // Cekani na seriovy port aby se pripojil
  }

  Serial.setTimeout(5000);      // Nastavi timeout na seriovy port dostatecne dlouhy aby ziskala data z pythonu

  moveArm(90, 165, 0, 0, 90);     
}


void loop() {


  while (Serial.available() == 0) {} // Cekani na prichazejici data

  delay(50);                         // Cas seriovemu portu aby se pripravil


  // Precte prichazejici byty:        ('VALUE' ',' 'CODE' ',')
  while (Serial.available() > 0) {                  // Kdyz jsou nejaka data, projde to

    inStringValue = Serial.readStringUntil(',');    // Precte VALUE ale ne carku
    delay(10);                                      // Cas seriovemu portu aby se pripravil
    dataValue = inStringValue.toInt();              // Konvertuje VALUE (string na integer)

    inStringCode = Serial.readStringUntil(',');     // Precte CODE ale ne carku
    delay(10);                                      // Cas seriovemu portu aby se pripravil
    dataCode = inStringCode.toInt();                // Konvertuje CODE (string na integer)

  }

  //Rameno vlevo
  if (dataCode == 1) {                              // Pohyb vlevo
    oldBaseVal -= dataValue;                        // Snizi pocet stupnu kdy base se otoci z klidove polohy
    if (oldBaseVal < 0) {                           // Kontrola zda se rameno snazi jit pod 0 stupnu (rameno nemuze jit pod 0)
      oldBaseVal = 0;                               // Pokud ano, nastavit stupne na 0
    }                              
    moveArm(oldBaseVal, 165, oldElbowVal, 0, 90);   
  }

  //Rameno vpravo
  if (dataCode == -1) {                             // Pohyb vpravo
    oldBaseVal += dataValue;                        // Zvysi pocet stupnu kdy se base otoci z klidove polohy
    if (oldBaseVal > 180) {                         // Kontrola zda se rameno snazi jit nad 180 stupnu
      oldBaseVal = 180;                             // Pokud ano, nastavit stupne na 180
    }
    moveArm(oldBaseVal, 165, oldElbowVal, 0, 90);   

  }

  //Rameno nahoru
  if (dataCode == 2) {                               // Pohyb nahoru
    oldElbowVal += dataValue;                        // Zvysi pocet stupnu kdy se elbow otoci z klidove polohy
    if (oldElbowVal > 180) {                         // Kontrola zda se rameno snazi jit nad 180 stupnu
      oldElbowVal = 180;                             // Pokud ano, nastavit stupne na 180
    }
    moveArm(oldBaseVal, 165, oldElbowVal , 0, 90);   
  }

  //Rameno dolu
  if (dataCode == -2) {                        // Pohyb dolu
    oldElbowVal -= dataValue;                  // Snizi pocet stupnu kdy elbow se otoci z klidove polohy
    if (oldElbowVal < 0) {                     // Kontrola zda se rameno snazi jit pod 0 stupnu (rameno nemuze jit pod 0)
      oldElbowVal = 0;                         // Pokud ano, nastavit stupne na 0
    }
    moveArm(oldBaseVal, 165, oldElbowVal, 0, 90);   
  }

  //Reset ramene
  if (dataCode == 3) {                          // Reset ramene do klidove polohy
    moveArm(90, 165, 0, 0, 90);                 // Reset ramene do klidove polohy
    oldBaseVal = 90;                            // Reset stupnu "base" 
    oldShoulderVal = 165;                       // Reset stupnu "shoulder" 
    oldElbowVal = 0;                            // Reset stupnu "elbow" 
    oldWrist1Val = 0;                           // Reset stupnu "wrist1" 
    oldWrist2Val = 90;                          // Reset stupnu "wrist2" 
    delay(50);                                  // Cas aby se serva vratily do klidove polohy
  }

  //Nahodny pohyb
  if (dataCode == 4 ) {
    for (int i = 1; i < 6; i = i + 1) {         // provest 6 nahodnych pozic
      moveArm(random(0, 180), random(30, 90), random(30, 90), random(30, 90), 90);   // Pohyb kazdeho segmentu ramene
      delay(3000);                              // Zastavit po kazdem pohybu na 3 vteriny
    } 
    moveArm(90, 165, 0, 0, 90);                 // Reset ramene do klidove polohy
    oldBaseVal = 90;                           // Reset stupnu "base" 
    oldElbowVal = 0;                           // Reset stupnu "elbow" 
  }



  inStringValue = "";    // Reset hodnoty inString pro dalsi sadu dat "Value" aby se konvertovala ze stringu na integer
  inStringCode = "";     // Reset hodnoty inString pro dalsi sadu dat "Code" aby se konvertovala ze stringu na integer
  dataCode = 999;        // Reset konvertovaneho "code" integeru
  dataValue = 999;       // Reset konvertovaneho "value" integeru

} 
