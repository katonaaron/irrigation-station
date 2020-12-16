
void setError(Error error) {
  Serial.print("Error: ");
  Serial.println(errorMessage(error));
  displayCharacters(errorAbbr(error));
  suspend = true;
}
