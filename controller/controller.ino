#include <Timer.h>
#include <EEPROM.h>

#include "config.h"
#include "SensorData.h"

Timer t;

// suspend execution
volatile bool suspend = false;

void setup() {
  // Show that setup is going on
  pinMode(alertLedPin, OUTPUT);
  digitalWrite(alertLedPin, HIGH);

  setupSerial();
  setupMoistureSensor();
  setupPump();
  setupProcessing();
  setupInterrupts();
  
  // Show that setup is over
  if(!suspend)
    digitalWrite(alertLedPin, LOW);
}

void loop() {
  if(suspend) {
    return;
  }

  t.update();

//  int soilMoistureValue = readMoistureValue();
//  int soilMoisturePercentage = moistureValueToPercentage(soilMoistureValue);
//
//  Serial.print("Sensor value: ");
//  Serial.print(soilMoistureValue);
//  Serial.print(" Precentage: ");
//  Serial.print(soilMoisturePercentage);
//  Serial.println(" %");
//
//  delay(1000);

  
}
