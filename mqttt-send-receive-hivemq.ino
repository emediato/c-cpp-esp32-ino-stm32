
#include <WiFi.h>
#include <PubSubClient.h>


const char *WIFI_SSID = "Wokwi-GUEST";
const char *MQTT_SERVER = "broker.hivemq.com";
bool flag_led = false;
const uint16_t MQTT_PORT = 1883;

WiFiClient wifiClient;
// OBJECT PUBSUBCLIENT must be created
PubSubClient mqttClient(wifiClient);

//topico = ponteiro para string
//payload ponteiro para byte - vetor de bytes
//length
void CallbackMqtt(char* topic, byte* payload, unsigned int length){
  Serial.print("Received Message");

  if (String(topic) == "/cmd/usrs/ICT-UNIFESP/Hello-ESP-World") {
      Serial.println("Message received:");
      Serial.print("Topic: ");
      Serial.println(topic);
      Serial.print("Payload: ");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
  }

  
    if (String(topic) == "/cmd/usrs/ICT-UNIFESP/Change-Led") {
      if (payload[0] == 1){
        flag_led = true;
      }
  }
}

void SetupMqtt(){
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(CallbackMqtt);
}

void ConnectToWiFi(){
  Serial.print("Connecting to WiFi ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, "", 6);

  while (WiFi.status() != WL_CONNECTED)  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nConnected to ");
  Serial.println(WIFI_SSID);
}

void ConnectToMqtt(){

  
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
    char clientId[100] = "\0";
    // it generates a unique client ID for the MQTT client on the ESP32 device.
    //sprintf is a function used to format a string.
    // This random number is used to create a unique client ID each time the ESP32 device 
    //connects to the MQTT broker.
    sprintf(clientId, "ESP32Client-%04X", random(0xffff));

    Serial.println(clientId);

    if (mqttClient.connect(clientId)){
      Serial.println("Connected to MQTT broker.");
      mqttClient.subscribe("/cmd/usrs/ICT-UNIFESP/IoT");
      Serial.println("Connected to MQTT broker /IoT .");
      mqttClient.subscribe("/cmd/usrs/ICT-UNIFESP/Hello-ESP-World");
      Serial.println("Connected to MQTT broker /Hello-ESP-World .");

    }
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println("Setup begin");

  ConnectToWiFi();
  SetupMqtt();

  Serial.println("Setup end");
}

void loop(){
  if (!mqttClient.connected()){
    ConnectToMqtt();
  }
  mqttClient.loop();

  static uint64_t last_time;
  uint64_t now = millis();
/* PUBLICANDO MENSAGEM */
  if (now - last_time > 500){
      // Send "Hello, World!" message to MQTT topic
    mqttClient.publish("/srs/usrs/ICT-UNIFESP/IoT", "Hello world"); // THIS IS THE TOPIC
    last_time = now;
  }
}
