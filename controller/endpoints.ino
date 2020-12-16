void handleRequest(WiFiEspClient client, String requestType, String endpoint) {
  if (endpoint == "/") {
    if (requestType == "GET") {
      serveRoot(client);
    } else {
      serveMethodNotAllowed(client);
    }
  } else {
    serveNotFound(client);
  }
}

// Endpoints

void serveRoot(WiFiEspClient client) {
  sendHttpResponse(client, OK, "Good");
}

// Errors

void serveNotFound(WiFiEspClient client) {
  sendHttpResponse(client, NOT_FOUND);
}

void serveMethodNotAllowed(WiFiEspClient client) {
  sendHttpResponse(client, METHOD_NOT_ALLOWED);
}

void serveBadRequest(WiFiEspClient client) {
  sendHttpResponse(client, BAD_REQUEST);
}


// HTTP response functions

void sendHttpResponse(WiFiEspClient client, HttpStatus httpStatus)
{
  client.print("HTTP/1.1 ");
  client.println(httpStatusToStr(httpStatus));
  client.println("Content-type:application/json");
  client.println();
}

void sendHttpResponse(WiFiEspClient client, HttpStatus httpStatus, const char* content)
{
  sendHttpResponse(client, httpStatus);
  client.println(content);
  client.println();
}
