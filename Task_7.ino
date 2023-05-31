int dir[]={1,2,3,4};
int PWM[]=(5,6,7,8);

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  for(i=0;i<4;i++){
  pinMode(dir[i], OUTPUT);
  pinMode(PWM[i], OUTPUT);
  delay(5000);
  }
}
void loop() {
  for(i=0;i<4;i++){
    digitalWrite(dir[i],HIGH);
    analogWrite(PWM[i],100);
  } 
  delay(5000);

   for(i=0;i<4;i++){
    analogWrite(PWM[i],0);
  }
  delay(2000);

  for(i=0;i<4;i++){
    digitalWrite(dir[i],LOW);
    analogWrite(PWM[i],100);
  } 
  delay(5000);

  for(i=0;i<4;i++){
    analogWrite(PWM[i],0);
  } 
  delay(2 000);
}
