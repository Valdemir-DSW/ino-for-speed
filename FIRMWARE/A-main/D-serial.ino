int currentRow = 0;
String dadosRecebidos;
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
           case 'D':
             dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha
    


          
             sscanf(dadosRecebidos.c_str(), "%d,%d,%d,%d", &teethCount, &missingToothGap, &angulo_ps_falha, &invertRPM);
             saveToEEPROM();
            break;
            case 'E':
             dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha
           
           // sscanf(dadosRecebidos.c_str(), "%d,%d,%[^,],%[^,],%[^,],%d,%d,%[^,],%d", 
           //    &cilindros, &tempoBico, ordemIgnicao.c_str(), evenOdd.c_str(), centelhaPerdida.c_str(), 
            //   &cilindrada, &afr, injetor.c_str());

            sscanf(dadosRecebidos.c_str(), "%d,%d",&map_zeroV, &map_cincoV);
             saveToEEPROM();
            break;
            case 'F':
             dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha
           
           
            sscanf(dadosRecebidos.c_str(), "%d,%d", &map_zeroV, &map_cincoV);
            
             saveToEEPROM();
            break;
            case 'G':
             reset_fact();
            
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
                             update_matriz_ve1(currentRow,colIndex,atof(token));
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
                  String(att_rpm) ;

  Serial.println(output);
  
}
