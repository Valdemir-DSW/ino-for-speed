//Variáveis do estado atual do motor com alta taxa de atualização e uso 

int  currentAngle = 0.0; // Ângulo atual em graus
float rpm = 0.0; // Rotação por minuto

const int numCylinders = 8;
const bool evenFire = true; // true para even-fire, false para odd-fire

int triggerDegrees[8];
int triggerDegreesbb[8];
void setupAngles() {
  if (evenFire) {
    if (numCylinders == 1) {
      int tempTriggerDegrees[1] = {0};
      int tempTriggerDegreesbb[1] = {0};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 2) {
      int tempTriggerDegrees[2] = {0, 180};
      int tempTriggerDegreesbb[2] = {0, 180};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 3) {
      int tempTriggerDegrees[3] = {0, 120, 240};
      int tempTriggerDegreesbb[3] = {0, 120, 240};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 4) {
      int tempTriggerDegrees[4] = {0, 0, 0, 0};
      int tempTriggerDegreesbb[4] = {0, 0, 0, 0};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 5) {
      int tempTriggerDegrees[5] = {0, 72, 144, 216, 288};
      int tempTriggerDegreesbb[5] = {0, 72, 144, 216, 288};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 6) {
      int tempTriggerDegrees[6] = {0, 60, 120, 180, 240, 300};
      int tempTriggerDegreesbb[6] = {0, 60, 120, 180, 240, 300};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 7) {
      int tempTriggerDegrees[7] = {0, 51, 102, 153, 204, 255, 306};
      int tempTriggerDegreesbb[7] = {0, 51, 102, 153, 204, 255, 306};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 8) {
      int tempTriggerDegrees[8] = {0, 45, 90, 135, 180, 225, 270, 315};
      int tempTriggerDegreesbb[8] = {0, 45, 90, 135, 180, 225, 270, 315};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    }
  } else {
    if (numCylinders == 1) {
      int tempTriggerDegrees[1] = {0};
      int tempTriggerDegreesbb[1] = {0};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 2) {
      int tempTriggerDegrees[2] = {0, 180};
      int tempTriggerDegreesbb[2] = {0, 180};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 3) {
      int tempTriggerDegrees[3] = {0, 90, 270};
      int tempTriggerDegreesbb[3] = {0, 90, 270};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 4) {
      int tempTriggerDegrees[4] = {0, 90, 180, 270};
      int tempTriggerDegreesbb[4] = {0, 90, 180, 270};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 5) {
      int tempTriggerDegrees[5] = {0, 72, 144, 216, 288};
      int tempTriggerDegreesbb[5] = {0, 72, 144, 216, 288};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 6) {
      int tempTriggerDegrees[6] = {0, 90, 120, 180, 240, 300};
      int tempTriggerDegreesbb[6] = {0, 90, 120, 180, 240, 300};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 7) {
      int tempTriggerDegrees[7] = {0, 51, 153, 204, 255, 306, 357};
      int tempTriggerDegreesbb[7] = {0, 51, 153, 204, 255, 306, 357};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    } else if (numCylinders == 8) {
      int tempTriggerDegrees[8] = {0, 45, 90, 135, 180, 225, 270, 315};
      int tempTriggerDegreesbb[8] = {0, 45, 90, 135, 180, 225, 270, 315};
      for (int i = 0; i < numCylinders; i++) {
        triggerDegrees[i] = tempTriggerDegrees[i];
        triggerDegreesbb[i] = tempTriggerDegreesbb[i];
      }
    }
  }
}

//porteiras

#define APbattsen A0
#define APtps A1
#define APaguasen A3
#define APlambda A4

//lambda
int Lbanda = 0;
float mvwb = 1.0;
float mlwb = 1.47;
float mavwb = 4.0;
float malwb = 18.0;
// bobina

const int pulsePins[numCylinders] = {2, 3, 4, 5, 6, 7, 8, 13};
unsigned long pulseDuration = 4;//dewell
// bicos
const int injectorPins[numCylinders] = {2, 3, 4, 5, 6, 7, 8, 9};
unsigned long injectionTime = 5;
//serial var 22
String output;
//roda fonica
const int numTeeth = 60;  // Quantidade total de dentes no disco
const int missingTeeth = 2;  // Quantidade de dentes faltando para identificar a falha
int battoffset = 15;
//Sensor de agua temperatura 
int  Atermres  = 100000; // Valor do termistor, no caso estamos utilizando um termistor de 100k
int  Atempnominal =  25 ;// Temperatura nominal do NTC utilizado
int  Abeta =  3950 ; // Valor do beta do termistor
int  Ares = 100000 ; // Valor do resistor utilizado em série com o termistor
//Sensores main
int tpsmin = 0;
int tpsmax = 1023;
float mapValue = 20;
float injectionTimevar = 40;
int tpsPosition = 0;
int coolantTemp = 10;
float lambdaAFR = 0.8;
float dutyCycle = 0;
float batteryVoltage = 0;
float error = 0;
