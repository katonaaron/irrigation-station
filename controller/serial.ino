char command[serialCommandLength] = {0};
int command_length = 0;

// the next character is between the '+' and '\n' characters
bool inside = false;

void setupSerial() {
  Serial.begin(baudRate);
}

void serialEvent() {
  if (readCommand()) {
    execute_command(command, command_length);
    command_length = 0;
  }
}

bool readCommand() {
  while (Serial.available()) {
    // get the next character of the message
    char inChar = (char)Serial.read();

    // start of the message
    if (inChar == '+') {
      inside = true;
      continue;
    }

    // invalid message. No starting '+' found.
    if (!inside) {
      continue;
    }

    // if the incoming character is a newline the message ends
    if (inChar == '\n') {
      command[command_length++] = 0;
      inside = false;
      return true;
    }

    // add the character to the message:
    command[command_length++] = inChar;
  }
  return false;
}

void printInt(int num) {
  Serial.write((byte*)num, sizeof(int));
}
