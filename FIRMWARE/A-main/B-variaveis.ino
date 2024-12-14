//porteiras

#define APbattsen A0
#define APtps A1
#define APaguasen A3
#define APlambda A4
#define APmap A5
// tipologia_motor
//map
int map_zeroV = 0;
int map_cincoV = 341;
//lambda
int Lbanda = 0;
float mvwb = 1.0;
float mlwb = 1.47;
float mavwb = 4.0;
float malwb = 18.0;
//serial var 22
String output;

//bicos
int cen_per_ms = 14;
int fine_pos   =  0;
//bobina_vela
int dwell_time = 44;
int porcent_dwell_volt[6] = {10, 50, 30, 0, -20, -44}; // Lista de porcent_dwell_volt inicializadas em zero
int avanco_padrao = 0;
//roda fonica
int angulo_ps_falha = 0;
int teethCount = 60;       // Número total de dentes na roda fônica
int missingToothGap = 2;   // Número de dentes ausentes
//float syncTolerance = 0.2; // Tolerância para detectar dentes consistentes
int att_rpm = 0;
int motor_pos = 0;
bool invertRPM = false; // Inverter o cálculo do RPM se necessário
#define sensorPin_fonica  2 // Pino digital 2



// sensor de batt
int battoffset = 30;
//Sensor de agua temperatura 
unsigned long  Atermres  = 100000; // Valor do termistor, no caso estamos utilizando um termistor de 100k
int  Atempnominal =  25 ;// Temperatura nominal do NTC utilizado
int  Abeta =  3950 ; // Valor do beta do termistor
unsigned long  Ares = 100000 ; // Valor do resistor utilizado em série com o termistor
//Sensores main
int tpsmin = 0;
int tpsmax = 1023;
float mapValue = 127;
float injectionTime = 0;
int tpsPosition = 0;
int coolantTemp = 10;
float lambdaAFR = 0.8;
float dutyCycle = 0;
float batteryVoltage = 0;
float error = 0;