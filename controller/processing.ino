void setupProcessing() {
  t.after(delayBetweenChecks, controlMoistureLevel);
  t.every(displayRefreshPeriod, displayMoisturePercentage);
}

void controlMoistureLevel() {
  int moistureValue = readMoistureValue();
  
  Serial.print("moistureValue: ");
  Serial.print(moistureValue );
  Serial.print("\tmoistureTreshold: ");
  Serial.println(moistureTreshold);

  if (moistureValueToPercentage(moistureValue) < moistureValueToPercentage(moistureTreshold)) {
    startPump();
    t.after(pumpTime, stopPumpAndWaitForSensorReaction);
  } else {
    t.after(delayBetweenChecks, controlMoistureLevel);
  }
}

void stopPumpAndWaitForSensorReaction() {
  stopPump();
  t.after(sensorReactionTime, controlMoistureLevel);
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
