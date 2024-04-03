#include <WiFi.h>

int status = WL_IDLE_STATUS;
char server[] = "www.google.com";

WiFiClient client; // objeto que serve para se conectar a uma rede ou site ...... usando o servidor google

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Wokwi-GUEST", "", 6); // 6 - padrçao no wokwi; canal é mais rapido
  //SSID LOCAL NETWORK // PASSWORD // CHANNEL
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected to Wifi");
  // wifi diferente da internet 
  // padrao 3.011 - associacao que mantem  - rede de conexão sem fio que segue padrão 

  // wifi é como se fosse cabo por RF radio frequencia
  // internet vem depois 
  //se o ponto de acesso tiver o ethernet/fibra com a internet, assim teremos aplicações com a internet
  Serial.println("\n starting connection to server....");

  if (client.connect(server, 80)){ // porta HTTP = 80 / MQTT = 1883
    Serial.println("Connected to server");
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
 
}

void loop() {
  // put your main code here, to run repeatedly:
  while (client.available()) { // porta HTTP = 80 / MQTT = 1883
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()){
    Serial.println();
    Serial.println("disconnecting from server");
    client.stop();

    while(true);

  }

// 2 Giga H z -> questão de frequência com a água, quando chove, humidade, etc

}
