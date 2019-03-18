#define bluetooth Serial2
#define keybluetooth 32

void setup() {
  pinMode(keybluetooth, OUTPUT);
  digitalWrite(keybluetooth, HIGH);

  delay(1000);
  /* Begin to init Serial */
  bluetooth.begin(38400);
  Serial.begin(9600);

  /* Start to config Bluetooth HC-05 */
  for (;;) {
    if (ConfigBluetooth())break;
  }
  Serial.println("[Bluetooth] Configured and connected");
}

void loop() {
  /* Connecting to OBD */
  Serial.println("[OBD] Version : " + CheckObdVersion());
  delay(500);

}
