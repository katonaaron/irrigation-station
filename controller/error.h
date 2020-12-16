#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

enum Error {
  NO_WIFI_MODULE = 1,
  NO_WIFI_CONNECTION
};

const char* errorMessage(Error error) {
  switch (error) {
    case NO_WIFI_MODULE:
      return "WiFi module is unplugged";
    case NO_WIFI_CONNECTION:
      return "Cannot connect to WiFi AP";
    default:
      return "Unknown error";
  }
}

const char* errorAbbr(Error error) {
  switch (error) {
    case NO_WIFI_MODULE:
      return "EU";
    case NO_WIFI_CONNECTION:
      return "EC";
    default:
      return "E-";
  }
}


#endif
