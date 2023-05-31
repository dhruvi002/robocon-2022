#define numberOfMotors 4
int directionPins[] = {5, 3, 32, 7};
int speedPins[] = {6, 4, 2, 8};
int speed = 60;

bool isDetected = false, toStop = false;

int cm = 0;
int trigPin = 9, echoPin = 11;

// read distance(cm) from UV sensor
//readcm(triggerPin,echoPin)
//

int readcm(int trigPin, int echoPin)
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
  return 0.01723 * pulseIn(echoPin, HIGH);
}

// Check if the distance is in range
bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numberOfMotors; i++) {
    pinMode(directionPins[i], OUTPUT);
    pinMode(speedPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  cm = readcm(trigPin, echoPin);

  Serial.print(cm);
  Serial.println("cm");

  if (isDetected && !toStop)
  {
    for (int i = 1; i < numberOfMotors; i += 2) {
      digitalWrite(directionPins[i], LOW);
      analogWrite(speedPins[i], speed);
    }
    delay(2000);
    toStop = true;
  }
  else if (toStop)
  {
    for (int i = 1; i < numberOfMotors; i += 2) {
      analogWrite(speedPins[i], 0);
    }
  }
  else
  {
    if (!inRange(cm, 0, 55)) {
      // Rotate 2 alternate wheels with the same direction
      for (int i = 0; i < numberOfMotors; i += 2) {
        digitalWrite(directionPins[i], LOW);
        analogWrite(speedPins[i], speed);
      }
      for (int i = 1; i < numberOfMotors; i += 2) {
        analogWrite(speedPins[i], 0);
      }
    } else {
      // Stop 2 alternate wheels
      for (int i = 0; i < numberOfMotors; i += 2) {
        analogWrite(speedPins[i], 0);
      }
      isDetected = true;
    }
  }

}
