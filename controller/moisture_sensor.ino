void setupMoistureSensor() {
  // Set analog reference to 3.3V (external)
  analogReference(EXTERNAL);
}

void readAndSaveMaxValue() {
  settings.maxValue = readMoistureValue();
  saveSettings();
}

void readAndSaveMinValue() {
  settings.minValue = readMoistureValue();
  saveSettings();
}

int readMoistureValue() {
  return average(settings.nrMeasurements, []() {
    return analogRead(moistureSensorPin);
  });
}

int readMoisturePercentage() {
  return moistureValueToPercentage(readMoistureValue());
}

int moistureValueToPercentage(int value) {
  return map(value, settings.minValue, settings.maxValue, 100, 0);
}
