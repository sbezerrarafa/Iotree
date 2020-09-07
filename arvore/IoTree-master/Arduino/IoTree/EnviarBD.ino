String data;
unsigned long periodo_req = 299995; // 10 minuto = 600000
unsigned long time_req    = 0;

void bancoEnviar(){
  if(millis() >  time_req + periodo_req){
    time_req = millis();
      String a1 = "arvore=";
      String t1 = "&temp1=";
      String h1 = "&hum1=";
      String c1 = "&solara=";
      String p1 = "&solarw=";
      String c2 = "&usbpetalamenora=";
      String p2 = "&usbpetalamenorw=";
      String c3 = "&usbpetalameioa=";
      String p3 = "&usbpetalameiow=";
      String c4 = "&usbpetalamaiora=";
      String p4 = "&usbpetalamaiorw=";
     // String c5 = "&XXXa=";
     // String p5 = "&XXXw=";
     
      data = a1 + a + t1 + t + h1 + h + c1 + corrente_1 + p1 + potencia_1 + c2 + corrente_2 + p2 + potencia_2 + c3 + corrente_3 + p3 + potencia_3 + c4 + corrente_4 + p4 + potencia_4;
      
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
