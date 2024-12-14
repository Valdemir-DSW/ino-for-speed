int currentRow = 0;
void serialreceiver() {
  
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {


   
    switch (Serial.read()) {
  
      case 'A':
      
        switch (Serial.read()) {
          case 'B':
            tpsmin = analogRead(APtps);
          
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
          switch (Serial.read()) {
          case 'A':
                     // Sensibilidade = Serial.parseInt(); // Lê o número e armazena em 'b'
                   // b = constrain(b, 0, 1023); // Garante que o valor esteja dentro do intervalo desejado
                      String line = Serial.readStringUntil('\n');
                        line.trim();
                        if (line == "START") {
                          currentRow = 0;
                        } else if (line == "END") {
                          //Serial.println("Data reception completed");
                          // Opcional: Processar ou verificar os dados
                        } else if (currentRow < 20) {
                          int colIndex = 0;
                          char *token = strtok(const_cast<char *>(line.c_str()), ",");
                          while (token != nullptr && colIndex < 20) {
                            //matriz_ve1[currentRow][colIndex] = atof(token);
                            token = strtok(nullptr, ",");
                            colIndex++;
                          }
                          currentRow++;
                        }
                    saveToEEPROM();
                  
            break;
        
          default:
          
            break;
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
                  String(error)+ "," + 
                  String(att_rpm);

  Serial.println(output);
  
}
