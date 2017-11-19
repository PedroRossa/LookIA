#include <Servo.h>

static int fingerPin = 2;
String receivedMessage = "";
char fingerDirection = 0;
char lastDirection = 0;

int fingerDown = 0;
int fingerUp = 25 ;

Servo finger;

void MoveFinger(char dir){
  if(dir == '0'){
    finger.write(fingerDown);       
  }
  else if(dir == '1'){
    finger.write(fingerUp);    
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("OLAR");
  finger.attach(fingerPin);
  finger.write(0);  
}

void loop() {
   fingerDirection = Serial.read();
   if(fingerDirection != lastDirection)
   {
    lastDirection = fingerDirection;
    MoveFinger(fingerDirection);
   }
   delay(10);
}
