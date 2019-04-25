#define bluetooth Serial2
#define keybluetooth 32

#define TINY_GSM_MODEM_SIM808
#include <TinyGsmClient.h>

boolean isObdConnected = false;

uint32_t rateBluetooth = 0;
int addrArr[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};

#include <TeensyThreads.h>
void setup() {
  pinMode(keybluetooth, OUTPUT);
  digitalWrite(keybluetooth, HIGH);

  delay(1000);
  /* Begin to init Serial */
  if (!rateBluetooth) {
    rateBluetooth = TinyGsmAutoBaud(bluetooth);
  }
  Serial.begin(9600);

  delay(1000);
  threads.addThread(cobaThreads, 1);
}

void cobaThreads(void) {
  while (1) {
    Serial.println("Teensy Thread");
    delay(400);
  }
  threads.yield();
}

void loop() {
  if (isObdConnected) {
    Serial.println("RPM : " + String(readObdPID("0C")));
    Serial.println("Speed : " + String(readObdPID("0D")));
    Serial.println("Engine Load : " + String(readObdPID("04")));
    Serial.println("Coolant : " + String(readObdPID("05")));
  }
  else {
    connectToObdBridge();
  }
}
