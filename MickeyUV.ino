int inches = 0;

int cm = 0;

int trigPin = 9, echoPin = 11;

long readUltrasonicDistance(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);  // Clear the trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // s(cm) = (0.034*t)/2
  cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
  // s(inch) = cm/2.54
  inches = (cm / 2.54);

  Serial.print(inches);
  Serial.print("in, ");

  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}
