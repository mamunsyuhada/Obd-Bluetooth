void RunObd() {
  String battObd = getObdBatt();
  double battResult = StringToDouble(battObd, 32);
  double battVal = testobd(battObd, battResult, 15, 8);
  if (statusTestObd) {
    Serial.println("[Battery]:" + String(battVal, 0) + " V");
  }
}
boolean ConfigOBD() {
  for (int i = 0; i < 10; i++) {
    //    Serial.println("[sw]:" + String(i));
    String answerObd;
    switch (i) {
      case (1): // Reset OBD or Check OBD Version
        Serial.print("[OBD] Version... ");
        answerObd = GetAnswerOBD("AT Z");
        if (answerObd.length() > 0)Serial.println(answerObd);
        else {
          ConfigBluetooth();
          //          i--;
        }
        break;
        return false;
      case (2): // Set communication protocol
        Serial.print("[OBD] Set communication protocol... ");
        answerObd = setProtocol(0);
        if (answerObd == "OK\r") {
          Serial.println(answerObd);
        }
        else {
          i--;
          Serial.println("failed");
        }
        break;
        return false;
      case (3): // Get protocol
        Serial.print("[OBD] The protocol... ");
        answerObd = GetAnswerOBD("AT DP");
        if (answerObd.length() > 0)Serial.println(answerObd);
        else {
          i--;
          Serial.println("not found");
        }
        break;
        return false;
      case (4): // Tries connection
        Serial.print("[OBD] Tries connection... ");
        answerObd = GetAnswerOBD("AT TP 0");
        if (answerObd == "OK\r") {
          Serial.println(answerObd);
        }
        else {
          i--;
          Serial.println("failed");
        }
        break;
        return false;
      case (5): // Get battery mobile
        Serial.print("[OBD] Batt : ");
        answerObd = getObdBatt();
        if (answerObd.length() > 0) {
          Serial.println(answerObd);
        }
        else {
          i--;
          Serial.println("not found");
        }
        return true;
        break;
    }
  }

}

String setProtocol(int protocol) {
  return GetAnswerOBD("AT SP " + String(protocol));
}

String getObdBatt() {
  String result = GetAnswerOBD("AT RV");
  return result.substring(0, result.indexOf("."));
}

String GetAnswerOBD(String cmd) {
  bluetooth.println(cmd);
  String answer = RespondBluetooth();
  answer = answer.substring(answer.indexOf("\n") + 1, answer.indexOf(">") - 1);
  if (answer == "?\r")Serial.println("invalid obd cmd");
  int error = answer.indexOf("RX");
  if (error > 0)setProtocol(0);
  //  Serial.println("[Answer OBD]:" + answer);
  return answer;
}
