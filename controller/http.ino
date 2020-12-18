// Sending HTTP header

void sendHttpHeader(WiFiEspClient& client, HttpStatus httpStatus, size_t contentLength)
{
  client.print("HTTP/1.1 ");
  client.println(httpStatusToStr(httpStatus));
  client.println("Content-type: application/json");
  if (contentLength > 0) {
    client.print("Content-Length: ");
    client.println(contentLength);
  }
  client.println();
}

void sendHttpHeader(WiFiEspClient& client, HttpStatus httpStatus)
{
  sendHttpHeader(client, httpStatus, 0);
}


// Sending HTTP response

void sendHttpResponse(WiFiEspClient& client, HttpStatus httpStatus, const DynamicJsonDocument& doc)
{
  sendHttpHeader(client, httpStatus, measureJson(doc));
  serializeJson(doc, client);
}


void sendHttpResponse(WiFiEspClient& client, HttpStatus httpStatus)
{
  sendHttpHeader(client, httpStatus);
}

void sendHttpResponse(WiFiEspClient& client, HttpStatus httpStatus, const char* content)
{
  sendHttpHeader(client, httpStatus);
  client.println(content);
  client.println();
}

void sendHttpResponse(WiFiEspClient& client, HttpStatus httpStatus, const char* label, const char* message)
{
  sendHttpHeader(client, httpStatus);
  client.print("{ \"");
  client.print(label);
  client.print("\": \"");
  client.print(message);
  client.print("\"}");
  client.println();
}
