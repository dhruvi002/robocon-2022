#include <Servo.h>
Servo myServo;
char inputBuffer[16];
unsigned int val=90;
void setup()
{
  Serial.begin(9600);
  myServo.attach(28);

}

void loop()
{ 
  if(Serial.available()>0)
  {
     // A function that reads characters from the serial port into a buffer.
    Serial.readBytes(inputBuffer, sizeof(inputBuffer));

    // Convert string to integer
    // cplusplus.com/reference/cstdlib/atoi/
    val = atoi(inputBuffer);

    // memset clears buffer and updates string length so strlen(inputBuffer) is accurate.
    memset(inputBuffer, 0, sizeof(inputBuffer));
    
  }
  myServo.write(constrain(val,20,160));
}
