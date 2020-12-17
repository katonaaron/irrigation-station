void setupProcessing() {
  t.after(settings.delayBetweenChecks, controlMoistureLevel);
  t.every(settings.displayRefreshPeriod, displayMoisturePercentage);
}

void controlMoistureLevel() {
  int moistureValue = readMoistureValue();
  
  Serial.print("moistureValue: ");
  Serial.print(moistureValue );
  Serial.print("\ttresholdValue: ");
  Serial.println(settings.tresholdValue);

  if (moistureValueToPercentage(moistureValue) < moistureValueToPercentage(settings.tresholdValue)) {
    startPump();
    t.after(settings.pumpingTime, stopPumpAndWaitForSensorReaction);
  } else {
    t.after(settings.delayBetweenChecks, controlMoistureLevel);
  }
}

void stopPumpAndWaitForSensorReaction() {
  stopPump();
  t.after(settings.sensorReactionTime, controlMoistureLevel);
}

void displayMoisturePercentage() {
  int moistureValue = readMoistureValue();
  int moisturePercentage = moistureValueToPercentage(moistureValue);

  Serial.print("moistureValue: ");
  Serial.print(moistureValue );
  Serial.print("\tmoisturePercentage: ");
  Serial.println(moisturePercentage);

  displayPercentage(moisturePercentage);
}
