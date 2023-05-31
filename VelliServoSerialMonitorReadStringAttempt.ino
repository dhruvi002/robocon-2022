#include<Servo.h>

Servo myservo;
int pos=90, delaytime=0;
String inp1 = "POSITION", inp2 = "TIME";
String var1, var2;

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
  Serial.println("POSITION|pos&TIME|delaytime");
}

void loop()
{
  if (Serial.available() > 0)
  {
    var1 = Serial.readStringUntil('|');
    inp1 = Serial.parseInt();
    var2 = Serial.readStringUntil('|');
    inp2 = Serial.parseInt();
    if (var1=inp1 && var2=inp2)
    {myservo.write(inp1);
    delay(inp2);}
  }
}
