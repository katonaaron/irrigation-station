void setupPump() {
  pinMode(pumpPin, OUTPUT);
}

void startPump() {
  digitalWrite(pumpPin, HIGH);
  Serial.println("Pump started");
}

void stopPump() {
  digitalWrite(pumpPin, LOW);
  Serial.println("Pump stopped");
}
