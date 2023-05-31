const byte serialEn = 47;    // Connect UART output enable of LSA08 to pin 2
const byte junctionPulse = 49;   // Connect JPULSE of LSA08 to pin 4

void setup() {
  pinMode(serialEn,OUTPUT);   // Setting serialEn as digital output pin
  pinMode(junctionPulse,INPUT);   // Setting junctionPulse as digital input pin


  // Setting initial condition of serialEn pin to HIGH
  digitalWrite(serialEn,HIGH);

  // Begin serial communication with baudrate 9600
  Serial.begin(9600);

}

void loop() {
  int dummy = 0;   // Declare a dummy variable to store incoming data
  
  
  digitalWrite(serialEn,LOW);   // Set serialEN to LOW to request UART data
  while(Serial.available() <= 0); 
  dummy = Serial.read();
  Serial.println(dummy);
  Serial.println("data");
  digitalWrite(serialEn,HIGH);    // Stop requesting for UART data
}
