const int addrMaxVal = 0;
const int addrMinVal = addrMaxVal + sizeof(int);

void setupMoistureSensor() {
  // Set analog reference to 3.3V (external)
  analogReference(EXTERNAL);

  // Read form the EEPROM the sensor readings in air and water
  maxValue = readIntFromEEPROM(addrMaxVal);
  minValue = readIntFromEEPROM(addrMinVal);

  Serial.print("maxValue: ");
  Serial.println(maxValue);
  Serial.print("minValue: ");
  Serial.println(minValue);

  checkMaxAndMinValues();
}

void checkMaxAndMinValues() {
  // Suspend the controller if the sensor parameters are not configured
  setSuspend(maxValue == -1 || minValue == -1);
}

void readAndSaveMaxValue() {
  maxValue = readMoistureValue();
  writeIntToEEPROM(addrMaxVal, maxValue);
}

void readAndSaveMinValue() {
  minValue = readMoistureValue();
  writeIntToEEPROM(addrMinVal, minValue);
}

int readMoistureValue() {
  return average(nrMeasurements, []() {
    return analogRead(moistureSensorPin);
  });
}

int readMoisturePercentage() {
  return moistureValueToPercentage(readMoistureValue());
}

int moistureValueToPercentage(int value) {
  return map(value, minValue, maxValue, 100, 0);
}
