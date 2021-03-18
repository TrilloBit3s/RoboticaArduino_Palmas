//Programa para ligar 4 leds usando um sensor de PALMAS
//estuartyy@gmail.com
//Arduino NANO utilizado para o projeto
//05-08-2018

#define PortaSensor 2 //pino do sensor de som

#define ledVerde 4   
#define ledBranco 6
#define ledVermelho 8
#define ledAmarelo 10

#define tempoSOM  150 //milisegundos
#define tempoEntreSOM 500 //milisegundos

int contSOM = 0; 
long tempEspera = 0;
long tempEsperaEntreSOM = 0;

void executarAcaoSOM();

void setup() {
  pinMode(PortaSensor, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledBranco, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
}

void loop() {

  //verifica o estado do sensor de som (ele fica normalmente com a porta ligada. 
  int sensorSom = digitalRead(PortaSensor);
  
//se o sensor detectou palmas
  if (sensorSom == LOW) {
     //espera um tempo para nao detectar a mesma palma 
     if (tempEspera == 0) {
        tempEspera = tempEsperaEntreSOM = millis(); 
        contSOM++;
     } else if ((millis() - tempEspera) >= tempoSOM) {
        tempEspera = 0;
     }
  }

  //caso exceda o tempo maximo entre palmas, zera o contador de palmas
  if ( (contSOM != 0) && ((millis() - tempEsperaEntreSOM) > 500) ) {
     executarAcaoSOM();
     contSOM = 0;
     tempEsperaEntreSOM = millis();
  }
}

void executarAcaoSOM() {
  switch (contSOM) {
    case 2: 
       digitalWrite(ledVerde, !digitalRead(ledVerde)); break;
    case 3:
       digitalWrite(ledBranco, !digitalRead(ledBranco)); break;
    case 4:
       digitalWrite(ledVermelho, !digitalRead(ledVermelho));break;
    case 5:
       digitalWrite(ledAmarelo, !digitalRead(ledAmarelo));break;
  }
}
