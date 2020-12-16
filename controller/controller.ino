#include <WiFiEsp.h>
#include <Timer.h>
#include <EEPROM.h>

#include "config.h"
#include "error.h"
#include "http.h"

Timer t;

// suspend execution
volatile bool suspend = false;

void setup() {
  // Show that setup is going on
  pinMode(alertLedPin, OUTPUT);
  digitalWrite(alertLedPin, HIGH);

  Serial.begin(baudRate);
  setupMoistureSensor();
  setupPump();
  setupProcessing();
  setupWifi();
  setupInterrupts();
  
  // Show that setup is over
  if(!suspend)
    digitalWrite(alertLedPin, LOW);
}

void loop() {
  if(suspend) {
    return;
  }

  receiveClients();

  //t.update();
}
