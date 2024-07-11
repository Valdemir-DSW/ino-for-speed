
void serialreceiver() {
  
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {


   
    switch (Serial.read()) {
  
      case 'A':
      
        switch (Serial.read()) {
          case 'B':
            tpsmin = analogRead(APtps);
            error = 0 ;
            saveToEEPROM();
            break;
          case 'C':
             tpsmax = analogRead(APtps);
             saveToEEPROM();
            break;
          default:
            break;
        }
        break;
      case 'B':
        // Lê o número após 'B' e configura a variável 'b'
        if (Serial.available() >= 2) { // Certifica-se de que há pelo menos dois caracteres disponíveis
         // Sensibilidade = Serial.parseInt(); // Lê o número e armazena em 'b'
         // b = constrain(b, 0, 1023); // Garante que o valor esteja dentro do intervalo desejado
          saveToEEPROM();
        }
        break;
      case 'C':
       // botao = 1;
        saveToEEPROM();
        break;
      case 'D':
       // botao = 0;
        saveToEEPROM();
        break;
      case 'E':
       // digital = 1;
        saveToEEPROM();
        break;
      case 'F':
       // digital = 0;
        saveToEEPROM();
        break;
      default:
          error = 1;
        break;
    }
  }
  
}
void semde_data(){

output = String(mapValue) + "," + 
                  String(injectionTime) + "," + 
                  String(tpsPosition) + "," + 
                  String(coolantTemp) + "," + 
                  String(lambdaAFR) + "," + 
                  String(dutyCycle) + "," + 
                  String(batteryVoltage) + "," + 
                  String(error);

  Serial.println(output);
  
}
