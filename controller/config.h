//==============================
// Pins
//==============================

// Moisture sensor
const int moistureSensorPin = A0;
const int configMaxIntPin = 18;
const int configMinIntPin = 19;

// LEDs
const int alertLedPin = 12;

// Pump
const int pumpPin = 11;

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
