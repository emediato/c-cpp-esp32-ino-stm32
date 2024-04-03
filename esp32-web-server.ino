#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// esp as server!! funcionalidades para quem quiser acessa-lo
// browser acessa o ip ou nome do site
// quando voce acessa o site, se abre uma conexao com cliente e vc começa a fazer requisicoes para o servidor

// ao fazer servidor no esp, devemos ver as funçoes disponiveis para isso

const char* ssid = “sua_rede";

const char* password = “sua_senha";

WebServer server(80);

// server sends code, type of text, string to be sent
void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleNotFound() {
  server.send(404, "text/plain",  “Not Found”);

  digitalWrite(led, 0);
}


void setup(void) {
  Serial.begin(9600);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // DNS servidor de nome : atribuimos nomes ao IP
  // nome para disposito local
  // IP conectado ao Wifi
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  // server.on atribui funcionalidades ao dominio
  server.on("/", handleRoot);
  server.on("/inline", []() { // definiu esse dominio

  server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);
}
