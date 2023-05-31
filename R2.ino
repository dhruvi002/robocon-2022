#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
//North = 0, east=0
int motor_dir[2][2] = {{15, 32}, {17, 6}}; //ne,nw,se,sw
int motor_spd[2][2] = {{12, 7}, {13, 5}}; //ne,nw,se,sw
int dir[2][2] = {{0, 1}, {1, 0}}; //1 clockwise, 0 anticlockwise
int max_speed = 170;
int min_speed = 50;

// Catapult pins
//int cdcv_pins[] = {};

bool cdcv = 1;

// Ball picking pins
//int bdcv_pins[] = {HERE, HERE};
int bd_pin = 3, bp_pin = 4;

const int bspd = 50, btime = 1000;
bool bdir = 1;

// Lagori disk picking
int ldcv_pins[] = {31, 33};
int ld_pin = 30, lp_pin = 2;
Servo lagoriServo;
//int lservo_pin = HERE;

const int lspd = 50, ltime = 10;
bool ldcv = 1;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
int y, x, l2, r2;
int spd[2][2];
void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  for (int i = 0; i <= 1 ; i++)
  {
    for (int j = 0; j <= 1 ; j++)
    {
      pinMode(motor_spd[i][j], OUTPUT);
      pinMode(motor_dir[i][j], OUTPUT);
    }
  }
  for(int i = 0; i < 2; i++) {
    pinMode(cdcv_pins[i], OUTPUT);
  }
  for(int i = 0; i < 2; i++) {
    pinMode(bdcv_pins[i], OUTPUT);
  }
  for(int i = 0; i < 2; i++) {
    pinMode(ldcv_pins[i], OUTPUT);
  }
  pinMode(bd_pin, OUTPUT);
  pinMode(bp_pin, OUTPUT);
  pinMode(ld_pin, OUTPUT);
  pinMode(lp_pin, OUTPUT);
  lagoriServo.attach(lservo_pin);
}

int self_map(int spd)
{
  int val = (max_speed - min_speed) * (spd - 5) / 127 + min_speed;
  if (val < min_speed)
  {
    return 0;
  }
  else if (val > max_speed)
  {
    return max_speed;
  }
  else
  {
    return val;
  }
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    y = 127 - PS3.getAnalogHat(LeftHatY);
    x = PS3.getAnalogHat(RightHatX) - 127;
    if (abs(y) < 10)
      y = 0;
    if (abs(x) < 10)
      x = 0;
    l2 = PS3.getAnalogButton(L2) / 2;
    r2 = PS3.getAnalogButton(R2) / 2;
    /*nw = -y-x;
      ne = y-x
      se = y+x
      sw = -y+x*/
    l2 /= 2;
    r2 /= 2;
    for (int i = 0; i <= 1; i++)
    {
      for (int j = 0; j <= 1; j++)
      {
        spd[i][j] = (l2 - r2 + (i * 2 - 1) * x - (j * 2 - 1) * y) * (dir[i][j] * 2 - 1);
        digitalWrite(motor_dir[i][j], ((spd[i][j] / abs(spd[i][j]) + 1) / 2));
        analogWrite(motor_spd[i][j], self_map(abs(spd[i][j])));
        Serial.print(motor_dir[i][j]);
        Serial.print("\t");
        Serial.println(((spd[i][j] / abs(spd[i][j]) + 1) / 2));
        Serial.print(motor_spd[i][j]);
        Serial.print("\t");
        Serial.println(self_map(abs(spd[i][j])));
      }
    }
    // Catapult mechanism on Left Button
    if (PS3.getButtonClick(LEFT)) {
      dcvWrite('c', 0, 0);
      dcvWrite('c', !cdcv, cdcv);
      delay(2000);
      dcvWrite('c', 0, 0);
      delay(10);
      cdcv = !cdcv;
    }
    if (PS3.getButtonClick(UP)) {
      dcvWrite('b', 0, 0);
      dcvWrite('b', 0, 1);
      delay(1000);
      dcvWrite('b', 0, 0);
      delay(10);
    }
    if (PS3.getButtonClick(UP)) {
      dcvWrite('b', 0, 0);
      dcvWrite('b', 1, 0);
      delay(1000);
      dcvWrite('b', 0, 0);
      delay(10);
    }
    if (PS3.getButtonClick(RIGHT)) {
      motorWrite('b', bspd, bdir);
      bdir = !bdir;
      delay(btime);
    }
    if (PS3.getButtonClick(L1)) {
      motorWrite('l', lspd, 1);
    } else {
      motorWrite('l', 0, 0);
    }
    if (PS3.getButtonPress(R1)) {
      motorWrite('l', lspd, 0);
    } else {
      motorWrite('l', 0, 0);
    }
    if (PS3.getButtonPress(CROSS)) {
      dcvWrite('l', 0, 0);
      dcvWrite('l', !ldcv, ldcv);
      delay(2000);
      dcvWrite('l', 0, 0);
      delay(10);
      ldcv = !ldcv;
    }
  }
}

void dcvWrite(char opt, bool val1, bool val2) {
  switch (opt) {
    case 'c': {
        digitalWrite(cdcv_pins[0], val1);
        digitalWrite(cdcv_pins[1], val2);
        break;
      }
    case 'b': {
        digitalWrite(bdcv_pins[0], val1);
        digitalWrite(bdcv_pins[1], val2);
        break;
      }
    case 'l': {
        digitalWrite(ldcv_pins[0], val1);
        digitalWrite(ldcv_pins[1], val2);
        break;
      }
  }
}

void motorWrite(char opt, int spd, bool dir) {
  switch (opt) {
    case 'b': {
        digitalWrite(bd_pin, dir);
        analogWrite(bp_pin, spd);
        break;
      }
    case 'l': {
        digitalWrite(ld_pin, dir);
        analogWrite(lp_pin, spd);
        break;
      }
  }
}
