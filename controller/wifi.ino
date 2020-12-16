WiFiEspServer server(port);

// use a ring buffer to increase speed and reduce memory allocation
RingBuffer buf(http_buffer_size);

void setupWifi() {
  Serial1.begin(115200);

  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    setError(NO_WIFI_MODULE);
    return;
  }

  // connect to WiFI AP
  if (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    setError(NO_CONNECTION);
    return;
  }

  printWifiData();

  // start the web server
  server.begin();
}

void printWifiData()
{
  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  Serial.print("MAC address: ");
  Serial.println(buf);
}

enum ParseState { RD_REQUEST, RD_ENDPOINT, IGNORE };

void receiveClients() {
  WiFiEspClient client = server.available();

  if (client) {
    buf.init();

    ParseState state = RD_REQUEST;
    String requestType = "";
    String endpoint = "";

    while (client.connected()) {
      if (client.available()) {               // if there's bytes to read from the client,
        char c = client.read();
        buf.push(c);

        // printing the stream to the serial monitor will slow down
        // the receiving of data from the ESP filling the serial buffer
        //Serial.write(c);

        // end of the HTTP request
        if (buf.endsWith("\r\n\r\n")) {
          if (state != IGNORE || requestType.length() == 0 || endpoint.length() == 0) {
            serveBadRequest(client);
          } else {
            handleRequest(client, requestType, endpoint);
          }
          state = RD_REQUEST;
          break;
        } else if (state == RD_REQUEST) {
          if (c == ' ') {
            state = RD_ENDPOINT;
          } else {
            requestType += c;
          }
        } else if (state == RD_ENDPOINT) {
          if (c == ' ') {
            state = IGNORE;
          } else {
            endpoint += c;
          }
        }
      }
    }

    // close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
