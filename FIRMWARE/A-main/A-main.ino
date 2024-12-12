#include <EEPROM.h>

 void setup(){

 Serial.begin(115200);
 setup_fon();
 loadFromEEPROM();
 setup_luz_injeao();
 setup_drivers();

}


void loop(){
//loop_fon();
map_sensor();
tpshande();
sensorBATT();
sensorTEMPagua();
verificar_inje_led();
one_cil();
lambdamonit();
  if (Serial.available() > 0) {
    serialreceiver();
  }else{
    semde_data();
  }
}
