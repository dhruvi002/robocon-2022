  // Reading analog Infrared Sensor values
  // https://www.arduinoplatform.com
  
  const int analogPin = A0;  // Analog input pin that the receiver is attached to
  const int digitalPin = 7;  // Analog input pin that the receiver is attached to
  int analogValue = 0;        // value read from the Analog receiver
  int digitalValue = 0;        // value read from the Digital receiver
  
  void setup() {
    pinMode(analogPin, INPUT);
    pinMode(digitalPin, INPUT);
  
    // initialize serial communications
    Serial.begin(9600); 
  }
  
  void loop() {
    // read the analog in value:
    analogValue = analogRead(analogPin);
    digitalValue = digitalRead(digitalPin);
  
    // print the results to the serial monitor:
  //  Serial.print("Analog Sensor = ");
  //  Serial.println(analogValue);
  
    Serial.print("Digital Sensor = ");
    Serial.println(digitalValue);
  
    //set the threshold which works best for you
  
    if (analogValue < 100) { //checks if object is there or not
  
      Serial.println("Object Detected by Analog Sensor");
    }
    else {
  
      Serial.println("No object in Front of Analog Sensor");
    }
    delay(500);
  
    if (digitalValue == LOW) { //checks if object is there or not
  
      Serial.println("Object Detected by Digital Sensor");
    }
    else {
  
      Serial.println("No object in Front of Digital Sensor");
    }
    delay(500);
  }
