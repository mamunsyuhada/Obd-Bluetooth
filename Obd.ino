boolean ConfigOBD() {
  for (int i = 0; i < 10; i++) {
    //    Serial.println("[sw]:" + String(i));
    String answerObd;
    switch (i) {
      case (1): // Reset OBD or Check OBD Version
        Serial.print("[OBD] Version... ");
        answerObd = GetAnswerOBD("ATZ");
        if (answerObd.length() > 0)Serial.println(answerObd);
        else {
          ConfigBluetooth();
          //          i--;
        }
        break;
        return false;
      case (2): // Set communication protocol
        Serial.print("[OBD] Set communication protocol... ");
        answerObd = GetAnswerOBD("AT SP 0");
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
      case (4): // Get battery mobile
        Serial.print("[OBD] Batt : ");
        answerObd = GetAnswerOBD("AT RV");
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

String GetAnswerOBD(String cmd) {
  bluetooth.println(cmd);
  String answer = RespondBluetooth();
  answer = answer.substring(answer.indexOf("\n") + 1, answer.indexOf(">") - 1);
  if (answer == "?\r")Serial.println("invalid obd cmd");
  //  Serial.println("[Answer OBD]:" + answer);
  return answer;
}
