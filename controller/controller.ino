#include <EEPROM.h>
#include "config.h"

// suspend execution
volatile bool suspend = false;

void setup() {
  // Show that setup is going on
  pinMode(alertLedPin, OUTPUT);
  digitalWrite(alertLedPin, HIGH);

  Serial.begin(115200);
  setupMoistureSensor();
  setupInterrupts();
  
  // Show that setup is over
  if(!suspend)
    digitalWrite(alertLedPin, LOW);
}

void loop() {

  if(suspend) {
    return;
  }

  int soilMoistureValue = readMoistureValue();
  int soilMoisturePercentage = moistureValueToPercentage(soilMoistureValue);

  Serial.print("Sensor value: ");
  Serial.print(soilMoistureValue);
  Serial.print(" Precentage: ");
  Serial.print(soilMoisturePercentage);
  Serial.println(" %");

  delay(1000);
}
