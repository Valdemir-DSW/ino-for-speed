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
