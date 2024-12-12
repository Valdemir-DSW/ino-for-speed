// Variáveis para armazenar o tempo de início e o estado do pulso para cada porta
unsigned long pulseStartTime[8] = {0};
bool pulseActive[8] = {false};

void bobinasetup() {
  // Configurar os pinos das portas como saída e inicializá-los como LOW
  for (int i = 0; i < numCylinders; i++) {
    pinMode(pulsePins[i], OUTPUT);
    digitalWrite(pulsePins[i], LOW);
  }
}

void loopbobina() {
  // Incrementar e voltar a 0 após 360 graus
  currentAngle = (currentAngle + 1) % 361;

  // Verificar e ativar as portas apropriadas com base nos ângulos de ativação
  for (int i = 0; i < numCylinders; i++) {
    if (currentAngle == triggerDegrees[i]) {
      pulseStartTime[i] = millis();
      pulseActive[i] = true;
      digitalWrite(pulsePins[i], HIGH);
    }
    if (pulseActive[i] && (millis() - pulseStartTime[i] >= pulseDuration)) {
      pulseActive[i] = false;
      digitalWrite(pulsePins[i], LOW);
    }
  }
}
