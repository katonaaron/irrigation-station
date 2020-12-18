void setupProcessing() {
  t.after(settings.delayBetweenChecks, controlMoistureLevel);
  t.every(settings.displayRefreshPeriod, displayMoisturePercentage);
}

void controlMoistureLevel() {
  int moisturePercentage = moistureValueToPercentage(readMoistureValue());

  Serial.print("moisturePercentage: ");
  Serial.print(moisturePercentage );
  Serial.print("\ttresholdPercentage: ");
  Serial.println(settings.tresholdPercentage);

  if (moisturePercentage < settings.tresholdPercentage) {
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
