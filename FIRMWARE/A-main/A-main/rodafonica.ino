
volatile int pulseCount = 0;
unsigned long lastPulseTime = 0;  // Tempo do último pulso
unsigned long currentTime = 0;  // Tempo atual
unsigned long interval = 0;  // Intervalo entre os pulsos
unsigned long referenceIntervalThreshold = 1000;  // Threshold para identificar o ponto de referência (em microssegundos)


const int effectiveTeeth = totalTeeth - missingTeeth;  // Dentes efetivos para contagem de pulsos
bool referenceDetected = false;  // Flag para verificar se o ponto de referência foi detectado

void setup_fon(){

  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING); 
}

void loop_fon(){
 
 currentTime = millis();
  
  // Calcule o RPM a cada 1 segundo
  if (currentTime - lastPulseTime >= 1000) {  // Corrigido: use lastPulseTime em vez de lastTime
    att_rpm = (pulseCount * 60) / effectiveTeeth;
    motor_pos = (pulseCount % effectiveTeeth) * (360.0 / effectiveTeeth);
    

    
    // Reset para o próximo cálculo
    pulseCount = 0;
    lastPulseTime = currentTime;
  }
}
void countPulse() {
  currentTime = micros();  // Captura o tempo do pulso em microssegundos
  interval = currentTime - lastPulseTime;  // Calcula o intervalo entre os pulsos

  if (interval > referenceIntervalThreshold && !referenceDetected) {
    
    
    // Aqui definimos o primeiro dente após o espaço vazio como 0°
    pulseCount = 0;  // Reset da contagem de pulsos para 0
    referenceDetected = true;  // Marca que o ponto de referência foi detectado
    
    // Ajusta a posição para 0 graus (primeiro dente após o espaço vazio)
    motor_pos = 0;
  }
  
  // Se o ponto de referência já foi detectado, continuamos a contagem normalmente
  if (referenceDetected) {
    pulseCount++;
    motor_pos = (pulseCount % effectiveTeeth) * (360.0 / effectiveTeeth);
  }

  // Atualiza o tempo do último pulso
  lastPulseTime = currentTime;
}
