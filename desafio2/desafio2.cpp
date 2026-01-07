#include "Servo.h"
Servo servoMotor;
int servoMotorPin = 3;
int valor_pot = 0;
int rotacao = 0;
const int pinoBuzzer = 5;

void setup()
{
  servoMotor.attach(servoMotorPin);
  pinMode(pinoBuzzer,OUTPUT);
  
}
void loop()
{
  valor_pot=analogRead(A3);
  rotacao = map(valor_pot,0,1023,0,180);
  servoMotor.write(rotacao);
  if (rotacao == 0){
    tone(pinoBuzzer,1000);
    delay(100);
    noTone(pinoBuzzer);
    delay(1000);
  }
  else if (rotacao == 180){
    tone(pinoBuzzer,600);
    delay(100);
    noTone(pinoBuzzer);
    delay(1000);
  }
    
}
