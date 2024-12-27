void saveToEEPROM() {
  EEPROM.write(0, tpsmin);
  EEPROM.write(1, tpsmax);
  EEPROM.write(2, angulo_ps_falha);
  EEPROM.write(3, teethCount);
  EEPROM.write(4, missingToothGap);
  EEPROM.write(5, invertRPM);
  EEPROM.write(6, map_zeroV);
  EEPROM.write(7, map_cincoV);
  EEPROM.write(8, matematica);
  save_matriz_ve1EEPROM(9);
  save_matriz_ve1EEPROM(809);
  EEPROM.write(810, ve_shitch_ops);
  EEPROM.write(811, ve_shitch_arg);
}

void loadFromEEPROM() {
  tpsmin = EEPROM.read(0);
  tpsmax = EEPROM.read(1);
  angulo_ps_falha = EEPROM.read(2);
  teethCount = EEPROM.read(3);
  missingToothGap = EEPROM.read(4);
  invertRPM = EEPROM.read(5);
  map_zeroV = EEPROM.read(6);
  map_cincoV = EEPROM.read(7);
  matematica = EEPROM.read(8);
  load_matriz_ve1FromEEPROM(9);
  load_matriz_ve2FromEEPROM(809);
  ve_shitch_arg = EEPROM.read(810);
  ve_shitch_ops = EEPROM.read(811);
}
