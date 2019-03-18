#define bluetooth Serial2
#define keybluetooth 32

int addrArr[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};

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
  /* Connecting to OBD */
  for (;;) {
    if (ConfigOBD())break;
  }
}

void loop() {
  delay(500);
  Serial.println("I'm Loop");
}
