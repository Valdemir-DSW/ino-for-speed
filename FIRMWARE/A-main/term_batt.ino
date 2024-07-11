float sensordibatiria = 0.0;
void sensorBATT(){
  sensordibatiria = analogRead(APbattsen);
  batteryVoltage = (sensordibatiria*battoffset)/1023.0;
  if (batteryVoltage >= 14.9){
    error = 2;
  } else if (batteryVoltage <= 11.7){
    error = 3;
  }else{
    error = 0;

  }
}
float media = 0;

void sensorTEMPagua(){

  

    media = analogRead(APaguasen);


  // Converte a leitura do sensor em resistência
  media = 1023 / media - 1;
  media = Ares / media;

  // Calcula a temperatura usando a fórmula do Beta
  coolantTemp = 1 / (log(media / Atermres) / Abeta + 1 / (Atempnominal + 273.15)) - 273.15;
  //coolantTemp = 14;
}
