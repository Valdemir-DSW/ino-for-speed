// Definindo as portas reais do Arduino
#define PORTA_1 13
#define PORTA_2 3
#define PORTA_3 4
#define PORTA_4 5
#define PORTA_5 6
#define PORTA_6 7
#define PORTA_7 8
#define PORTA_8 9

void setup_drivers() {
  // Inicializando as portas como saída
  pinMode(PORTA_1, OUTPUT);
  pinMode(PORTA_2, OUTPUT);
  pinMode(PORTA_3, OUTPUT);
  pinMode(PORTA_4, OUTPUT);
  pinMode(PORTA_5, OUTPUT);
  pinMode(PORTA_6, OUTPUT);
  pinMode(PORTA_7, OUTPUT);
  pinMode(PORTA_8, OUTPUT);
  
 
 
}



void habilitarDriver(int porta, unsigned long tempo) {
  unsigned long tempoInicial = millis();  // Tempo inicial
  int portaReal;

  // Mapeia o número da porta para a porta real
  switch (porta) {
    case 1:
      portaReal = PORTA_1;
      break;
    case 2:
      portaReal = PORTA_2;
      break;
    case 3:
      portaReal = PORTA_3;
      break;
    case 4:
      portaReal = PORTA_4;
      break;
    case 5:
      portaReal = PORTA_5;
      break;
    case 6:
      portaReal = PORTA_6;
      break;
    case 7:
      portaReal = PORTA_7;
      break;
    case 8:
      portaReal = PORTA_8;
      break;
    default:
      return;  // Caso a porta seja inválida
  }

  digitalWrite(portaReal, HIGH);  // Habilita a porta

  // A função vai rodar até que o tempo de habilitação tenha passado
  while (millis() - tempoInicial < tempo) {
    // O Arduino pode continuar fazendo outras tarefas aqui
  }

  digitalWrite(portaReal, LOW);  // Desabilita a porta após o tempo
}
