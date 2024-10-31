#include "HX711.h"
//Lab 3A code
// HX711 circuit wiring
//Hx711 Left side 21.9 Middle 22.6 Right side 22.9
const int LOADCELL_DOUT_PIN = 15;
const int LOADCELL_SCK_PIN = 14;
double voltreading;
double maxvalue = 100000;
double maxValue = -1e6;  // Initialize to a very small number
double minValue = 1e6;   // Initialize to a very large number
HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_gain(64);
  double Angle = 0;
  
}

void loop() {

  /*
  //InAmp Measurement
  sensorValue = analogRead(BridgeOutput);  // Read the analog input
  counter++;
  sum = sum + sensorValue;
  if (counter > 100) {

    counter = 0;
    sum = floor(sum / 10);
    //This is to smooth out serial plotter, so it doesn't auto change to show noise
    Serial.print(28500);
    Serial.print(", ");
    Serial.println(sum);
    Serial.print(28000);
    Serial.print(", ");
  } 
  */  


  if (scale.is_ready()) {
    double reading = scale.read();
    //Serial.print("HX711 reading: ");
    voltreading = ((-409732 + reading)/325957)- .2;
    
    Serial.print(90);
    Serial.print(", ");
    Serial.print(-45);
    Serial.print(", ");
    //Serial.println(voltreading);

    if (voltreading > maxValue) {
      maxValue = voltreading;
    }
    if (voltreading < minValue) {
      minValue = voltreading;
    }

    //Hx711 is the right strain gauge so pulling to the left is the maximum strain angle
    //double AngleFromLeft = 56.962*voltreading - 1249.7;
    //30 is the distance from full left to the center
    //double AngleFromCenter = AngleFromLeft - 30;
    //If negative then the Angle is to the left of center and if positive the angle is to the right of center
    //Serial.println(AngleFromCenter);

    //Determine the adc_value when angle is 0
    //Max Left is 22
    //Middle 0 angle is 21.3
    //Max Right is 20.9
/*
    Serial.print("max Value");
    Serial.println(maxValue);
    Serial.print("min Value");
    Serial.println(minValue);
*/
    //double Angle = (-80 * (voltreading)) + 1695;
    double Angle = (-79.839 * voltreading) + 1708.5;

    Serial.println(Angle);
  } else {
    Serial.println("HX711 not found.");
  }
  
  delay(100);
  
}