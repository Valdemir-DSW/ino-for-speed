void engine_loop(){
  switch (cylinder) {
  case 1:
    one_cil();
    
    break;
  case 2:
    Serial.println("Comando 2");
    break;
  case 3:
    Serial.println("Comando 3");
    break;
  case 4:
    Serial.println("Comando 1");
    break;
  case 5:
    Serial.println("Comando 2");
    break;
  case 6:
    Serial.println("Comando 3");
    break;
  case 7:
    Serial.println("Comando 2");
    break;
  case 8:
    Serial.println("Comando 3");
    break;
  default:
    error = 6;
    break;
}

}


///////////////////////////////////////////////////////////////////////////////////////////

void one_cil(){

if (att_rpm > 10){
    
    if (motor_pos ==   0 + fine_pos){
      
      habilitarDriver(1,calc_inje_time());
 }
    if (motor_pos == 360 + calcular_avanco()){
      
      habilitarDriver(5,dwell_time_calc(dwell_time));
 }
     
}else{
  injectionTime = 0;
}


  
}
///////////////////////////////////////////////////////////////////////////////////////////
void two_cil(){

if (att_rpm > 10){
    
    if (motor_pos ==   0 + fine_pos){
      
      habilitarDriver(1,calc_inje_time());
 }
    if (motor_pos == 360 + calcular_avanco()){
      
      habilitarDriver(5,dwell_time_calc(dwell_time));
 }
     
}


  
}
