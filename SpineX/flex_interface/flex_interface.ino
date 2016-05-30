#include "Arduino.h"
//#include "Servo/Servo.h"

//Servo servo;

void setup()
{
  Serial.begin(115200);
  //pinMode(11, OUTPUT);
  //servo.attach(11);
}

void loop()
{
  // [0; 1024] -> [-50C, 450C]
  float temp = analogRead(0);// * 500. / 1024. - 50.;
  //servo.write((temp - 23.) * 20 + 90);
  //float nVal = (temp - 23.) * 20 + 90;
  float nVal = map(temp, 0, 552, 0, 180);
  
  Serial.println(nVal);
  delay(100);
}

