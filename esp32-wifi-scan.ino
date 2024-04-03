#include "WiFi.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");


// 2 Giga H z -> questão de frequência com a água, quando chove, humidade, etc

  if (n==0){
    Serial.println("no networks found");
  }
  else {
    Serial.print(n);
    Serial.println("networks found");
    for (int i = 0; i < n; i++){
      Serial.print(i+1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" ( ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" ) ");

      delay(10);

    }

  } Serial.println("");
  delay(5000);
}

// minuto 8:30
