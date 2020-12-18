const int debounceTime = 200; //ms

void setupInterrupts() {
  // Set interrupt pins as input
  pinMode(configMaxIntPin, INPUT_PULLUP);
  pinMode(configMinIntPin, INPUT_PULLUP);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(configMaxIntPin), configMaxValue, FALLING);
  attachInterrupt(digitalPinToInterrupt(configMinIntPin), configMinValue, FALLING);
}

void configMaxValue() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  int interruptPinValue = digitalRead(configMaxIntPin);

  // debounce + active when button is pressed
  if (interrupt_time - last_interrupt_time > debounceTime && interruptPinValue == 0)
  {
    Serial.println("Interrupted: configMaxValue");
    readAndSaveDryValue();
  }

  last_interrupt_time = interrupt_time;
}

void configMinValue() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  int interruptPinValue = digitalRead(configMinIntPin);

  // debounce + active when button is pressed
  if (interrupt_time - last_interrupt_time > debounceTime && interruptPinValue == 0)
  {
    Serial.println("Interrupted: configMinValue");
    readAndSaveWetValue();
  }

  last_interrupt_time = interrupt_time;
}
