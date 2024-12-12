#include <EEPROM.h>

 void setup(){

 Serial.begin(115200);
 setupfon();
 loadFromEEPROM();
 bobinasetup();
  setupAngles(); // Adicionar esta linha
 
 setupbico();
 

}


void loop(){
  loopbobina();
  loopbico();
loopfon();
tpshande();
sensorBATT();
sensorTEMPagua();
lambdamonit();
  if (Serial.available() > 0) {
    serialreceiver();
  }else{
    semde_data();
  }
}
