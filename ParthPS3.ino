#include <PS3BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// North, West, South, East Pins
int dir[2][2] = {{6, 24}, {3, 8}};
int speeds[2][2] = {{5, 2}, {4, 7}};
int max_speed = 130;
int min_speed = 80;
bool North1 = LOW;
bool North2 = LOW;
bool W = North1^North2;

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void setup()
{
  for (int i{0}; i < 2; i++)
  {
    for (int j{0}; j < 2; j++)
    {
      pinMode(dir[i][j], OUTPUT);
      pinMode(speeds[i][j], OUTPUT);
    }
  }
  if (Usb.Init() == -1)
  {
    while (1);
  }
}

void loop()
{
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  {
    int RightX = PS3.getAnalogHat(RightHatX);
    int LeftY = PS3.getAnalogHat(LeftHatY);
    int Right2 = PS3.getAnalogButton(R2);
    int Left2 = PS3.getAnalogButton(L2);

    if (LeftY < 137 and LeftY > 117 and Right2 == 0 and Left2 == 0)
    {
      analogWrite(speeds[!(W)][!North2], 0);
      analogWrite(speeds[W][!North2], 0);
    }
    else if (LeftY > 137)
    {
      digitalWrite(dir[!(W)][!North2], !North1);
      digitalWrite(dir[W][!North2], !North1);
      analogWrite(speeds[!(W)][!North2], map(LeftY, 137, 255, min_speed, max_speed));
      analogWrite(speeds[W][!North2], map(LeftY, 137, 255, min_speed, max_speed));
    }
    else if (LeftY < 117)
    {
      digitalWrite(dir[!(W)][!North2], North1);
      digitalWrite(dir[W][!North2], North1);
      analogWrite(speeds[!(W)][!North2], map(LeftY, 117, 0, min_speed, max_speed));
      analogWrite(speeds[W][!North2], map(LeftY, 117, 0, min_speed, max_speed));
    }

    if (RightX < 137 and RightX > 117 and Right2 == 0 and Left2 == 0)
    {
      analogWrite(speeds[North1][North2], 0);
      analogWrite(speeds[!North1][North2], 0);
    }
    else if (RightX > 137)
    {
      digitalWrite(dir[North1][North2], !(W));
      digitalWrite(dir[!North1][North2], !(W));
      analogWrite(speeds[North1][North2], map(RightX, 137, 255, min_speed, max_speed));
      analogWrite(speeds[!North1][North2], map(RightX, 137, 255, min_speed, max_speed));
    }
    else if (RightX < 117)
    {
      digitalWrite(dir[North1][North2], W);
      digitalWrite(dir[!North1][North2], W);
      analogWrite(speeds[North1][North2], map(RightX, 117, 0, min_speed, max_speed));
      analogWrite(speeds[!North1][North2], map(RightX, 117, 0, min_speed, max_speed));
    }

    if (Right2 > 0)
    {
      digitalWrite(dir[North1][North2], HIGH);
      digitalWrite(dir[!North1][North2], LOW);
      digitalWrite(dir[!(W)][!North2], HIGH);
      digitalWrite(dir[W][!North2], LOW);
      for (int i{0}; i < 2; i++)
      {
        for (int j{0}; j < 2; j++)
        {
          analogWrite(speeds[i][j], map(Right2, 0, 255, min_speed, max_speed));
        }
      }
    }
    else if (Left2 > 0)
    {
      digitalWrite(dir[North1][North2], LOW);
      digitalWrite(dir[!North1][North2], HIGH);
      digitalWrite(dir[!(W)][!North2], LOW);
      digitalWrite(dir[W][!North2], HIGH);
      
      for (int i{0}; i < 2; i++)
      {
        for (int j{0}; j < 2; j++)
          {
            analogWrite(speeds[i][j], map(Left2, 0, 255, min_speed, max_speed));
          }
      }
    }

    if (PS3.getButtonClick(LEFT))
    {
      North1 = W;
      North2 = !North2;
      W = North1^North2;
    }

    if (PS3.getButtonClick(RIGHT))
    {
      North1 = !W;
      North2 = !North2;
      W = North1^North2;
    }
  }
}
