String CheckObdVersion() {
  bluetooth.println("ATZ");
  return RespondBluetooth();
}
