void one_cil(){
  if (motor_pos ==   0){
    
    habilitarDriver(1,calc_inje_time());
  }
  if (motor_pos == 180 + calcular_avanco()){
    
    habilitarDriver(5,dwell_time_calc(dwell_time));
  }



motor_pos = motor_pos +1;
if (motor_pos > 10){
  motor_pos = 0;
}
  
}
