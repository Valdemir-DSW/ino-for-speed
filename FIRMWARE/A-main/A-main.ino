



void setup(void){
 
 Serial.begin(115200);
 setup_fon();
 loadFromEEPROM();

}


void loop(void){
loop_fon();
serialreceiver();
}
