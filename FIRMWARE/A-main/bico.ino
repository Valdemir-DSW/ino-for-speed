// Variáveis para armazenar o tempo de início e o estado do pulso para cada injetor
unsigned long pulseStartTimebb[numCylinders] = {0};
bool pulseActivebb[numCylinders] = {false};

void setupbico() {
  // Configurar os pinos dos injetores como saída e inicializá-los como LOW
  for (int i = 0; i < numCylinders; i++) {
    pinMode(injectorPins[i], OUTPUT);
    digitalWrite(injectorPins[i], LOW);
  }
}

void loopbico() {
  

  // Verificar e ativar os injetores apropriados com base nos ângulos de ativação
  for (int i = 0; i < numCylinders; i++) {
    if (mdegrees == triggerDegreesbb[i]) {
      pulseStartTimebb[i] = millis();
      pulseActivebb[i] = true;
      digitalWrite(injectorPins[i], HIGH);
    }

    // Desativar o injetor após o tempo de injeção especificado
    if (pulseActivebb[i] && (millis() - pulseStartTimebb[i] >= injectionTime)) {
      pulseActivebb[i] = false;
      digitalWrite(injectorPins[i], LOW);
    }
  }
}
