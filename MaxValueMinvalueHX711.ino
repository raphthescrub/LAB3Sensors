#include "HX711.h"
//Lab 3A code
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 15;
const int LOADCELL_SCK_PIN = 14;
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
  if (scale.is_ready()) {
    double reading = scale.read();
    voltreading = ((-409732 + reading) / 325957) - 0.2;

    // Update max and min values
    if (voltreading > maxValue) {
      maxValue = voltreading;
    }
    if (voltreading < minValue) {
      minValue = voltreading;
    }

    // Print the current reading
    Serial.print("Current reading: ");
    Serial.println(voltreading);

    // Print the highest and lowest values so far
    Serial.print("Max value: ");
    Serial.println(maxValue);

    Serial.print("Min value: ");
    Serial.println(minValue);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(50);  // Adjust the delay as needed
}
