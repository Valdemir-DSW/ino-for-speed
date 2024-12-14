volatile unsigned long lastToothTime = 0; 
volatile unsigned long revolutionStartTime = 0;  
volatile int toothCount = 0;                
volatile bool hasSync = false;                 

volatile float rpm = 0.0;                         
volatile float crankAngle = 0.0;               



void setup_fon() {
  //pinMode(sensorPin_fonica, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin_fonica), handleToothSignal, RISING);
}

void loop_fon() {
  noInterrupts();
  bool synced = hasSync;
  interrupts();

  att_rpm = rpm;
  motor_pos = crankAngle;
}

void handleToothSignal() {
  unsigned long currentToothTime = micros();
  unsigned long deltaTime = currentToothTime - lastToothTime;

  static float averageToothTime = 0.0;            
  static int intervalCount = 0;                 
  static bool isInGap = false;                   

  if (!hasSync) {
    // Modo de sincronização inicial
    averageToothTime = (averageToothTime * intervalCount + deltaTime) / (intervalCount + 1);
    intervalCount++;

    if (deltaTime > averageToothTime * 1.8) {    
      hasSync = true;
      revolutionStartTime = currentToothTime;
      toothCount = 0;
      crankAngle = 0.0;                         
      isInGap = false;                           
    }
  } else {
 
    if (deltaTime > averageToothTime * 1.8) {
      // Detecta a falha novamente
      crankAngle = 0.0;                     
      toothCount = 0;                             
      isInGap = true;                             
    } else {
      if (isInGap) {
    
        float anglePerTooth = 360.0 / teethCount;
        crankAngle += anglePerTooth;             
        if (crankAngle >= 360.0) {
          crankAngle -= 360.0;                
        }
      } else {
     
        float anglePerTooth = 360.0 / teethCount;
        crankAngle = (anglePerTooth * toothCount);
      }

     
      toothCount++;
      if (toothCount >= (teethCount - missingToothGap)) {
        // Final da revolução
        unsigned long revolutionDuration = currentToothTime - revolutionStartTime;
        rpm = 60000000.0 / revolutionDuration;

      
        revolutionStartTime = currentToothTime;
        toothCount = 0;
        crankAngle = 0.0;
        isInGap = false;                         
      }
    }
  }


  lastToothTime = currentToothTime;
}
