String data;

unsigned long periodo_req = 599995; // 10 minuto = 600000
unsigned long time_req    = 0;

unsigned long periodo_ldr = 60000; // 1 minuto = 60000
unsigned long time_ldr    = 0;

unsigned long periodo_me = 2000; // 10 minuto = 600000
unsigned long time_me    = 0;

unsigned long periodo_pir = 2000; // 10 minuto = 600000
unsigned long time_pir    = 0;

void MonitoramentoEnergia(){
    if(millis() >  time_me + periodo_me){
    time_me = millis();
      corrente_1 = SCT013.calcIrms(1480);
      corrente_2 = SCT013.calcIrms(1480);
      corrente_3 = SCT013.calcIrms(1480);
    
      potencia_1 = corrente_1 * tensao_1;
      potencia_2 = corrente_2 * tensao_2;
      potencia_3 = corrente_3 * tensao_3;
    }
}

void MonitoramentoPIR(){
    if(millis() >  time_pir + periodo_pir){
    time_pir = millis();
      
    }
}

void MonitoramentoLDR(){
  if(millis() >  time_ldr + periodo_ldr){
    time_ldr = millis();
      if(estado >= 140){
      digitalWrite(pinoRELE,LOW);
      Serial.println("RELE LIGADO -> LUZ LIGADA");
    }else if(estado <= 135){
      digitalWrite(pinoRELE,HIGH);
      Serial.println("RELE DESLIGADO -> LUZ DESLIGADA");
    } 
  }
} 
 
void bancoEnviar(){
  if(millis() >  time_req + periodo_req){
    time_req = millis();
      String t1 = "temp1=";
      String h1 = "&hum1=";
      String c1 = "&cor1=";
      String p1 = "&pot1=";
      String c2 = "&cor2=";
      String p2 = "&pot2=";
      String c3 = "&cor3=";
      String p3 = "&pot3=";
      
      data = t1 + t + h1 + h + c1 + corrente_1 + p1 + potencia_1 + c2 + corrente_2 + p2 + potencia_2 + c3 + corrente_3 + p3 + potencia_3;
      
      Serial.print("Informação para o servidor -> ");
      Serial.println(data);
      Serial.println("Connectando");
      if(client.connect("iotree.recifetecnologia.com.br",80)){  // REPLACE WITH YOUR SERVER ADDRESS
      Serial.println("Conectou!");
      client.println("POST /add.php HTTP/1.1"); 
      client.println("Host: iotree.recifetecnologia.com.br"); // SERVER ADDRESS HERE TOO
      client.println("Content-Type: application/x-www-form-urlencoded"); 
      client.print("Content-Length: "); 
      client.println(data.length()); 
      client.println(); 
      client.print(data); 
      Serial.print(data);
      Serial.print("Foi enviado!");
    }else{
      Serial.println("Não conectou ao servidor!");
      }

    if (client.connected()) { 
      client.stop();
      Serial.println("Desconectou!");// DISCONNECT FROM THE SERVER
    }
  }
}
