void execute_command(char command[], int command_length) {
  if(strcmp("RNR", command) == 0) {
    Serial.print("+RNR");
    printInt(nrPlants);
    Serial.print("\n");
  }
}
