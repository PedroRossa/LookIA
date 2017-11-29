
#include <Servo.h>

static int fingerPin = 2;
String receivedMessage = "";

int fingerDown = 45;
int fingerUp = 20;

Servo finger;

void MoveFinger(char dir){
  if(dir == '0'){
    finger.write(fingerDown);       
  }
  else if(dir == '1'){
    finger.write(fingerUp);    
  }
}

void SetFingerAngleUP(int angle){
  fingerUp = angle;
}

void SetFingerAngleDown(int angle){
  fingerDown = angle;
}

void PressButton(){
  finger.attach(fingerPin);
  finger.write(fingerDown);   
  delay(80);
  finger.write(fingerUp);
  delay(80);
  finger.detach();
  Serial.println('1');
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hi software, please TEACH ME!!!");
}

void loop() 
{
   char command = Serial.read();
   if(command == '1')
      PressButton();
  //  if(fingerDirection != lastDirection)
  //  {
  //   lastDirection = fingerDirection;
  //   MoveFinger(fingerDirection);
  //  }
  //  delay(10);
}
