void connectToObdBridge() {
  /* Start to config Bluetooth HC-05 */
  for (;;) {
    if (ConfigBluetooth())break;
  }
  Serial.println("[Bluetooth] Configured and connected");

  delay(1000);
  /* Connecting to OBD */
  for (;;) {
    if (ConfigOBD())break;
  }
  Serial.println("[OBD] Configured and connected");
  bluetooth.println("01 00");
  isObdConnected = true;
}

unsigned int readObdPID(String pid) {
  unsigned int result = 0;

  bluetooth.println("01 " + pid);
  String answer = RespondBluetooth();

  int statusConnectObd = answer.indexOf(">");
  if (statusConnectObd > 0) {
    Serial.println("Obd Connected");
    isObdConnected = true;
  }
  else {
    Serial.println("Obd not connected");
    isObdConnected = false;
  }

  int pos = answer.indexOf("41 " + pid);
  if (pos == 7) {
    answer = answer.substring(pos, answer.lastIndexOf("\n"));
    answer = answer.replace("41 " + pid, "");
    answer = answer.replace("\n", "");
    answer = answer.replace(" ", "");
    answer = answer.replace("\r", "");
    result = hexToDec(answer);
  }
  else result = 0;

  return result;
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
