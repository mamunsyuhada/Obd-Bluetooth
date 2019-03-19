double StringToDouble(String data, int buff) {
  char rawBuff[buff];
  data.toCharArray(rawBuff, sizeof(rawBuff));
  float result = atof(rawBuff);
  return result;
}
