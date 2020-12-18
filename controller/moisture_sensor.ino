void setupMoistureSensor() {
  // Set analog reference to 3.3V (external)
  analogReference(EXTERNAL);
}

void readAndSaveDryValue() {
  settings.dryValue = readMoistureValue();
  saveSettings();
}

void readAndSaveWetValue() {
  settings.wetValue = readMoistureValue();
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
  return map(value, settings.wetValue, settings.dryValue, 100, 0);
}

int percentageToMoistureValue(int percentage) {
  return map(percentage, 100, 0, settings.wetValue, settings.dryValue);
}

float moistureValueToVoltage(int value) {
  return map(value, 0, 1023, 0, 33) / 10.0f;
}
