#include <PS3BT.h>
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

void setup() {
Serial.begin(115200);
if (Usb.Init() == -1) {
Serial.print(F("\r\nOSC did not start"));
while(1); //halt
}
Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
Usb.Task();

if(PS3.PS3Connected || PS3.PS3NavigationConnected) {
if(PS3.getAnalogHat(LeftHatX) > 137 || 
    PS3.getAnalogHat(LeftHatX) < 117 || 
    PS3.getAnalogHat(LeftHatY) > 137 || 
    PS3.getAnalogHat(LeftHatY) < 117 || 
    PS3.getAnalogHat(RightHatX) > 137 || 
    PS3.getAnalogHat(RightHatX) < 117 || 
    PS3.getAnalogHat(RightHatY) > 137 || 
    PS3.getAnalogHat(RightHatY) < 117) {
Serial.print(F("\r\nLeftHatX: “));
Serial.print(PS3.getAnalogHat(LeftHatX));
Serial.print(F(”\tLeftHatY: “));
Serial.print(PS3.getAnalogHat(LeftHatY));
Serial.print(F(”\tRightHatX: “));
Serial.print(PS3.getAnalogHat(RightHatX));
Serial.print(F(”\tRightHatY: "));
Serial.print(PS3.getAnalogHat(RightHatY));
}

//Analog button values can be read from almost all buttons
if(PS3.getAnalogButton(L2_ANALOG) > 0 || PS3.getAnalogButton(R2_ANALOG) > 0) {
Serial.print(F("\r\nL2: “));
Serial.print(PS3.getAnalogButton(L2_ANALOG));
Serial.print(F(”\tR2: “));
Serial.print(PS3.getAnalogButton(R2_ANALOG));
}
if(PS3.getButtonClick(PS)) {
Serial.print(F(”\r\nPS"));
PS3.disconnect();
}
else {
if(PS3.getButtonClick(TRIANGLE))
Serial.print(F("\r\nTraingle"));
if(PS3.getButtonClick(CIRCLE))
Serial.print(F("\r\nCircle"));
if(PS3.getButtonClick(CROSS))
Serial.print(F("\r\nCross"));
if(PS3.getButtonClick(SQUARE))
Serial.print(F("\r\nSquare"));

if(PS3.getButtonClick(UP)) {
Serial.print(F("\r\nUp"));
if(PS3.PS3Connected) {
PS3.setAllOff();
PS3.setLedOn(LED4);
}
}
if(PS3.getButtonClick(RIGHT)) {
Serial.print(F("\r\nRight"));
if(PS3.PS3Connected) {
PS3.setAllOff();
PS3.setLedOn(LED1);
}
}
if(PS3.getButtonClick(DOWN)) {
Serial.print(F("\r\nDown"));
if(PS3.PS3Connected) {
PS3.setAllOff();
PS3.setLedOn(LED2);
}
}
if(PS3.getButtonClick(LEFT)) {
Serial.print(F("\r\nLeft"));
if(PS3.PS3Connected) {
PS3.setAllOff();
PS3.setLedOn(LED3);
}
}
}
}
