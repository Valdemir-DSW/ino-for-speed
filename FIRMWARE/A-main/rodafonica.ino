volatile unsigned long lastToothTime = 0;
volatile unsigned long revolutionStartTime = 0;
volatile int toothCount = 0;
volatile bool hasSync = false;


volatile float rpm = 0.0;
volatile float crankAngle = 0.0;


const unsigned long sensorTimeout = 1500000;  // Tempo limite para sinal do sensor (1.5s)
float expectedAngleAfterGap = 0.0;  // Ângulo esperado após a falha

void setup_fon() {
  attachInterrupt(digitalPinToInterrupt(sensorPin_fonica), handleToothSignal, RISING);
}

void loop_fon() {
  unsigned long currentTime = micros();

 

  noInterrupts();
  bool synced = hasSync;
  interrupts();

  att_rpm = rpm;
  motor_pos = crankAngle;
}

void handleToothSignal() {
  unsigned long currentToothTime = micros();
  unsigned long deltaTime = currentToothTime - lastToothTime;

  static float averageToothTime = 0.0;  // Tempo médio entre dentes
  static int intervalCount = 0;
  static bool isInGap = false;

  // Se ainda não sincronizado, calcular o tempo médio entre dentes
  if (!hasSync) {
    averageToothTime = (averageToothTime * intervalCount + deltaTime) / (intervalCount + 1);
    intervalCount++;

    // Detectar lacuna com base na proporção do tempo
    if (deltaTime > averageToothTime * missingToothGap) {
      hasSync = true;
      revolutionStartTime = currentToothTime;
      toothCount = 0;
      crankAngle = angulo_ps_falha;
      motor_pos_total = angulo_ps_falha;
      expectedAngleAfterGap = (360.0 / teethCount) * missingToothGap;
      isInGap = false;
    }
  } else {
    // Verificar se o tempo atual indica uma lacuna
    if (deltaTime > averageToothTime * missingToothGap) {
      isInGap = true;

      // Calcular o ângulo dinamicamente durante a lacuna
      float anglePerTooth = 360.0 / teethCount;
      crankAngle += anglePerTooth * missingToothGap;
      if (crankAngle >= 360.0) {
        crankAngle -= 360.0;
      }

      // Verificar se o ângulo calculado após a lacuna corresponde ao esperado
      if (fabs(crankAngle - expectedAngleAfterGap) > 1.0) {  // Tolerância de 1 grau
        error = 7;  // Sinalizar erro
        hasSync = false;  // Desativar sincronização
        return;
      }
    } else {
      // Atualizar o ângulo com base no tempo entre dentes
      float anglePerMicrosecond = 360.0 / (teethCount * averageToothTime);
      crankAngle += deltaTime * anglePerMicrosecond;
      motor_pos_total += deltaTime * anglePerMicrosecond;
      if (crankAngle >= 360.0) {
        crankAngle -= 360.0;
      }
      if (motor_pos_total >= 720.0) {
        motor_pos_total -= 720.0; // Manter total dentro de um ciclo de 720°
      }

      isInGap = false;
    }

    // Incrementar a contagem de dentes se não estiver na lacuna
    if (!isInGap) {
      toothCount++;
    }

    // Calcular RPM no final da revolução
    if (toothCount >= (teethCount - missingToothGap)) {
      unsigned long revolutionDuration = currentToothTime - revolutionStartTime;
      rpm = 60000000.0 / revolutionDuration;  // Calcular RPM em minutos

      revolutionStartTime = currentToothTime;
      toothCount = 0;
      crankAngle = 0.0;
    }
  }

  lastToothTime = currentToothTime;
}
