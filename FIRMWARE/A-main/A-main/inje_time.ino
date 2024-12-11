 

float calc_inje_time(){
  float carga_bruta = calc_ve_1(att_rpm,mapValue);
  float carga_liza = enrikegama(carga_bruta);
  float D = (cen_per_ms * carga_liza) / 100.0;
  dutyCycle = ( D / 44) * 100.0;
  injectionTime = D;
  return D;
  
}
