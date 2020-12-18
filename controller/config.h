#include "secrets.h"

//==============================
// Pins
//==============================

// Moisture sensor
const int moistureSensorPin = A0;
const int configMaxIntPin = 3;
const int configMinIntPin = 2;

// Pump
const int pumpPin = 5;

// Display
const int dispSDI = 8;
const int dispSCLK = 7;
const int dispLOAD = 6;

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

#define MAX_SENSOR_VAL 930 // 3V
#define MIN_SENSOR_VAL 0 // 0V


//================================
// User adjustable settings
//================================


#define SETTINGS_VERSION "v02"
#define SETTINGS_ADDR 0


typedef struct {
  char version[4] = SETTINGS_VERSION;

  // Soil moisture sensor
  int nrMeasurements = 10; // per a single reading
  
  // Sensor readings
  volatile int dryValue = MAX_SENSOR_VAL; // 3V
  volatile int wetValue = MIN_SENSOR_VAL; // 0V
  int tresholdPercentage = 0; // disable watering
  
  // Moisture controller timings
  long sensorReactionTime = 10 * 1000; //10 s
  long pumpingTime = 1 * 1000; //ms
  long delayBetweenChecks = 5000; //ms
  long displayRefreshPeriod = 1000; //ms
} Settings;

// System settings. initialized with default values.
Settings settings;
