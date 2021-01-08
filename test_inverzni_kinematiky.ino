#include <Servo.h>


Servo BasePan, GripTilt, ShoulderTilt, ElbowTilt, WristTilt; 

int pos, CurrentAngle;
int i;



#define PI 3.14159265

float ShoulderLength = 6.0;
float ElbowLength = 4.0;
float WristLength = 4.0;
float Hypot, Slope, CirclePointX, CirclePointY;
float x1 = 10.0;
float y1 = 7.0;
float x2 = 0.0;
float y2 = 0.0;
float A, B, C,
      PosXAnswer,   
      PosYAnswer,  
      NegXAnswer, 
      NegYAnswer,  
      Angle_A,     
      Angle_A_Temp,
      Angle_B,      
      Angle_C;     


void setup()
{

  Serial.begin(9600);



  pinMode( 9, OUTPUT); //Base pin.
  pinMode( 10, OUTPUT); //Shoulder pin.
  pinMode( 11, OUTPUT); //Elbow pin.
  pinMode( 8, OUTPUT); //Wrist pin.
  pinMode( 7, OUTPUT); //Grip



  BasePan.attach(9); 
  GripTilt.attach(7);
  ShoulderTilt.attach(10); 
  ElbowTilt.attach(11);
  WristTilt.attach(8);


  Serial.println("Initializing Servos");
  ResetServos();

}//end setup.


void loop()
{


  for ( x1 = 3; x1 < 14; x1 = x1 + 1) {

    for (y1 = 1; y1 < 15; y1 = y1 + 1) {


      Serial.println("*******************");
      Serial.println();
      Serial.print("Point: (");
      Serial.print(x1);
      Serial.print(",");
      Serial.print(y1);
      Serial.println(")");
      if ((x1 < ShoulderLength) && (y1 < ShoulderLength)) {
        Special_Calc_Point();

      }
      else {

        Calc_Point();

      }
    }
  }


}



void Special_Calc_Point() {


  Hypot = sqrt(sq(x1) + sq(y1)) + WristLength;
  A = ElbowLength;//4;
  B = Hypot;
  C = ShoulderLength;//6;



  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);


  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);

  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C))); 

  if (Angle_A < 35) {
    Angle_A = 35;
  }//End if <35.



  if (!isnan(Angle_A)) {      
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }


  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
      }//end for CurrentAngle.

    }//end if Angle_B > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } 


}


void Calc_Point() {
  //*********** Line Calcs *********************************
  Slope = (y2 - y1) / (x2 - x1);
  Serial.print("Slope: ");
  Serial.println(Slope, 4);


  A = 1 + sq(y1 / x1);
  B = (-2 * x1) + (-2 * y1 * Slope);
  C = sq(y1) + sq(x1) - sq(WristLength);


  Serial.println();

  NegXAnswer = ((-1 * B) - (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Minus portion of Quadratic Equation.
  NegYAnswer = Slope * NegXAnswer;

  if (!isnan(NegXAnswer)) {

    Serial.print("Negative Point: ");
    Serial.print(NegXAnswer);
    Serial.print(",");
    Serial.println(NegYAnswer);
    Serial.println();

    Calc_Circle(NegXAnswer, NegYAnswer);
  }

  else
  {



    PosXAnswer = ((-1 * B) + (sqrt(sq(B) - (4 * A * C)))) / (2 * A); //Plus portion of Quadratic Equation.
    PosYAnswer = Slope * PosXAnswer;

    if (!isnan(PosXAnswer)) {
      Serial.print("**** Positive Point: ");
      Serial.print(PosXAnswer);
      Serial.print(",");
      Serial.println(PosYAnswer);
      Serial.println();

      Calc_Circle(PosXAnswer, PosYAnswer);

    }

  }

}



void Calc_Circle(float BXValue, float BYValue) {

  Hypot = sqrt(sq(BXValue) + sq(BYValue));
  A = ElbowLength;//4;
  B = Hypot;
  C = ShoulderLength;//6;


  // Calculate angle B //
  Angle_B =  acos((sq(C) + sq(A) - sq(B)) / (2 * A * C)) * (180 / PI);


  // Calculate angle C //
  Angle_C = acos((sq(A) + sq(B) - sq(C)) / (2 * A * B)) * (180 / PI);
  Angle_C = 180 - Angle_C; //must calc larger opposite side angle.


  // Calculate angle A //
  Angle_A = acos((sq(B) + sq(C) - sq(A)) / (2 * B * C)) * (180 / PI);

  Angle_A = Angle_A * (1 + (Angle_A / (Angle_B + Angle_C))); 

  if (Angle_A < 35) {
    Angle_A = 35;
  }//End if <35.


  if (!isnan(Angle_A)) { //If Angle is a valid number.
    Serial.println(Angle_A);
    ShoulderTilt.write(Angle_A);
    delay(1000);
  }

  if (!isnan(Angle_B)) { //If Angle is a valid number.

    CurrentAngle = ElbowTilt.read();

    if (Angle_B > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i < Angle_B; i = i + 1) //if Angle_B > CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
      }

    }

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_B);
      for (i = CurrentAngle; i > Angle_B; i = i - 1) //if Angle_B < CurrentAngle.
      {

        ElbowTilt.write(i);
        delay(5);
      }
    }

  }



  if (!isnan(Angle_C)) { //If Angle is a valid number.

    CurrentAngle = WristTilt.read();

    if (Angle_C > CurrentAngle) {
      Serial.print(CurrentAngle);
      Serial.print(" < ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i < Angle_C; i = i + 1) //if Angle_C > CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
      }//end for CurrentAngle.

    }//end if Angle_C > CurrentAngle.

    else
    {
      Serial.print(CurrentAngle);
      Serial.print(" > ");
      Serial.println(Angle_C);
      for (i = CurrentAngle; i > Angle_C; i = i - 1) //if Angle_C < CurrentAngle.
      {

        WristTilt.write(i);
        delay(5);
      }//end for CurrentAngle.
    }//end else.

  } //end if !isnan.


}



//*************************************************************
//                  ResetServos
//*************************************************************
void ResetServos()
{

  ShoulderTilt.write(65);
  delay(2000);


  ElbowTilt.write(90 );
  delay(500);


  WristTilt.write(90);
  delay(500);


  GripTilt.write(90); 
  delay(500);


}
