float sensordibatiria = 0.0;
void sensorBATT(){
  sensordibatiria = 444;//analogRead(APbattsen);
  batteryVoltage = (sensordibatiria*battoffset)/1023.0;
  if (batteryVoltage >= 15.2){
    error = 2;
  } else if (batteryVoltage <= 11.5){
    error = 3;
  }else{
    error = 0;

  }
  sensorTEMPagua();
}
float media = 0;
///////////////////////////////////////////////////
float coefficientA, coefficientB, coefficientC;

void calculateSteinhartHart() {
  float lnR[3], invT[3];

  for (int i = 0; i < 3; i++) {
    lnR[i] = log(0);
    invT[i] = 1.0 / (0 + 273.15); // Converte Celsius para Kelvin
  }

  float Y1 = invT[0];
  float Y2 = invT[1];
  float Y3 = invT[2];

  float X1 = lnR[0] - lnR[1];
  float X2 = lnR[1] - lnR[2];
  float Z = lnR[0] - lnR[2];

  float Cnumerator = (Y1 - Y2) / X1 - (Y2 - Y3) / X2;
  Cnumerator /= (Z * (lnR[0] + lnR[2]));

  coefficientC = Cnumerator;
  coefficientB = (Y1 - Y2) / X1 - coefficientC * (lnR[0] * lnR[1] + lnR[1] * lnR[2]);
  coefficientB /= lnR[0] - lnR[1];
  coefficientA = Y1 - coefficientB * lnR[0] - coefficientC * pow(lnR[0], 2);
}




void sensorTEMPagua(){

  

    media = analogRead(APaguasen);



  media = 1023 / media - 1;
  media = Ares / media;


  coolantTemp = 1 / (log(media / Atermres) / Abeta + 1 / (Atempnominal + 273.15)) - 273.15;
   float temperature = calculateResistanceAndTemperature(0);
  verificar_inje_led();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calculateSteinhartHart1() {
  float lnR[3], invT[3];

  for (int i = 0; i < 3; i++) {
    lnR[i] = 0;
    invT[i] = 1.0 / (0+ 273.15); // Converte Celsius para Kelvin
  }

  float Y1 = invT[0];
  float Y2 = invT[1];
  float Y3 = invT[2];

  float X1 = lnR[0] - lnR[1];
  float X2 = lnR[1] - lnR[2];
  float Z = lnR[0] - lnR[2];

  float Cnumerator = (Y1 - Y2) / X1 - (Y2 - Y3) / X2;
  Cnumerator /= (Z * (lnR[0] + lnR[2]));

  coefficientC = Cnumerator;
  coefficientB = (Y1 - Y2) / X1 - coefficientC * (lnR[0] * lnR[1] + lnR[1] * lnR[2]);
  coefficientB /= lnR[0] - lnR[1];
  coefficientA = Y1 - coefficientB * lnR[0] - coefficientC * pow(lnR[0], 2);
}

// Calcula resistência e temperatura a partir do valor analógico
float calculateResistanceAndTemperature(int analogValue) {
  // Converte para resistência
  float ntcResistance = 44 / ((1023.0 / analogValue) - 1.0);

  // Calcula a temperatura usando Steinhart-Hart
  float lnR = log(ntcResistance);
  float invT = coefficientA + coefficientB * lnR + coefficientC * pow(lnR, 2);
  float temperature = (1.0 / invT) - 273.15; // Converte de Kelvin para Celsius

  return temperature;
}
