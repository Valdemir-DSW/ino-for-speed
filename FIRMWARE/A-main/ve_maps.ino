 // Matriz de valores RPM e MAP ve
 float matriz_ve1[20][20] = {
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
void update_matriz_ve1(int currentRow,int colIndex,float token){
  //matriz_ve1[currentRow][colIndex] =token;
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
