boolean ConfigOBD() {
  for (int i = 0; i < 10; i++) {
    switch (i) {
      case (1): // Set as default
        ObdDefault();
        return false;
        break;
    }
  }
}

String AnswerOBD() {
  String answer = RespondBluetooth();
  answer = answer.substring(answer.indexOf("\n") + 1, answer.indexOf(">") - 1);
  Serial.println("[Answer OBD]:" + answer);
  return answer;
}

String CheckObdVersion() {
  bluetooth.println("ATZ");
  return AnswerOBD();
}

boolean ObdDefault() {
  bluetooth.println("ATD");
  if (AnswerOBD() == "OK")return true;
  else return false;
}
