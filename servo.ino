#include <Servo.h>
String c;
Servo myservo;
int state=0;

void setup()
{
Serial.begin(9600);
myservo.attach(28);
myservo.write(state);
}

void loop() {
   while (Serial.available()) {
    String c = Serial.readString();  
 }
   state = c.toInt();

if (Serial.available()>0)
{
  
//Serial.println();


myservo.write(state);
}
}
