char incomingChar; // Variável para armazenar o caractere recebido

void serialreceiver() {
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {
    incomingChar = Serial.read(); // Lê o caractere recebido

    // Utiliza a estrutura switch-case para lidar com o caractere recebido
    switch (incomingChar) {
      case 'A':
        // Lê o número após 'A' e configura a variável 'a'
        if (Serial.available() >= 2) { // Certifica-se de que há pelo menos dois caracteres disponíveis
          //alcanse = Serial.parseInt(); // Lê o número e armazena em 'a'
          //a = constrain(a, 0, 1023); // Garante que o valor esteja dentro do intervalo desejado
          saveToEEPROM();
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
        break;
    }
  }
}
