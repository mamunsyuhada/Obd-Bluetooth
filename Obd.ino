String CheckObdVersion() {
  bluetooth.println("ATZ");
  String answer = RespondBluetooth();
  return answer = answer.substring(0, answer.indexOf(">") - 1);
}
