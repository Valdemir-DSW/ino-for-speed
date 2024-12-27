//mapas !
int matriz_ve1[20][20] = {
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
  {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
  {100, 100, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40},
  {100, 100, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
  {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
  {70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70},
  {80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80},
  {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
  {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
  {110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110},
  {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120},
  {130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130},
  {140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140},
  {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150},
  {160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160},
  {170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170},
  {180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180},
  {190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190},
  {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}

};



void save_matriz_ve1EEPROM(int startAddress) {
  int totalSize = 20 * 20 * sizeof(int16_t);
  if (startAddress + totalSize > EEPROM.length()) {
    Serial.println("Erro: Espaço insuficiente na EEPROM.");
    return;
  }

  int address = startAddress;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      EEPROM.put(address, matriz_ve1[i][j]);
      address += sizeof(int16_t);
    }
  }
}


void load_matriz_ve1FromEEPROM(int startAddress) {
  int totalSize = 20 * 20 * sizeof(int16_t);
  if (startAddress + totalSize > EEPROM.length()) {
    Serial.println("Erro: Espaço insuficiente na EEPROM.");
    return;
  }

  int address = startAddress;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      EEPROM.get(address, matriz_ve1[i][j]);
      address += sizeof(int16_t);
    }
  }
}
const float rpm_values_ve1[20] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};
const float map_values_ve1[20] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
//------------------------------------------------------------------



//------------------------------------------------------------------
float calc_ve_1(float rpm_input, float map_input) {
    if ( rpm_input >rpm_values_ve1[19] - 1){
      rpm_input = rpm_values_ve1[19] - 1;
    }else if ( rpm_input <rpm_values_ve1[0]){
      rpm_input = rpm_values_ve1[0];
    }
    if ( map_input >map_values_ve1[19] - 1){
      map_input = map_values_ve1[19] - 1;
    }else if ( map_input <map_values_ve1[0]){
      map_input = map_values_ve1[0];
    }
    
    float x = -1.0f; // Índice para RPM (pode ser decimal)
    float y = -1.0f; // Índice para MAP (pode ser decimal)

    // Determinar o índice X (RPM) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (rpm_input == rpm_values_ve1[i]) {
            y = i; // Índice exato
            break;
        } else if (rpm_input > rpm_values_ve1[i] && rpm_input < rpm_values_ve1[i + 1]) {
            // Interpolação para índices fracionários
            y = i + (rpm_input - rpm_values_ve1[i]) / (rpm_values_ve1[i + 1] - rpm_values_ve1[i]);
            break;
        }
    }

    // Determinar o índice Y (MAP) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (map_input == map_values_ve1[i]) {
            x = i; // Índice exato
            break;
        } else if (map_input > map_values_ve1[i] && map_input < map_values_ve1[i + 1]) {
            // Interpolação para índices fracionários
            x = i + (map_input - map_values_ve1[i]) / (map_values_ve1[i + 1] - map_values_ve1[i]);
            break;
        }
    }

    // Verificar se X ou Y estão fora do intervalo válido
    if (x < 0 || y < 0 || x >= 19 || y >= 19) {
        error = 4; 
        return 0; // Valor de erro para entradas inválidas
    }

    // Caso os índices sejam inteiros, pegar diretamente o valor da matriz
    if (x == (int)x && y == (int)y) {
        return matriz_ve1[(int)x][(int)y];
    }

    // Caso contrário, fazer interpolação bilinear nos valores da matriz
    int x_low = (int)x;         // Índice inferior para X
    int x_high = x_low + 1;     // Índice superior para X
    int y_low = (int)y;         // Índice inferior para Y
    int y_high = y_low + 1;     // Índice superior para Y

    // Valores da matriz adjacentes
    float ve_11 = matriz_ve1[x_low][y_low];
    float ve_12 = matriz_ve1[x_low][y_high];
    float ve_21 = matriz_ve1[x_high][y_low];
    float ve_22 = matriz_ve1[x_high][y_high];

    // Frações para ponderação
    float x_frac = x - x_low;
    float y_frac = y - y_low;

    // Interpolação bilinear
    float ve_interpolated =
        (1 - x_frac) * (1 - y_frac) * ve_11 +
        (x_frac) * (1 - y_frac) * ve_21 +
        (1 - x_frac) * (y_frac) * ve_12 +
        (x_frac) * (y_frac) * ve_22;

    return ve_interpolated;
}

//------------------------------------------------------------------



//------------------------------------------------------------------
int matriz_ve2[20][20] = {
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
{20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
{30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
{100, 100, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40},
{100, 100, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
{60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
{70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70},
{80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80},
{90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
{110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110},
{120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120},
{130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130},
{140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140},
{150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150},
{160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160},
{170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170},
{180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180},
{190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190},
{200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}
  
}; 

void save_matriz_ve2EEPROM(int startAddress) {
  int totalSize = 20 * 20 * sizeof(int16_t);
  if (startAddress + totalSize > EEPROM.length()) {
    Serial.println("Erro: Espaço insuficiente na EEPROM.");
    return;
  }

  int address = startAddress;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      EEPROM.put(address, matriz_ve2[i][j]);
      address += sizeof(int16_t);
    }
  }
}


void load_matriz_ve2FromEEPROM(int startAddress) {
  int totalSize = 20 * 20 * sizeof(int16_t);
  if (startAddress + totalSize > EEPROM.length()) {
    Serial.println("Erro: Espaço insuficiente na EEPROM.");
    return;
  }

  int address = startAddress;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      EEPROM.get(address, matriz_ve2[i][j]);
      address += sizeof(int16_t);
    }
  }
}
const float rpm_values_ve2[20] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};
const float map_values_ve2[20] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
float calc_ve_2(float rpm_input, float map_input) {
    if ( rpm_input >rpm_values_ve2[19] - 1){
      rpm_input = rpm_values_ve2[19] - 1;
    }else if ( rpm_input <rpm_values_ve2[0]){
      rpm_input = rpm_values_ve2[0];
    }
    if ( map_input >map_values_ve2[19] - 1){
      map_input = map_values_ve2[19] - 1;
    }else if ( map_input <map_values_ve2[0]){
      map_input = map_values_ve2[0];
    }
    
    float x = -1.0f; // Índice para RPM (pode ser decimal)
    float y = -1.0f; // Índice para MAP (pode ser decimal)

    // Determinar o índice X (RPM) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (rpm_input == rpm_values_ve2[i]) {
            y = i; // Índice exato
            break;
        } else if (rpm_input > rpm_values_ve2[i] && rpm_input < rpm_values_ve2[i + 1]) {
            // Interpolação para índices fracionários
            y = i + (rpm_input - rpm_values_ve2[i]) / (rpm_values_ve2[i + 1] - rpm_values_ve2[i]);
            break;
        }
    }

    // Determinar o índice Y (MAP) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (map_input == map_values_ve2[i]) {
            x = i; // Índice exato
            break;
        } else if (map_input > map_values_ve2[i] && map_input < map_values_ve2[i + 1]) {
            // Interpolação para índices fracionários
            x = i + (map_input - map_values_ve2[i]) / (map_values_ve2[i + 1] - map_values_ve2[i]);
            break;
        }
    }

    // Verificar se X ou Y estão fora do intervalo válido
    if (x < 0 || y < 0 || x >= 19 || y >= 19) {
        error = 4; 
        return 0; // Valor de erro para entradas inválidas
    }

    // Caso os índices sejam inteiros, pegar diretamente o valor da matriz
    if (x == (int)x && y == (int)y) {
        return matriz_ve2[(int)x][(int)y];
    }

    // Caso contrário, fazer interpolação bilinear nos valores da matriz
    int x_low = (int)x;         // Índice inferior para X
    int x_high = x_low + 1;     // Índice superior para X
    int y_low = (int)y;         // Índice inferior para Y
    int y_high = y_low + 1;     // Índice superior para Y

    // Valores da matriz adjacentes
    float ve_11 = matriz_ve2[x_low][y_low];
    float ve_12 = matriz_ve2[x_low][y_high];
    float ve_21 = matriz_ve2[x_high][y_low];
    float ve_22 = matriz_ve2[x_high][y_high];

    // Frações para ponderação
    float x_frac = x - x_low;
    float y_frac = y - y_low;

    // Interpolação bilinear
    float ve_interpolated =
        (1 - x_frac) * (1 - y_frac) * ve_11 +
        (x_frac) * (1 - y_frac) * ve_21 +
        (1 - x_frac) * (y_frac) * ve_12 +
        (x_frac) * (y_frac) * ve_22;

    return ve_interpolated;
}
//------------------------------------------
void ve_shitch_loop(){
  if (ve_shitch_ops == 1){
    
  }else if (ve_shitch_ops == 2){
    if (coolantTemp >= ve_shitch_arg){
      att_ve_shitch = 2;
    }else{
      att_ve_shitch = 1;
    }
  }else if (ve_shitch_ops == 3){
    
  }else{
    att_ve_shitch = 1;
  }

  
}

//...................

//Auxiliar de atualização de software
int aux_var = 0;
int valoresLidos[20];


void update_matriz_ve1(String dadosRecebidos){
              if (sscanf(dadosRecebidos.c_str(),
                       "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                       &valoresLidos[0], &valoresLidos[1], &valoresLidos[2], &valoresLidos[3],
                       &valoresLidos[4], &valoresLidos[5], &valoresLidos[6], &valoresLidos[7],
                       &valoresLidos[8], &valoresLidos[9], &valoresLidos[10], &valoresLidos[11],
                       &valoresLidos[12], &valoresLidos[13], &valoresLidos[14], &valoresLidos[15],
                       &valoresLidos[16], &valoresLidos[17], &valoresLidos[18], &valoresLidos[19]) == 20) {

              
              for (int i = 0; i < 20; i++) {
                matriz_ve1[aux_var][i] = valoresLidos[i];
              }

         
              aux_var += 1;
              if (aux_var == 20) {
                aux_var = 0;  
                saveToEEPROM();
              }
            }  
}
void update_matriz_ve2(String dadosRecebidos){
              if (sscanf(dadosRecebidos.c_str(),
                       "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                       &valoresLidos[0], &valoresLidos[1], &valoresLidos[2], &valoresLidos[3],
                       &valoresLidos[4], &valoresLidos[5], &valoresLidos[6], &valoresLidos[7],
                       &valoresLidos[8], &valoresLidos[9], &valoresLidos[10], &valoresLidos[11],
                       &valoresLidos[12], &valoresLidos[13], &valoresLidos[14], &valoresLidos[15],
                       &valoresLidos[16], &valoresLidos[17], &valoresLidos[18], &valoresLidos[19]) == 20) {

              
              for (int i = 0; i < 20; i++) {
                matriz_ve2[aux_var][i] = valoresLidos[i];
              }

         
              aux_var += 1;
              if (aux_var == 20) {
                aux_var = 0;  
                saveToEEPROM();
              }
            }  
}
