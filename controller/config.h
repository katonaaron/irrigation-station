#include "secrets.h"

//==============================
// Pins
//==============================

// Moisture sensor
const int moistureSensorPin = A0;
const int configMaxIntPin = 3;
const int configMinIntPin = 2;

// LEDs
const int alertLedPin = 12;

// Pump
const int pumpPin = 11;

// Display
const int dispSDI = 7;
const int dispSCLK = 6;
const int dispLOAD = 5;

//==============================
// Parameters - Default values
//==============================

// Soil moisture sensor
const int nrMeasurements = 10; // per a single reading

volatile int maxValue = 930; // 3V
volatile int minValue = 0; // 0V
int moistureTreshold = maxValue / 2; // 50%

// Moisture controller timings
long sensorReactionTime = 10 * 1000; //30 s
long pumpTime = 1 * 1000; //ms
long delayBetweenChecks = 5000; //ms
long displayRefreshPeriod = 1000; //ms

//==============================
// Constants
//==============================

const int nrPlants = 1;

// Display
const int dispDigits = 2;

// Serial communication
const long baudRate = 115200;
const int serialCommandLength = 20; 

// WiFi
const char ssid[] = SECRET_SSID;           
const char pass[] = SECRET_PASS;
const int port = 80;

// The size of the circular buffer storing (partially) the HTTP request
const int http_buffer_size = 4;
