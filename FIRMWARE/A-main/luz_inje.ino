    
    #define ledPin_injeao  13 // Pino do LED
 
    
    void setup_luz_injeao() {
    pinMode(ledPin_injeao, OUTPUT); // Define o pino do LED como saída
    digitalWrite(ledPin_injeao, LOW); // Inicializa o LED desligado
    }
    void verificar_inje_led(){
      if (error != 0){
      turnOnLED_inje();
      }else if (error == 0){
      turnOffLED_inje();
      }
    }

    

    void turnOnLED_inje() {
   
      digitalWrite(ledPin_injeao, HIGH);
    }

    void turnOffLED_inje() {
     
      digitalWrite(ledPin_injeao, LOW);
    }
