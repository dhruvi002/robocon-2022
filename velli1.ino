#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[ ] = "IoIkDYFkwDHCV77_-EmiDfXMw4eNrW9T";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[ ] = "Yash";
char pass[ ] = "yash1234";

WidgetLED led1(V1);
BlynkTimer timer;

// V1 LED Widget is blinking
void blinkLedWidget()  // function for switching off and on LED
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);
}

//In the loop function include Blynk.run() command.
void loop()
{
  Blynk.run();
  timer.run();
}
