const int sensorPin = 1;  // Pino conectado ao sensor

volatile unsigned long lastTime = 0;  // Armazena o último tempo de pulso
volatile unsigned long pulseCount = 0;  // Contagem de pulsos
volatile unsigned long revolutionCount = 0;  // Contagem de revoluções
const unsigned long debounceTime = 1000;  // Tempo de debounce em microssegundos
const unsigned long missingToothTime = 5000 * missingTeeth;  // Tempo para identificar a falha de dentes em microssegundos
volatile bool zeroDetected = false;  // Indica se o ponto zero foi detectado
const int sampleSize = 10;  // Tamanho da janela para a média móvel
double rpmSamples[sampleSize];  // Armazena as amostras de RPM
int sampleIndex = 0;  // Índice da amostra atual

void setupfon() {

  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseISR, RISING);
  for (int i = 0; i < sampleSize; i++) {
    rpmSamples[i] = 0;
  }
}

void loopfon() {
  // Desative interrupções para leitura segura
  noInterrupts();
  unsigned long currentPulseCount = pulseCount;
  unsigned long currentRevolutionCount = revolutionCount;
  unsigned long currentTime = micros();
  interrupts();

  // Calcular tempo desde o último pulso
  unsigned long pulseTime = currentTime - lastTime;

  if (zeroDetected) {
    // Calcular RPM (60.000.000 / (tempo por pulso * número de dentes))
    double rpm = 60000000.0 / (pulseTime * numTeeth);

    // Validar leitura de RPM
    if (rpm > 0 && rpm < 10000) {  // Ajuste conforme necessário para o seu sistema
      // Adicionar a amostra de RPM à janela de média móvel
      rpmSamples[sampleIndex] = rpm;
      sampleIndex = (sampleIndex + 1) % sampleSize;

      // Calcular a média das amostras de RPM
      double avgRpm = 0;
      for (int i = 0; i < sampleSize; i++) {
        avgRpm += rpmSamples[i];
      }
      avgRpm /= sampleSize;

      // Calcular ângulo (720 * (pulsos % número de dentes) / número de dentes)
      double angle = 360.0 * (currentPulseCount % numTeeth) / numTeeth + 360.0 * (currentRevolutionCount % 2);

    //  // Exibir resultados
   //   Serial.print("RPM: ");
    //  Serial.print(avgRpm);
    //  Serial.print("  Angle: ");
     // Serial.println(angle);
     currentAngle = angle;
     rpm = avgRpm;

      // Resetar a detecção do ponto zero se o RPM for zero
      if (avgRpm < 1) {
        zeroDetected = false;
        //Serial.println("RPM zero detectado. Aguardando nova falha de dentes para redefinir o ponto zero.");
      }
    }
  } 
  
}

void pulseISR() {
  unsigned long currentTime = micros();
  // Filtro de debounce: ignora pulsos muito rápidos
  if (currentTime - lastTime > debounceTime) {
    // Verificar se há uma falha de dentes
    if (currentTime - lastTime > missingToothTime) {
      zeroDetected = true;  // Detectar o ponto zero
      pulseCount = 0;       // Resetar a contagem de pulsos
      revolutionCount = 0;  // Resetar a contagem de revoluções
      // Resetar a janela de média móvel
      for (int i = 0; i < sampleSize; i++) {
        rpmSamples[i] = 0;
      }
      sampleIndex = 0;
    }
    // Atualiza o tempo do último pulso
    lastTime = currentTime;
    // Incrementa a contagem de pulsos se o ponto zero já foi detectado
    if (zeroDetected) {
      pulseCount++;
      // Verificar se completou uma revolução
      if (pulseCount % numTeeth == 0) {
        revolutionCount++;
      }
    }
  }
}
