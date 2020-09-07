#include "DHT.h"

DHT dht = DHT(7, DHT22);
int portaLDR = A5;   
int portaRELE = 8;
int estado = analogRead(portaLDR); 
float humidity; 
float temperature;
 
void setup(){    
  Serial.begin(9600);
  dht.begin();
  pinMode(portaRELE, OUTPUT); 
}  

void loop() {    
  estado = analogRead(portaLDR);  
  humidity = dht.readHumidity(); /* Get humidity value */
  temperature = dht.readTemperature(); /* Get temperature value */
Serial.println("------------------------");
Serial.print("VALOR LDR: ");
Serial.println(estado);
Serial.print("UMIDADE: ");
Serial.println(humidity);
Serial.print("TEMPERATURA: ");
Serial.println(temperature);

  
  if(estado > 500){
    digitalWrite(portaRELE,LOW);
    Serial.println("RELE LIGADO");
  }else{
    digitalWrite(portaRELE,HIGH);
    Serial.println("RELE DESLIGADO");
  }
delay(5000); 

}
