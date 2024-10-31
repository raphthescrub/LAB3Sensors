#include "HX711.h"
const int LOADCELL_DOUT_PIN = 15;
const int LOADCELL_SCK_PIN = 14;
const int BridgeOutput = 35;

float sensorValue;
float voltageValue2;
double voltreading;
double maxValue = -1e6;  // Initialize to a very small number
double minValue = 1e6;   // Initialize to a very large number
HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_gain(64);
}

void loop() {
  // Read the analog input
  sensorValue = analogRead(BridgeOutput);
  voltageValue2 = (sensorValue + 280) / 1333.893;
  delay(200);

  int AngleINAMP = -(680 * (voltageValue2) - 1421);

  // HX711
  if (scale.is_ready()) {
    double reading = scale.read();
    voltreading = ((-409732 + reading) / 325957) - 0.2;

    // Calculate angle from HX711 reading
    double Angle = (-79.839 * voltreading) + 1680;

    // Print all four values in one line
    Serial.print((AngleINAMP + Angle)/2);   // First value
    Serial.print(", ");         // Comma separator
    Serial.print(90);           // Second value
    Serial.print(", ");         // Comma separator
    Serial.println(-45);          // Third value
        // Fourth value + newline to end the line

  } else {
    Serial.println("HX711 not found.");
  }
}
