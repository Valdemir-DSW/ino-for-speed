void one_cil(){

if (att_rpm > 10){
    
    if (motor_pos ==   0 + fine_pos){
      
      habilitarDriver(1,calc_inje_time());
 }
    if (motor_pos == 360 + calcular_avanco()){
      
      habilitarDriver(5,dwell_time_calc(dwell_time));
 }
     
}


  
}
