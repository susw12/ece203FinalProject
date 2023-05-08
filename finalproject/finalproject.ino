#include <TinyGPSPlus.h>
#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus/blob/master/src/TinyGPS%2B%2B.h
#include <SoftwareSerial.h>
#include<Wire.h>
#include<Adafruit_GFX.h> //https://github.com/adafruit/Adafruit-GFX-Library
#include<Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306
#include <Adafruit_LSM303_Accel.h>


int RXPin = 19;
int TXPin = 18; 
int GPSBaud = 9600; 
const int lebar=128;
const int tinggi=64;
const int reset= -1;

// Adafruit_LIS2MDL mag = Adafruit_LIS2MDL(12345);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(12345);
Adafruit_SSD1306 display(lebar,tinggi,&Wire,reset);
TinyGPSPlus gps;


SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  gpsSerial.begin(GPSBaud);
  Serial.begin(9600);

   if (!accel.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    delay(2000);
    Serial.println("Ooops, no LSM303 Accelerometer detected ... Check your wiring!");
    while (1)
      ;
  }
    Serial.println("Found LSM303AGR sensor");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
  display.clearDisplay();
  
  display.display();

  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
}
}


void loop(){
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
     display.clearDisplay();
     display.setTextSize(1);             
     display.setTextColor(WHITE);
     display.setCursor(0,1);      
     display.print(F("latitude: "));

     display.print(gps.location.lat(), 6);
     display.setCursor(0,16);

     display.print(F("longitude: "));

     display.print(gps.location.lng(), 6);

     display.setCursor(0,30);      
     display.print(F("time: "));

     display.setCursor(30,31);

    if (gps.time.isValid()){
     display.print(gps.time.hour());

     display.setCursor(50,31);
     display.print(gps.time.minute());

     display.setCursor(70,31);
     display.print(gps.time.second());

     display.setCursor(0,37);
     display.setCursor(0,40);      
     display.print(F("date: "));
     display.setCursor(30,40);
    }

      else
  {
    Serial.println("Not Available");
  }

     if (gps.date.isValid())
  {
     display.print(gps.date.day());
     display.setCursor(50,40);
     display.print(gps.date.month());
     display.setCursor(70,40);
     display.print(gps.date.year());
     display.setCursor(0,53);
     display.display();
      delay(10);
  }
    else
  {
    display.print("Not Available");
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(WHITE);
    display.setCursor(0,13);      
    display.print(F("No GPS detected"));
    display.setCursor(0,23);      
    display.print(F("check the cable and  restart the arduino"));
    display.display();
    Serial.println("check the cable and  restart the arduino");
    while(true);
  }
}



