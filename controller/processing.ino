void setupProcessing() {
  t.after(delayBetweenChecks, controlMoistureLevel);
}

void controlMoistureLevel() {
  int moistureValue = readMoistureValue();

  Serial.println(String("moistureValue: ") +  moistureValue + "\tmoistureTreshold: " + moistureTreshold);

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
