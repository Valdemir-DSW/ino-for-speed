volatile unsigned long lastToothTime = 0;
volatile unsigned long revolutionStartTime = 0;
volatile int toothCount = 0;
volatile bool hasSync = false;
volatile unsigned long lastSignalTime = 0; // Marca o último momento em que houve sinal.
const unsigned long signalTimeout = 1000000; // 1 segundo (em microssegundos)

volatile float rpm = 0.0;
volatile float crankAngle = 0.0;




void setup_fon() {
  attachInterrupt(digitalPinToInterrupt(sensorPin_fonica), handleToothSignal, RISING);
}

void loop_fon() {
  noInterrupts();
  unsigned long currentTime = micros();
  bool synced = hasSync;
  interrupts();

  // Atualiza os valores
  att_rpm = rpm;
  motor_pos = crankAngle;

  // Verifica timeout para perda de sinal
  if ((currentTime - lastSignalTime) > signalTimeout) {
    rpm = 0.0;      // Zera o RPM
    hasSync = false; // Perde a sincronização
  }
}


void handleToothSignal() {
  unsigned long currentToothTime = micros();
  lastSignalTime = currentToothTime; // Atualiza o tempo do último sinal
  
  unsigned long deltaTime = (currentToothTime >= lastToothTime) ? 
                            (currentToothTime - lastToothTime) : 
                            (currentToothTime + (4294967295UL - lastToothTime));

  static float averageToothTime = 1000.0;
  static int intervalCount = 0;

  if (!hasSync) {
    if (deltaTime > 0 && deltaTime < 100000) {
      averageToothTime = (averageToothTime * intervalCount + deltaTime) / (intervalCount + 1);
      intervalCount++;
    }

    if (deltaTime > averageToothTime * missingToothGap * 1.5) {
      hasSync = true;
      revolutionStartTime = currentToothTime;
      toothCount = angulo_ps_falha;
      crankAngle = angulo_ps_falha;
      motor_pos_total = angulo_ps_falha;
    }
  } else {
    if (deltaTime > averageToothTime * missingToothGap * 1.5) {
      toothCount += missingToothGap;
      if (toothCount >= teethCount) {
        toothCount -= teethCount;
        motor_pos_total += 720.0;
      }
    } else {
      toothCount++;
      if (toothCount >= teethCount) {
        toothCount -= teethCount;
        motor_pos_total += 720.0;
      }
    }

    crankAngle = (toothCount % teethCount) * (360.0 / teethCount);

    if (toothCount == 0) {
      unsigned long revolutionDuration = (currentToothTime >= revolutionStartTime) ? 
                                          (currentToothTime - revolutionStartTime) : 
                                          (currentToothTime + (4294967295UL - revolutionStartTime));
      if (revolutionDuration > 0)
        rpm = 60000000.0 / revolutionDuration;
      revolutionStartTime = currentToothTime;
    }
  }

  lastToothTime = currentToothTime;
}
