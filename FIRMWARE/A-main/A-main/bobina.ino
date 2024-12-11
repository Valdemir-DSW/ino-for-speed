
int voltagens[6] = {6, 8, 10, 12, 16, 18}; // Lista de voltagens fixas


int dwell_time_calc(int valor) {
  // Variáveis para armazenar as porcentagens e índices
  int indexInferior = -1;
  int indexSuperior = -1;
  float porcentagemInferior = 0;
  float porcentagemSuperior = 0;

  // Número de elementos na lista de voltagens
  const int numVoltagens = 6; // Ajuste conforme necessário
  const float maxVoltage = voltagens[numVoltagens - 1]; // Último valor de voltagens
  
  // Verificação se a tensão da bateria é maior ou menor que os limites
  if (batteryVoltage >= maxVoltage) {
    porcentagemInferior = porcent_dwell_volt[numVoltagens - 1];
    valor += valor * (porcentagemInferior / 100.0);
    return valor; // Retorna o valor ajustado
  } else if (batteryVoltage < voltagens[0]) {
    porcentagemInferior = porcent_dwell_volt[0];
    valor += valor * (porcentagemInferior / 100.0);
    return valor; // Retorna o valor ajustado
  }

  // Procurando os índices que englobam a tensão da bateria
  for (int i = 0; i < numVoltagens - 1; i++) {
    if (batteryVoltage >= voltagens[i] && batteryVoltage < voltagens[i + 1]) {
      indexInferior = i;
      indexSuperior = i + 1;
      porcentagemInferior = porcent_dwell_volt[i];
      porcentagemSuperior = porcent_dwell_volt[i + 1];
      break;
    }
  }

  // Caso a tensão esteja exatamente em um dos valores da lista
  if (batteryVoltage == voltagens[indexInferior]) {
    valor += valor * (porcentagemInferior / 100.0);
    return valor; // Retorna o valor ajustado
  }

  // Calculo de ajuste proporcional entre dois valores de voltagem
  if (indexInferior != -1 && indexSuperior != -1) {
    float proporcao = (batteryVoltage - voltagens[indexInferior]) / 
                      (voltagens[indexSuperior] - voltagens[indexInferior]);
    float porcentagemAjustada = porcentagemInferior + proporcao * (porcentagemSuperior - porcentagemInferior);
    valor += valor * (porcentagemAjustada / 100.0);
  }

  // Retorna o valor ajustado
  return valor;
}




const float map_values_Avanco_ponto[20][20] = {
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
{20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
{30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
{40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40},
{50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
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

/* float map_values_Avanco_ponto[20][20] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/
const float rpm_Avanco_ponto[20] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};
const float map_Avanco_ponto[20] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
//------------------------------------------------------------------



//------------------------------------------------------------------
float Avanco_ponto(float rpm_input, float map_input) {
    if ( rpm_input >rpm_Avanco_ponto[19] - 1){
      rpm_input = rpm_Avanco_ponto[19] - 1;
    }else if ( rpm_input <rpm_Avanco_ponto[0]){
      rpm_input = rpm_Avanco_ponto[0];
    }
    if ( map_input >map_Avanco_ponto[19] - 1){
      map_input = map_Avanco_ponto[19] - 1;
    }else if ( map_input <map_Avanco_ponto[0]){
      map_input = map_Avanco_ponto[0];
    }
    
    float x = -1.0f; // Índice para RPM (pode ser decimal)
    float y = -1.0f; // Índice para MAP (pode ser decimal)

    // Determinar o índice X (RPM) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (rpm_input == rpm_Avanco_ponto[i]) {
            y = i; // Índice exato
            break;
        } else if (rpm_input > rpm_Avanco_ponto[i] && rpm_input < rpm_Avanco_ponto[i + 1]) {
            // Interpolação para índices fracionários
            y = i + (rpm_input - rpm_Avanco_ponto[i]) / (rpm_Avanco_ponto[i + 1] - rpm_Avanco_ponto[i]);
            break;
        }
    }

    // Determinar o índice Y (MAP) considerando interpolação
    for (int i = 0; i < 19; i++) {
        if (map_input == map_Avanco_ponto[i]) {
            x = i; // Índice exato
            break;
        } else if (map_input > map_Avanco_ponto[i] && map_input < map_Avanco_ponto[i + 1]) {
            // Interpolação para índices fracionários
            x = i + (map_input - map_Avanco_ponto[i]) / (map_Avanco_ponto[i + 1] - map_Avanco_ponto[i]);
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
        return map_values_Avanco_ponto[(int)x][(int)y];
    }

    // Caso contrário, fazer interpolação bilinear nos valores da matriz
    int x_low = (int)x;         // Índice inferior para X
    int x_high = x_low + 1;     // Índice superior para X
    int y_low = (int)y;         // Índice inferior para Y
    int y_high = y_low + 1;     // Índice superior para Y

    // Valores da matriz adjacentes
    float ve_11 = map_values_Avanco_ponto[x_low][y_low];
    float ve_12 = map_values_Avanco_ponto[x_low][y_high];
    float ve_21 = map_values_Avanco_ponto[x_high][y_low];
    float ve_22 = map_values_Avanco_ponto[x_high][y_high];

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

int  calcular_avanco(){
     
  return Avanco_ponto(att_rpm,mapValue) + avanco_padrao;
}
