

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

            sscanf(dadosRecebidos.c_str(), "%d,%d", &map_zeroV, &map_cincoV);
            saveToEEPROM();
            break;
          case 'F':
            dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha


            sscanf(dadosRecebidos.c_str(), "%d,%d", &map_zeroV, &map_cincoV);

            saveToEEPROM();
            break;
          case 'G':
            // reset_fact();

            saveToEEPROM();
            break;
          case 'H':
            dadosRecebidos = Serial.readStringUntil('\n');  // Lê os dados até o final da linha
            mapa_dweel(dadosRecebidos);  // Processa os dados recebidos


            saveToEEPROM();
            break;
          case 'I':
            dadosRecebidos = Serial.readStringUntil('\n');  // Lê os dados até o final da linha
            up_tps_map(dadosRecebidos);


            break;
          case 'J':
            dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha


            sscanf(dadosRecebidos.c_str(), "%d,%d", &ve_shitch_ops, &ve_shitch_arg);

            saveToEEPROM();
            break;
          case 'K':
            dadosRecebidos = Serial.readStringUntil('\n');  // Lê os dados até o final da linha
            up_2d_map(dadosRecebidos);


            break;
           case 'L':
            //polir!
            break;
          default:
            break;
        }
        break;
      case 'B':
        switch (Serial.read()) {
          case 'A':


           
            update_matriz_ve1(Serial.readStringUntil('\n'));


            break;
            case 'C':


           
            update_matriz_ve2(Serial.readStringUntil('\n'));


            break;

          default:

            break;
        }

        break;
      case 'C':
        switch (Serial.read()) {
          case 'A':
            dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha


            sscanf(dadosRecebidos.c_str(), "%d,%d", &oil_zeroV, &oil_cincoV);

            saveToEEPROM();
            break;
          case 'B':
            dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha


            sscanf(dadosRecebidos.c_str(), "%d,%d,%d,%d%,d", &Lbanda, &mvwb, &mlwb, &mavwb, &malwb);

            saveToEEPROM();
            break;
          case 'D':
            matematica = Serial.readStringUntil('\n').toInt();  // Leia até nova linha

            saveToEEPROM();
            break;
            case 'E':
            dadosRecebidos = Serial.readStringUntil('\n');  // Leia até nova linha


            sscanf(dadosRecebidos.c_str(), "%d,%d", &ve_shitch_ops, &ve_shitch_arg);

            saveToEEPROM();
            break;
          default:

            break;
        }
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
void semde_data() {

  output =          String(mapValue) + "," +
                    String(injectionTime) + "," +
                    String(tpsPosition) + "," +
                    String(coolantTemp) + "," +
                    String(lambdaAFR) + "," +
                    String(dutyCycle) + "," +
                    String(batteryVoltage) + "," +
                    String(error) + "," +
                    String(att_rpm) ;

  Serial.println(output);

}
