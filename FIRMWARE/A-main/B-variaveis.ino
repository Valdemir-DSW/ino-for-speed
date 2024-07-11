//Variáveis do estado atual do motor com alta taxa de atualização e uso 
int mdegrees = 0;
const int numCylinders = 8;


//porteiras

#define APbattsen A0
#define APtps A1
#define APaguasen A3
#define APlambda A4

//lambda
int Lbanda = 0;
float mvwb = 1.0;
float mlwb = 1.47;
float mavwb = 4.0;
float malwb = 18.0;
// bobina

const int pulsePins[numCylinders] = {2, 3, 4, 5, 6, 7, 8, 13};
int triggerDegrees[numCylinders] = {45, 90, 135, 180, 225, 270, 315, 0};
unsigned long pulseDuration = 4;//dewell
// bicos
const int injectorPins[numCylinders] = {2, 3, 4, 5, 6, 7, 8, 9};
int triggerDegreesbb[numCylinders] = {45, 90, 135, 180, 225, 270, 315, 0};
unsigned long injectionTime = 5;
//serial var 22
String output;
//roda fonica
int conta1=0, conta2=0, ponto=0, avanco=1;
int f;
int battoffset = 15;
//Sensor de agua temperatura 
int  Atermres  = 100000; // Valor do termistor, no caso estamos utilizando um termistor de 100k
int  Atempnominal =  25 ;// Temperatura nominal do NTC utilizado
int  Abeta =  3950 ; // Valor do beta do termistor
int  Ares = 100000 ; // Valor do resistor utilizado em série com o termistor
//Sensores main
int tpsmin = 0;
int tpsmax = 1023;
float mapValue = 20;
float injectionTimevar = 40;
int tpsPosition = 0;
int coolantTemp = 10;
float lambdaAFR = 0.8;
float dutyCycle = 0;
float batteryVoltage = 0;
float error = 0;
