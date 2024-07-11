#include <EEPROM.h>

 void setup(){

 Serial.begin(115200);
 setup_fon();
 loadFromEEPROM();
 bobinasetup();
 
 setupbico();
 

}


void loop(){
  loopbobina();
  loopbico();
loop_fon();
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
