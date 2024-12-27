

float calc_inje_time() {
  float carga_bruta;
  if (matematica == 1) {
    
    if (att_ve_shitch == 1) {
      carga_bruta = calc_ve_1(att_rpm, mapValue);
    } else if (att_ve_shitch == 1) {
      carga_bruta = calc_ve_2(att_rpm, mapValue);
    }
  } else if (matematica == 2) {
   
      carga_bruta = calc_ve_2d(mapValue);
    
  } else if (matematica == 3) {
    carga_bruta = calc_ve_tps(tpsPosition);
  }

  float carga_liza = enrikegama(carga_bruta);
  float D = (cen_per_ms * carga_liza) / 100.0;
  dutyCycle = ( D / 44) * 100.0;
  injectionTime = D;
  return D;

}
