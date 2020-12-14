int average(int count, int (*func) ()) {
  int sum = 0;
  for(int i = 0; i < count; i++) {
    sum += func();
  }
  return sum / count;
}

int readIntFromEEPROM(int address) {
  byte low = EEPROM.read(address);
  byte high = EEPROM.read(address + 1);
  return (high << 8) | low;
}

void writeIntToEEPROM(int address, int num) {
  byte low = num & 0xFF;
  byte high = num >> 8;
  EEPROM.update(address, low);
  EEPROM.update(address + 1, high);
}

void setSuspend(bool isSuspended) {
  suspend = isSuspended;
  digitalWrite(alertLedPin, isSuspended ? HIGH : LOW);
}
