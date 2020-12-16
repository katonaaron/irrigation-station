
void setError(Error error) {
  Serial.print("Error: ");
  Serial.println(errorToString(error));
  suspend = true;
}

const char* errorToString(Error error) {
  switch(error) {
    case NO_WIFI_MODULE:
      return "WiFi module not connected";
    default:
      return "Unknown error";
  }
}
