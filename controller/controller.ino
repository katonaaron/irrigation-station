#include <Timer.h>
#include <ShiftRegister74HC595.h>
#include <WiFiEsp.h>
#include <EEPROMex.h>
#include <ArduinoJson.h>

#include "config.h"
#include "error.h"
#include "http.h"

Timer t;

// suspend execution
volatile bool suspend = false;

void setup() {
  // Show that setup is going on
  displayCharacters("SE");

  Serial.begin(baudRate);
  loadSettings();
  printSettings();
  setupMoistureSensor();
  setupPump();
  setupProcessing();
  setupWifi();
  setupInterrupts();
}

void loop() {
  if (suspend) {
    return;
  }

  receiveClients();

  t.update();
}
