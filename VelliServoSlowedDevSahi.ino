#include <Servo.h>
Servo myServo;
char inputBuffer[16];
unsigned int currentval = 0, lastcurrentval;
void setup()
{
  Serial.begin(9600);
  myServo.attach(28);
}

void loop()
{
  if (Serial.available() > 0)
  {
    // A function that reads characters from the serial port into a buffer.
    Serial.readBytes(inputBuffer, sizeof(inputBuffer));

    // Convert string to integer
    // cplusplus.com/reference/cstdlib/atoi/
    currentval = atoi(inputBuffer);

    // memset clears buffer and updates string length so strlen(inputBuffer) is accurate.
    memset(inputBuffer, 0, sizeof(inputBuffer));

  }

  if (currentval != lastcurrentval)
  {
    if (currentval < lastcurrentval)
    {
      for (currentval = 0; currentval <= 180; currentval += 1) {
        myServo.write(constrain(currentval, 20, 160));
      }
    }
    else
      {
        for (currentval = 0; currentval <= 180; currentval -= 1) 
        {
          myServo.write(constrain(currentval, 20, 160));
        }
      }
    }
    lastcurrentval = currentval;
}
