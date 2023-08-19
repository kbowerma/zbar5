/*
 * Project zbar4
 * Description:
 * Author: Kyle Bowerman
 * Date: 8/8/23
 * 2 led light strips on turtle-bobcat refactored
 */

#include "zbar5.h"
#include <neopixel.h>

// Globals
int led2 = D7; 
int led1 = D0; // Instead of writing D0 over and over again, we'll write led1
int red, green, blue, white, red2,green2,blue2,white2 = 0;  // variable to store color
int oldred, oldgreen, oldblue, oldwhite = 0;  // variable to store color
int strip1pin = D2;
int strip2pin = D3;
int strip3pin = D4;
int numpixel = 18;

// Objects 
SYSTEM_MODE(AUTOMATIC);
Adafruit_NeoPixel strip1(numpixel, strip1pin, SK6812RGBW);
Adafruit_NeoPixel strip2(81, strip2pin, SK6812RGBW);
Adafruit_NeoPixel strip3(85, strip3pin, SK6812RGBW);
MyConfig myConfig = { false, false, "Test!", 20}; 


void setup() {
  EEPROM.get(CONFIGADDR,myConfig);

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

  Particle.function("setConfig1", setConfig1);
  Particle.function("setConfig2", setConfig2);
  Particle.function("ledConfig", ledConfig);
  Particle.subscribe("drago", myHandler, MY_DEVICES);

  pinMode(led2, OUTPUT);  // Built in led
  pinMode(led1, OUTPUT);
  pinMode(strip1pin, OUTPUT);  // 18x neopixel
  pinMode(strip2pin, OUTPUT);  // 81x neopixel
  pinMode(strip3pin, OUTPUT);  // 81x neopixel


  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip3.begin();
  strip3.show(); // Initialize all pixels to 'off'

}

void loop() {
  // set the stip om
  // juiceLeds1(red,green,blue,white);
  // juiceLeds2(red2,green2,blue2,white2);

  // check for the color to be changed
  if (oldblue != blue) {
    Particle.publish("bluecolorchanged", "foo");
  }

  // set last color change so we know when an event cahnges
  oldred = red;
  oldgreen = green;
  oldblue = blue;
  oldwhite = white;



}

  int setConfig1(String command) {
    int seperator = command.indexOf("=");
    String key = command.substring(0,seperator);
    String value = command.substring(seperator+1);

    if ( key == "red") { red = value.toInt(); juiceLeds1(red,green,blue,white); return 5; }
      if ( key == "green") { green = value.toInt(); juiceLeds1(red,green,blue,white); return 7; }
      if ( key == "blue") { blue = value.toInt(); juiceLeds1(red,green,blue,white); return 8; }
      if ( key == "white") { white = value.toInt(); juiceLeds1(red,green,blue,white); return 9; }
      if ( key == "all") { white = red = green = blue = value.toInt(); juiceLeds1(red,green,blue,white); return 9; }
      if ( key == "reset" ) {System.reset(); return 99;}

    
    else
      return 0;

  }
  int setConfig2(String command) {
    int seperator = command.indexOf("=");
    String key = command.substring(0,seperator);
    String value = command.substring(seperator+1);

      if ( key == "red") { red2 = value.toInt(); juiceLeds2(red2,green2,blue2,white2); return 5; }
      if ( key == "green") { green2 = value.toInt(); juiceLeds2(red2,green2,blue2,white2); return 7; }
      if ( key == "blue") { blue2 = value.toInt(); juiceLeds2(red2,green2,blue2,white2); return 8; }
      if ( key == "white") { white2 = value.toInt(); juiceLeds2(red2,green2,blue2,white2); return 9; }
      if ( key == "all") { white2 = red2 = green2 = blue2 = value.toInt(); juiceLeds2(red2,green2,blue2,white2); return 9; }
      if ( key == "reset" ) {System.reset(); return 99;}
    else
      return 0;
  }

  int ledConfig(String command) {
    int delim1 = command.indexOf(":");
    int delim2 = command.lastIndexOf(":");
    //Particle.publish("delim1", String(delim1));
    //Particle.publish("delim2", String(delim2));
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

  void juiceLeds1(int ured, int ugreen,int ublue, int uwhite) {
        
        #define mydelay2 10
        for (int n=0; n < numpixel; n++ ) {
        strip1.setPixelColor(n,ugreen,ured,ublue,uwhite );  // not sure why red and green is swapped
       //Particle.publish("juiceLeds", "foo");
        delay(mydelay2);
        strip1.show();
        }

  }

  void juiceLeds2(int ured, int ugreen,int ublue, int uwhite) {
        
        #define mydelay2 10
        for (int n=0; n < 81; n++ ) {
        strip2.setPixelColor(n,ugreen,ured,ublue,uwhite );  // not sure why red and green is swapped
       //Particle.publish("juiceLeds", "foo");
        delay(mydelay2);
        strip2.show();
        }

  }  

  void juiceSection(int startled, int endled, int ured, int ugreen,int ublue, int uwhite) {
      
      #define mydelay2 10
      for (int n=startled; n < endled; n++) {
      strip1.setPixelColor(n,ugreen,ured,ublue,uwhite );  // not sure why red and green is swapped
      //strip2.setPixelColor(n,ugreen,ured,ublue,uwhite );
      delay(mydelay2);
      strip1.show();

      }

  }

  void myHandler(const char *event, const char *data) {
    if (strcmp(data,"00")==0) {
      juiceLeds1(0,0,0,0);
    }
  }