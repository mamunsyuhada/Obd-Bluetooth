#define bluetooth Serial2
#define keybluetooth 32

#define TINY_GSM_MODEM_SIM808
#include <TinyGsmClient.h>

boolean statusTestObd = 0;

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
  //TODO
  /* Acquisition PID value */
  //  RunObd();

  bluetooth.println("01 0C");
  String answerRpm = RespondBluetooth();
  int posRpm = answerRpm.indexOf("41 0C");
  if (posRpm == 7) {
    //    Serial.print("RPM Hex:");
    answerRpm = answerRpm.substring(posRpm, answerRpm.lastIndexOf("\n"));
    answerRpm = answerRpm.replace("41 0C", "");
    answerRpm = answerRpm.replace("\n", "");
    answerRpm = answerRpm.replace(" ", "");
    answerRpm = answerRpm.replace("\r", "");

    unsigned int rpm = hexToDec(answerRpm) / 4;
    if (rpm > 0 and rpm < 10000) {
      Serial.print("RPM: ");
      Serial.print(rpm);
      Serial.println(" x");
    }
  }

  bluetooth.println("01 0D");
  String answerFuel = RespondBluetooth();
  int posFuel = answerFuel.indexOf("41 0D");
  if (posFuel == 7) {
    answerFuel = answerFuel.substring(posFuel, answerFuel.lastIndexOf("\n"));
    answerFuel = answerFuel.replace("41 0D", "");
    answerFuel = answerFuel.replace("\n", "");
    answerFuel = answerFuel.replace(" ", "");
    answerFuel = answerFuel.replace("\r", "");
    unsigned int fuel = hexToDec(answerFuel);
    Serial.print("Fuel: ");
    Serial.print(fuel);
    Serial.println(" %");
  }

  bluetooth.println("01 04");
  String answerEngineLoad = RespondBluetooth();
  int posEngineLoad = answerEngineLoad.indexOf("41 04");
  if (posFuel == 7) {
    answerEngineLoad = answerEngineLoad.substring(posEngineLoad, answerEngineLoad.lastIndexOf("\n"));
    answerEngineLoad = answerEngineLoad.replace("41 04", "");
    answerEngineLoad = answerEngineLoad.replace("\n", "");
    answerEngineLoad = answerEngineLoad.replace(" ", "");
    answerEngineLoad = answerEngineLoad.replace("\r", "");
    unsigned long engineLoad = hexToDec(answerEngineLoad);
    Serial.print("Engine Load: ");
    Serial.print(engineLoad);
    Serial.println(" %");
  }

  bluetooth.println("01 05");
  String answerCoolant = RespondBluetooth();
  int posCoolant = answerCoolant.indexOf("41 05");
  if (posCoolant == 7) {
    answerCoolant = answerCoolant.substring(posCoolant, answerCoolant.lastIndexOf("\n"));
    answerCoolant = answerCoolant.replace("41 05", "");
    answerCoolant = answerCoolant.replace("\n", "");
    answerCoolant = answerCoolant.replace(" ", "");
    answerCoolant = answerCoolant.replace("\r", "");
    unsigned long coolant = hexToDec(answerCoolant);
    Serial.print("Coolant Temperature: ");
    Serial.print(coolant);
    Serial.println(" °C");
  }
}

double testobd(String resultObd, double resultVal,
               double maxVal, double minVal) {
  for (int i = 0; i < 4; i++) {
    switch (i) {
      case (1):
        if (resultObd == "timeout")statusTestObd = false;
        break;
      case (2):
        if (resultVal < 0)statusTestObd = false;
        break;
      case (3):
        if (resultVal < maxVal and resultVal > minVal) {
          statusTestObd = true;
          return resultVal;
        }
        break;
    }
  }
}
