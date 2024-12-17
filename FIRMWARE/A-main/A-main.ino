#include <EEPROM.h>

 void setup(){

 Serial.begin(115200);
 setup_fon();
 loadFromEEPROM();
 setup_luz_injeao();
 setup_drivers();

}


void loop(){
  

//Os sensores um acaba chamando ficar sobrecarga começamos pelo sensor de map que vai avançando a chamada 
map_sensor();
//roda fonica e sensor O2 com mais prioridade 
loop_fon();
lambdamonit();
//------------------------------------------------
engine_loop();
//------------------------------------------------
if (Serial){
  if (Serial.available() > 0) {
    serialreceiver();
  }else{
    semde_data();
  }
}

//-----------------------------------------------
}
