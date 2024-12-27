int tps_map_var[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void up_tps_map(String dados) {
  // Divide os dados recebidos e armazena nos valores
  int idx = 0;
  int lastIndex = 0;

  for (int i = 0; i < 7; i++) {
    idx = dados.indexOf(',', lastIndex);  // Encontra a próxima vírgula
    if (idx == -1) {
      idx = dados.length();  // Caso seja o último valor
    }
    String valor_str = dados.substring(lastIndex, idx);
    tps_map_var[i] = valor_str.toInt();  // Converte o valor para inteiro
    lastIndex = idx + 1;  // Avança para o próximo índice
  }
  saveToEEPROM();
}



float calc_ve_tps(int tps) {
  // Garantir que tps esteja no intervalo de 0 a 100
  if (tps < 0) tps = 0;
  if (tps > 100) tps = 100;

  // Calcular o índice no array
  int indice = tps / 5;
  int proximoIndice = indice + 1;

  // Verificar se está no último intervalo
  if (proximoIndice >= 20) {
    return tps_map_var[indice];
  }

  // Obter os valores do array correspondentes
  int valorAtual = tps_map_var[indice];
  int valorProximo = tps_map_var[proximoIndice];

  // Interpolação linear para maior precisão
  float proporcao = (tps % 5) / 5.0;
  return valorAtual + proporcao * (valorProximo - valorAtual);
}

//////////////////////////////////////////////////////////

int ve2d_map_var[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void up_2d_map(String dados) {
  // Divide os dados recebidos e armazena nos valores
  int idx = 0;
  int lastIndex = 0;

  for (int i = 0; i < 7; i++) {
    idx = dados.indexOf(',', lastIndex);  // Encontra a próxima vírgula
    if (idx == -1) {
      idx = dados.length();  // Caso seja o último valor
    }
    String valor_str = dados.substring(lastIndex, idx);
    ve2d_map_var[i] = valor_str.toInt();  // Converte o valor para inteiro
    lastIndex = idx + 1;  // Avança para o próximo índice
  }

}



float calc_ve_2d(int maps) {
  // Garantir que maps esteja no intervalo de 0 a 100
  if (maps < 0) maps = 0;
  if (maps > 100) maps = 100;

  // Calcular o índice no array
  int indice = maps / 5;
  int proximoIndice = indice + 1;

  // Verificar se está no último intervalo
  if (proximoIndice >= 20) {
    return ve2d_map_var[indice];
  }

  // Obter os valores do array correspondentes
  int valorAtual = ve2d_map_var[indice];
  int valorProximo = ve2d_map_var[proximoIndice];

  // Interpolação linear para maior precisão
  float proporcao = (maps % 5) / 5.0;
  return valorAtual + proporcao * (valorProximo - valorAtual);
}
