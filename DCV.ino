int valve1= 51;
int valve2= 47;
int valve4= 23;
int valve3= 27;

void setup() {
  
}

void loop() {

digitalWrite(valve1, LOW);
digitalWrite(valve2, LOW);
digitalWrite(valve3, LOW);
digitalWrite(valve4, LOW);
delay(1000); //Wait 1 Second

digitalWrite(valve1, LOW); 
digitalWrite(valve2, HIGH);

digitalWrite(valve3, LOW); 
digitalWrite(valve4, HIGH);
delay(2000); //Wait 1 Second


digitalWrite(valve1, LOW);
digitalWrite(valve2, LOW);
digitalWrite(valve3, LOW);
digitalWrite(valve4, LOW);
delay(1000); //Wait 1 Second

digitalWrite(valve2, LOW);
digitalWrite(valve1, HIGH);
digitalWrite(valve2, LOW);
digitalWrite(valve1, HIGH);
delay(1000);
}
