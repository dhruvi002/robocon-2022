#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE
#define PWM 5
#define DIR 9

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT); 
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(DIR,OUTPUT);
  
  Serial.println("target pos");
}

void loop() {

  // set target position
  //int target = 1200;
  int target = 250*sin(prevT/1e6);

  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
  
  int e = pos - target;   // error

  float dedt = (e-eprev)/(deltaT); // derivative

  eintegral = eintegral + e*deltaT;  // integral

  float u = kp*e + kd*dedt + ki*eintegral;// control signal

  float pwr = fabs(u);  // motor power
  if( pwr > 255 ){
    pwr = 255;
  }

  int dir = 1;  // motor direction
  if(u<0){
    dir = -1;
  }

  setMotor(dir,pwr,PWM);   // signal the motor

  eprev = e; // store previous error

  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm){
  analogWrite(pwm,pwmVal);
  digitalWrite(DIR,dir);
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}


//from video
//void loop{
//  int a = digitalRead(ENCA);
//  int b = digitalRead(ENCB);
//  Serial.print(a*5);
//  Serial.print(" ");
//  Serial.print(b*5);
//  Serial.println();
//}
