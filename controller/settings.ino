
/**
 * Loads the settings from the EEPROM to the "settings" variable. 
 * In case the data in the EEPROM is not valid, the variable remains unchanged.
 */
void loadSettings() {
   Settings storedSettings;
   EEPROM.readBlock(SETTINGS_ADDR, storedSettings);

   if(strcmp(SETTINGS_VERSION, storedSettings.version) == 0) {
    settings = storedSettings;
   }
}


void saveSettings() {
   EEPROM.updateBlock(SETTINGS_ADDR, settings);
}


void printSettings() {
  Serial.println("Settings");
  Serial.print("\tversion: ");
  Serial.println(settings.version);
  Serial.print("\tnrMeasurements: ");
  Serial.println(settings.nrMeasurements);
  Serial.print("\tdryValue: ");
  Serial.println(settings.dryValue);
  Serial.print("\twetValue: ");
  Serial.println(settings.wetValue);
  Serial.print("\ttresholdPercentage: ");
  Serial.println(settings.tresholdPercentage);
  Serial.print("\tsensorReactionTime: ");
  Serial.println(settings.sensorReactionTime);
  Serial.print("\tpumpingTime: ");
  Serial.println(settings.pumpingTime);
  Serial.print("\tdelayBetweenChecks: ");
  Serial.println(settings.delayBetweenChecks);
  Serial.print("\tdisplayRefreshPeriod: ");
  Serial.println(settings.displayRefreshPeriod);
}
