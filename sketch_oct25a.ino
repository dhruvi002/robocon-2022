void setup()
{
  pinMode(9,OUTPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);

}
void loop()
{
  if (digitalRead(6)== LOW)
  {
    digitalWrite(9,HIGH);
    Serial.println("on");

  
 }
  else 
  {
    
    digitalWrite(9,LOW);
   Serial.println("off");

    
  }
  
}
