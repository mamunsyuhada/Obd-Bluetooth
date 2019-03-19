#define bluetooth Serial2
#define keybluetooth 32

#include <OBD2UART.h>
COBD obd;

boolean statusTestObd = 0;

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
  Serial.println("[OBD] Configured and connected");
}

void loop() {
  //TODO
  /* Acquisition PID value */
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


  //  String engineLoad = GetAnswerOBD("01 04");
  //  Serial.println("[Engine Load] : " + engineLoad);
  //  engineLoad = engineLoad.substring(6, engineLoad.length()-1);
  //  Serial.print("Engine Load }}");
  //  Serial.println(engineLoad);
  //  String coolantTemp = GetAnswerOBD("01 05");
  //  Serial.println("[Coolant Temperature] : " + coolantTemp);
  //  String rpm = GetAnswerOBD("01 0C");
  //  Serial.println("[rpm] : " + rpm);
  //  String velocity = GetAnswerOBD("01 0D");
  //  Serial.println("[velocity] : " + velocity);
  //  String rpmObd = getValueObd(PID_RPM, 0);
  //  double rpmTest = StringToDouble(rpmObd, 32);
  //  int rpmVal;
  //  if (testobd(rpmObd, rpmVal, 9000, 100)) {
  //    Serial.println("[OBD]" + String(rpmVal));
  //  }

  //  String coolantObd = getValueObd(PID_COOLANT_TEMP, 0);
  //  Serial.println("[Coolant]:" + coolantObd);
  //  String speedObd = getValueObd(PID_SPEED, 0);
  //  Serial.println("[Speed]:" + speedObd);
  delay(500);
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
