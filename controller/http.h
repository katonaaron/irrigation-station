#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

enum HttpStatus {
  OK = 200,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405
};

const char* httpStatusToStr(enum HttpStatus httpStatus) {
  switch(httpStatus) {
    case OK:
      return "200 OK";
    case BAD_REQUEST:
      return "400 Bad Request";
    case NOT_FOUND:
      return "404 Not Found";
    case METHOD_NOT_ALLOWED:
      return "405 Method Not Allowed";
    default: 
      return "";
  }
}

#endif
