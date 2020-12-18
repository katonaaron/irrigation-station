void handleRequest(WiFiEspClient& client, const String& requestType, const String& endpoint) {
  if (endpoint == "/") {
    if (requestType == "GET") {
      getRoot(client);
    } else {
      serveMethodNotAllowed(client);
    }
  } else if (endpoint == "/sensor") {
    if (requestType == "GET") {
      getSensor(client);
    } else if (requestType == "PATCH") {
      updateSensor(client);
    } else {
      serveMethodNotAllowed(client);
    }
  } else if (endpoint == "/moisture") {
    if (requestType == "GET") {
      getMoisture(client);
    } else {
      serveMethodNotAllowed(client);
    }
  } else if (endpoint == "/timing") {
    if (requestType == "GET") {
      getTiming(client);
    } else if (requestType == "PATCH") {
      updateTiming(client);
    } else {
      serveMethodNotAllowed(client);
    }
  } else {
    serveNotFound(client);
  }
}

// Root

void getRoot(WiFiEspClient& client) {
  DynamicJsonDocument doc(64);

  JsonObject _links = doc.createNestedObject("_links");
  _links["moisture"]["href"] = "/moisture";
  _links["sensor"]["href"] = "/sensor";
  _links["timing"]["href"] = "/timing";

  sendHttpResponse(client, OK, doc);
}

// Sensor

void getSensor(WiFiEspClient& client) {
  DynamicJsonDocument doc(48);

  doc["maxValue"] = MAX_SENSOR_VAL;
  doc["minValue"] = MIN_SENSOR_VAL;
  doc["dryValue"] = settings.dryValue;
  doc["wetValue"] = settings.wetValue;
  doc["tresholdPercentage"] = settings.tresholdPercentage;

  sendHttpResponse(client, OK, doc);
}

void updateSensor(WiFiEspClient& client) {
  StaticJsonDocument<24> filter;
  filter["dryValue"] = true;
  filter["wetValue"] = true;
  filter["tresholdPercentage"] = true;

  DynamicJsonDocument doc(96);
  DeserializationError error = deserializeJson(doc, client, DeserializationOption::Filter(filter));

  if (error) {
    sendHttpResponse(client, BAD_REQUEST, "reason", error.c_str());
    return;
  }

  int dryValue = doc["dryValue"] | settings.dryValue;
  int wetValue = doc["wetValue"] | settings.wetValue;
  int tresholdPercentage = doc["tresholdPercentage"] | settings.tresholdPercentage;

  if (dryValue < MIN_SENSOR_VAL || dryValue > MAX_SENSOR_VAL
      || wetValue < MIN_SENSOR_VAL || wetValue > MAX_SENSOR_VAL
      || dryValue <= wetValue) {
    sendHttpResponse(client, UNPROCESSABLE_ENTITY, "reason", "must hold: minValue <= wetValue < dryValue <= maxValue");
    return;
  }

  if (tresholdPercentage < 0 || tresholdPercentage > 100) {
    sendHttpResponse(client, UNPROCESSABLE_ENTITY, "reason", "must hold: 0 <= tresholdPercentage <= 100");
    return;
  }

  settings.dryValue = dryValue;
  settings.wetValue = wetValue;
  settings.tresholdPercentage = tresholdPercentage;

  saveSettings();
  getSensor(client);
}

// Moisture level

void getMoisture(WiFiEspClient& client) {
  DynamicJsonDocument doc(24);

  int moistureValue = readMoistureValue();

  doc["value"] = moistureValue;
  doc["percentage"] = moistureValueToPercentage(moistureValue);
  doc["voltage"] = moistureValueToVoltage(moistureValue);

  sendHttpResponse(client, OK, doc);
}

// Timing

void getTiming(WiFiEspClient& client) {
  DynamicJsonDocument doc(32);

  doc["sensorReactionTime"] = settings.sensorReactionTime;
  doc["pumpingTime"] = settings.pumpingTime;
  doc["delayBetweenChecks"] = settings.delayBetweenChecks;
  doc["displayRefreshPeriod"] = settings.displayRefreshPeriod;

  sendHttpResponse(client, OK, doc);
}

void updateTiming(WiFiEspClient& client) {
  StaticJsonDocument<32> filter;
  filter["sensorReactionTime"] = true;
  filter["pumpingTime"] = true;
  filter["delayBetweenChecks"] = true;
  filter["displayRefreshPeriod"] = true;

  DynamicJsonDocument doc(128);
  DeserializationError error = deserializeJson(doc, client, DeserializationOption::Filter(filter));

  if (error) {
    sendHttpResponse(client, BAD_REQUEST, "reason", error.c_str());
    return;
  }

  long sensorReactionTime = doc["sensorReactionTime"] | settings.sensorReactionTime;
  long pumpingTime = doc["pumpingTime"] | settings.pumpingTime;
  long delayBetweenChecks = doc["delayBetweenChecks"] | settings.delayBetweenChecks;
  long displayRefreshPeriod = doc["displayRefreshPeriod"] | settings.displayRefreshPeriod;

  if (sensorReactionTime < 0 || pumpingTime < 0
      || delayBetweenChecks < 0 || displayRefreshPeriod < 0) {
    sendHttpResponse(client, UNPROCESSABLE_ENTITY, "reason", "values must be >= 0");
    return;
  }

  settings.sensorReactionTime = sensorReactionTime;
  settings.pumpingTime = pumpingTime;
  settings.delayBetweenChecks = delayBetweenChecks;
  settings.displayRefreshPeriod = displayRefreshPeriod;

  saveSettings();
  getTiming(client);
}

// Errors

void serveNotFound(WiFiEspClient& client) {
  sendHttpResponse(client, NOT_FOUND);
}

void serveMethodNotAllowed(WiFiEspClient& client) {
  sendHttpResponse(client, METHOD_NOT_ALLOWED);
}

void serveBadRequest(WiFiEspClient& client) {
  sendHttpResponse(client, BAD_REQUEST);
}
