/*
 * Project zbar5
 * Description:
 * Author: Kyle Bowerman
 * Date: 8/30/23
 * 3 led light strips on swed1 and swed2 
 * working with PIR
 */

#include "zbar5.h"
#include <neopixel.h>

// Globals
int led2 = D7; 
int led1 = D0; // Instead of writing D0 over and over again, we'll write led1
int red, green, blue, white, red2,green2,blue2,white2 = 0;  // variable to store color
int strip1pin = D2;
int strip2pin = D3;
int strip3pin = D4;
int PIR = A0;
int numpixel = 18;
int motionState;
int lastMotionTime, secSinceMotion = 0;

// Objects 
SYSTEM_MODE(AUTOMATIC);
Adafruit_NeoPixel strip1(numpixel, strip1pin, SK6812RGBW);
Adafruit_NeoPixel strip2(81, strip2pin, SK6812RGBW);
Adafruit_NeoPixel strip3(85, strip3pin, SK6812RGBW);
MyConfig myConfig = { false, false, "Test!", 20}; 


void setup() {
  size_t eepromlength = int(EEPROM.length());
  EEPROM.get(CONFIGADDR,myConfig);

  Particle.variable("eepromlength", int(eepromlength));
  Particle.variable("D2Armed", myConfig.D2Armed);
  Particle.variable("red", red);
  Particle.variable("green", green);
  Particle.variable("blue", blue);
  Particle.variable("white", white);
  Particle.variable("red2", red2);
  Particle.variable("green2", green2);
  Particle.variable("blue2", blue2);
  Particle.variable("white2", white2);
  Particle.variable("version", MYVERSION);
  Particle.variable("fileName", FILENAME);
  Particle.variable("buildDate", BUILD_DATE);
  Particle.variable("myfirmware", MYFIRMWARE);
  Particle.variable("lastMotion", secSinceMotion);
  Particle.function("ledConfig", ledConfig);
  Particle.subscribe("office", ledhandler, MY_DEVICES);

  pinMode(led2, OUTPUT);  // Built in led
  pinMode(led1, OUTPUT);
  pinMode(strip1pin, OUTPUT);  // 18x neopixel
  pinMode(strip2pin, OUTPUT);  // 81x neopixel
  pinMode(strip3pin, OUTPUT);  // 81x neopixel
  pinMode(PIR, INPUT_PULLDOWN);


  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip3.begin();
  strip3.show(); // Initialize all pixels to 'off'
  // Publish my vars
  Particle.publish("FILENAME", FILENAME);
  Particle.publish("MYVERSION", MYVERSION);
  Particle.publish("BUILD_DATE", BUILD_DATE);
  Particle.publish("MYFIRMWARE", MYFIRMWARE);

}

void loop() {

// read PIR Sensor
motionState = digitalRead(PIR);

// Got motion
if ( motionState == HIGH ) { // got motion
  motionHandler(); 
}

 // last item in loop
 secSinceMotion = ( millis() - lastMotionTime )/1000;
}

// ---------- Functions ---------

  int ledConfig(String command) {
    // usage:  strip:color:brightness   2:white:200
    int delim1 = command.indexOf(":");
    int delim2 = command.lastIndexOf(":");
    String mystrip = command.substring(0,delim1);
    String mycolor = command.substring(delim1+1,delim2);
    String mybrightness = command.substring(delim2+1);
    int stripId = mystrip.toInt();
    Particle.publish("mystrip", String(mystrip));
    Particle.publish("mycolor", String(mycolor));
    Particle.publish("mybrightness", String(mybrightness));

      if ( mycolor == "red") { red = mybrightness.toInt(); juiceLeds(stripId,red,green,blue,white); return 5; }
      if ( mycolor == "green") { green = mybrightness.toInt(); juiceLeds(stripId,red,green,blue,white); return 7; }
      if ( mycolor == "blue") { blue = mybrightness.toInt(); juiceLeds(stripId,red,green,blue,white); return 8; }
      if ( mycolor == "white") { white = mybrightness.toInt(); juiceLeds(stripId,red,green,blue,white); return 9; }
      if ( mycolor == "all") { white = red = green = blue = mybrightness.toInt(); juiceLeds(stripId,red,green,blue,white); return 9; }
      if ( mycolor == "reset" ) {System.reset(); return 99;}
    else
      return 0;

  }

  void juiceLeds(int stripId, int ured, int ugreen,int ublue, int uwhite) {

    if ( stripId == 1 ){
      Particle.publish("juiceleds", String(stripId));
      int pix = 18;
      for (int n=0; n < pix; n++ ) {
        strip1.setPixelColor(n,ugreen,ured,ublue,uwhite ); 
        delay(10);
        strip1.show();
      }
      
    }
    else if ( stripId == 2 ){
      int pix = 81;
      for (int n=0; n < pix; n++ ) {
        strip2.setPixelColor(n,ugreen,ured,ublue,uwhite ); 
        delay(10);
        strip2.show();
      }
      
    }
    else if ( stripId == 3 ){
      int pix = 84;
      for (int n=0; n < pix; n++ ) {
        strip3.setPixelColor(n,ugreen,ured,ublue,uwhite ); 
        delay(10);
        strip3.show();
      }
      
    }
    else if ( stripId == 4 ){
      int pix = 84;
      for (int n=0; n < pix; n++ ) {
        strip3.setPixelColor(n,ugreen,ured,ublue,uwhite ); 
      }
      strip3.show();
      
    }
    else if ( stripId == 5 ){

        strip1.clear();
        strip1.show();
        strip2.clear(); 
        strip2.show(); 
        strip3.clear();  
        strip3.show(); 

    }
    else {
      Particle.publish("ERROR", "Did not find stripid");
    }


  }

  void ledhandler(const char *event, const char *data) {
    String stdata = String(data);
    Particle.publish("debug stdata",stdata);
    ledConfig(String(stdata));

  }

  void motionHandler() {
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, HIGH);
    lastMotionTime = millis();
    return;

  }