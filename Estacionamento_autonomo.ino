
#include <Servo.h>

Servo entrada,saida;

//vetor com os leds
const int iQuantLed = 8;
const int ledVet[iQuantLed] = {15, 16, 17, 18, 2, 3, 4, 5};

//vetor com os pinos dos leds
const int iQuantSensor = 6;
const int sensorPinVet[iQuantSensor] = {0, 1, 2, 3, 4, 5};

//vetor com os valores do sensores
int sensorVet[iQuantSensor] = {0, 0, 0, 0, 0, 0};

//Quantidade de vagas
const int tlVagas = 4;
int contVagas = 0;

int pos = 0;

const long espAbertCancEntr = 2000;
unsigned long ultAbertCancEntr = 0;

const long espAbertCancSaida = 3500;
unsigned long ultAbertCancSaida = 0;

//Desliga todos os leds, apos 1s liga todos os leds por 1 s e depois apaga todos os leds vermelhos
void testaLed () {
  //Serial.println("-----------Inicio teste dos leds-----------");
  for (int i = 0; i < iQuantLed; i++) {
    digitalWrite(ledVet[i], LOW);
  }
  delay(1000);
  
  for (int i = 0; i < iQuantLed; i++) {
    digitalWrite(ledVet[i], HIGH);
    delay(200);
  }
  delay(1000);
  for (int i = 1; i < iQuantLed; i = i+2) {
    digitalWrite(ledVet[i], LOW);
  }

  //Serial.println("-----------Fim teste dos leds-----------");
}

//le todos os sensores
void readSensor(int sensor[]) {
  
  for (int i = 0; i < iQuantSensor; i++) {
    sensor[i] = analogRead(sensorPinVet[i]);
    //Serial.print("Sensor ");
    //Serial.print(i);
    //Serial.print(" : ");
    //Serial.println(sensor[i]);
    //delay(200);
  }
  //Serial.println("-----------------------"); 
}

void setup() {
  Serial.begin(9600);
  //declaração
  for (int i = 0; i < iQuantLed; i++) {
    pinMode(ledVet[i], OUTPUT);
  }

  entrada.attach(9);
  entrada.write(90);
  
  saida.attach(10);
  entrada.write(90);
 
  testaLed();

}

void loop() {
  readSensor(sensorVet);
  unsigned long currentMillis = millis();
  for (int i = 0; i < iQuantSensor; i++) {
    if(i==0){ 
      if(currentMillis - ultAbertCancEntr >= espAbertCancEntr){
        if(sensorVet[i] < 490){  
          //Serial.println("abrir porta");
          if(contVagas <  tlVagas){
            entrada.write(10);
            contVagas += 1;
            Serial.println("Seja Bem Vindo");
          }else{
            Serial.println("Não temos Vagas");
          }
        }else{
          if(entrada.read() != 90){
            entrada.write(90);
          }
        }
        ultAbertCancEntr = currentMillis;
      }
    }else if (i==1) {
      if(currentMillis - ultAbertCancSaida >= espAbertCancSaida){
        if(sensorVet[i] < 490){  
          //Serial.println("na porta");
          saida.write(170);
          contVagas -= 1;
          Serial.println("Obrigado Volte Sempre");
        }else{
          if(saida.read() != 90){
            saida.write(90);
          }
        }
        ultAbertCancSaida = currentMillis;
     }
    }else if (i>=2) {
        if(sensorVet[i] > 800){
          digitalWrite(ledVet[2*(i-2)], LOW);
          digitalWrite(ledVet[2*(i-2)+1], HIGH);
        } else {
          digitalWrite(ledVet[2*(i-2)], HIGH);
          digitalWrite(ledVet[2*(i-2)+1], LOW);
        }
    }
 }
 delay(1000);
}
