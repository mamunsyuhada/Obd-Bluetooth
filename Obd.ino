void RunObd() {
  String battObd = getObdBatt();
  double battResult = StringToDouble(battObd, 32);
  double battVal = testobd(battObd, battResult, 15, 8);
  if (statusTestObd) {
    Serial.println("[Battery]:" + String(battVal, 0) + " V");
  }

  String rpmObd = getValueObd(PID_RPM, 0);
  double rpmResult = StringToDouble(rpmObd, 32);
  double rpmVal = testobd(rpmObd, rpmResult, 9000, 100);
  if (statusTestObd) {
    Serial.println("[RPM]:" + String(rpmVal, 0) + " x");
  }

  String engineLoadObd = getValueObd(PID_ENGINE_LOAD, 0);
  double engineLoadResult = StringToDouble(engineLoadObd, 32);
  double engineLoadVal = testobd(engineLoadObd, engineLoadResult, 0, 100);
  if (statusTestObd) {
    Serial.println("[Engine Load]:" + String(engineLoadVal, 0) + " x");
  }

  String speedObd = getValueObd(PID_SPEED, 0);
  double speedResult = StringToDouble(speedObd, 32);
  double speedVal = testobd(speedObd, speedResult, 0, 100);
  if (statusTestObd) {
    Serial.println("[Speed]:" + String(speedVal, 0) + " KMph");
  }

  String coolantObd = getValueObd(PID_COOLANT_TEMP, 0);
  double coolantResult = StringToDouble(coolantObd, 32);
  double coolantVal = testobd(coolantObd, coolantResult, 0, 100);
  if (statusTestObd) {
    Serial.println("[Coolant Temp]:" + String(coolantVal, 0) + " °C");
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

String getValueObd(byte PID, int timeout) {
  int value;
  boolean status = obd.readPID(PID, value);
  delay(timeout);
  if (status) {
    return String(value);
  }
  else {
    return "timeout";
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
