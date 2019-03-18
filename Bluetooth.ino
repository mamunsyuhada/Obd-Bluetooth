boolean CommandBluetooth(String command) {
  bluetooth.println(command);
  String answer = RespondBluetooth();
  //  Serial.println(answer);
  int pos = answer.indexOf("\n");
  answer = answer.substring(0, answer.length() - 2);
  boolean status = answer == "OK";
  if (!status) return false; //Serial.println("AT Ok");
  else return true;
}

String RespondBluetooth() {
  while (!bluetooth.available()) {}
  return bluetooth.readString();
}

boolean ConfigBluetooth() {
  int uuidArr[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
  String idBt = String(uuidArr[0]);
  idBt       += String(uuidArr[1]);
  idBt       += String(uuidArr[2]);
  idBt       += String(uuidArr[3]);
  idBt       += ",";
  idBt       += String(uuidArr[4]);
  idBt       += String(uuidArr[5]);
  idBt       += ",";
  idBt       += String(uuidArr[6]);
  idBt       += String(uuidArr[7]);
  idBt       += String(uuidArr[8]);
  idBt       += String(uuidArr[9]);
  idBt       += String(uuidArr[10]);
  idBt       += String(uuidArr[11]);

  String sequenceBt[10] = {
    "AT",
    "AT+RESET",
    "AT+NAME",
    "AT+ROLE",
    "AT+CMODE",
    "AT+BIND",
    "AT+INIT",
    "AT+PAIR",
    "AT+LINK"
  };

  for (int i = 0; i < 10; i++) {
    switch (i) {
        boolean statusBt;
      case (1): // Test AT
        Serial.print("[HC05] Testing AT... ");
        statusBt = CommandBluetooth(sequenceBt[0]);
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (2): // Setel pabrikan
        Serial.print("[HC05] Resetting ... ");
        statusBt = CommandBluetooth(sequenceBt[1]);
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (3): // Set Name
        Serial.print("[HC05] Set Name to Matador... ");
        statusBt = CommandBluetooth(String(sequenceBt[2]) + "=Matador-Telemetry");
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (4): // Set Master Mode
        Serial.print("[HC05] Set role to MASTER... ");
        statusBt = CommandBluetooth(String(sequenceBt[3]) + "=1");
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (5): // Set Master Mode
        Serial.print("[HC05] Set mode to fixed address mode... ");
        statusBt = CommandBluetooth(String(sequenceBt[4]) + "=0");
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (6): // Set Fixed Address Mode
        Serial.print("[HC05] Binding to " + idBt + " ... ");
        statusBt = CommandBluetooth(String(sequenceBt[5]) + "=" + idBt);
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (7): // Initializing to SPP
        Serial.print("[HC05] Initializing to Serial Port Protocol... ");
        statusBt = CommandBluetooth(String(sequenceBt[6]));
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (8): // Pairing to address fixed
        Serial.print("[HC05] Pairing to " + idBt + "... ");
        statusBt = CommandBluetooth(String(sequenceBt[7]) + "=" + idBt + ",10");
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return false;
      case (9): // Connecting to address
        Serial.print("[HC05] Connecting to " + idBt + "... ");
        statusBt = CommandBluetooth(String(sequenceBt[8]) + "=" + idBt);
        if (!statusBt) {
          Serial.println("failed");
          i--;
        } else Serial.println("ok");
        break;
        return true;
      default: break;
    }
  }
}
