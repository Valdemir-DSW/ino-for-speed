void saveToEEPROM() {
 EEPROM.write(0, tpsmin);
 EEPROM.write(1, tpsmax);
 // EEPROM.write(2, botao);
 // EEPROM.write(3, digital);
 // EEPROM.write(4, variable);
 // EEPROM.write(5, colorValue);
 //// EEPROM.write(6, agp);
 // EEPROM.write(7, bgp);
  
}

void loadFromEEPROM() {
  tpsmin = EEPROM.read(0);
  tpsmax = EEPROM.read(1);
 // botao = EEPROM.read(2);
 // digital = EEPROM.read(3);
 // variable = EEPROM.read(4);
//  colorValue = EEPROM.read(5);
//   agp = EEPROM.read(6);
//  bgp = EEPROM.read(7);
}
