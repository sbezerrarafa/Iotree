#define BLYNK_PRINT Serial
#include "DHT.h"
#include <Ethernet.h>
#include <SPI.h>
#include <BlynkSimpleEthernet.h>
#define W5100_CS  10
#define SDCARD_CS 4
#include "EmonLib.h"


byte mac[] = {  0x90, 0xA2, 0xDA, 0x00, 0x73, 0xE4 }; //ethernet mac
EthernetClient client;
DHT dht = DHT(7, DHT22);
BlynkTimer timer;
EnergyMonitor SCT013;

int pinoLDR = A15;   
int pinoPIR = A14;
int pinoRELE = 8;
int estado = analogRead(pinoLDR); 
int pir = 0;
float h; 
float t;
char auth[] = "Bv_Rvrl0cYOihAEe3-piEPydia-l-IzJ";
bool bypass;
bool x;

int pinSCT_1 = A8; //
int pinSCT_2 = A9; //placaint
int pinSCT_3 = A10; //circuito
 
int tensao_1 = 12;
double potencia_1;
int tensao_2 = 12;
double potencia_2;
int tensao_3 = 12;
double potencia_3;

double potencia__total;

double corrente_1;
double corrente_2;
double corrente_3;

void sendSensor(){
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, estado);
  Blynk.virtualWrite(V8, corrente_1); //usb
  Blynk.virtualWrite(V9, potencia_1); //usb
  Blynk.virtualWrite(V10, corrente_2); //placa
  Blynk.virtualWrite(V11, potencia_2); //placa
  Blynk.virtualWrite(V12, corrente_3); //circuito
  Blynk.virtualWrite(V13, potencia_3); //circuito
}
BLYNK_WRITE(V1){
 int pinValue = param.asInt();
  if(pinValue == 0){
    bypass = true;
    digitalWrite(pinoRELE,HIGH);
    Serial.println("BYPASS - RELE DESLIGADO");
  }else if(pinValue == 1){
    bypass = false;
    Serial.println("bypass falso");
  }else{
    bypass = true;
    digitalWrite(pinoRELE,LOW);
    Serial.println("BYPASS - RELE LIGADO");
    }
  Serial.println(pinValue);
}

void reconnectBlynk(){
  if(!Blynk.connect()){
    Serial.println("blynk não conectou!");
     x == false;
    }if(Blynk.connect()){
      Serial.println("blynk conectou!");
      x == true;
      }else{
        Serial.println("blynk não reconectou!");
        x == false;
        }
  }
 
void setup(){
  SCT013.current(pinSCT_1, 6.0606);
  SCT013.current(pinSCT_2, 6.0606);
  SCT013.current(pinSCT_3, 6.0606);    
  x = false;
  Serial.begin(9600);
  Serial.println("SETUP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);
  Serial.println(Ethernet.localIP());
  Blynk.config(auth);
  Blynk.connect();
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(180000L, reconnectBlynk);
  dht.begin();
  pinMode(pinoRELE, OUTPUT); 
  bypass = false;
}  

void loop() {   
  debug(1);
  if(x == true){
   Blynk.run();
  }else{
}
  MonitoramentoEnergia();
  timer.run();
  estado = analogRead(pinoLDR);  
  h = dht.readHumidity(); 
  t = dht.readTemperature(); 
  pir = digitalRead(pinoPIR);
  bancoEnviar();
  if(bypass == false){
    MonitoramentoLDR();
    } 
}
