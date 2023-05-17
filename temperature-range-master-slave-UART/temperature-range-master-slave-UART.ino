/*

Atenção: Para a implementação dessa Atividade, verifique a
tensão de operação das duas placas envolvidas na comunicação,
pois existe o risco de danificar uma das placas. Em caso de
dúvidas, consulte o professor.

Passo 1: Assista ao vídeo do exemplo da Aula 6 e o implemente.

Passo 2: Escolha uma placas para ser o “Dispositivo Master”
(conexão com um botão, um LED vermelho e um LED verde) e a
outra, o “Dispositivo Slave” (conexão com um sensor de
temperatura LM 35).

Atividade A2

✔O “Dispositivo Master” deve
✔Solicitar a temperatura ao “Dispositivo Slave” quando o
botão for pressionado e receber o valor correspondente. Se
a temperatura estiver acima de 25oC, o LED Interno da
placa do “Dispositivo Master” deve ser aceso. Caso
contrário, deve se manter apagado.
*/ 

// **************************************************************
// arduino 1
#define BOUNCE_TIME 200
const int ledPin_one_red = 12;    // pin 13 - LED
const int ledPin_two_yellow = 8; // pin 12 - LED
const int ledPin_three_green = 13; // pin 8 - LED
const int buttonPin_one = 2;   // pin 2

long lastMillis = 0;   // the time the LED started blinking
unsigned long debounceDelay = 500;   // the last time the output pin was toggled


void setup() {
  // put your setup code here, to run once:
    // Serial communication
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

    // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
    if ((millis() - lastMillis) > debounceDelay) {
      Serial.print('a');
      lastMillis = millis();

    }
}
// **************************************************************
// arduino 2
/*
✔O “Dispositivo Slave” deve enviar ao “Dispositivo Master”
duas indicações:
✔Caso a temperatura esteja entre 30oC e 35oC, o LED verde
do “Dispositivo Master” deve piscar com frequência de 1 Hz
✔Caso a temperatura seja maior do que 35oC, o LED verde
deve ser manter aceso, e o LED vermelho deve piscar.
*/ 
const unsigned long blinkDuration = 1000; // the duration of the blink in milliseconds
const int buttonPin = 2;   // pin 2


bool pinState = LOW;

bool green_on = false;
bool red_on  = false;
char command = 0;

static uint32_t lastPressTime1 = 0;

void setup() {
  // put your setup code here, to run once:
    // Serial communication
    pinMode(ledPin, OUTPUT); // LED as OUTPUT
    Serial.begin(9600);
}

void blink_leds() {
    unsigned long time = millis();

    if (green_on) {
        digitalWrite(ledPin_three_green, (time / blinkDuration) % 2);
    } else {
        digitalWrite(ledPin_three_green, LOW);
    }

    if (red_on) {
        digitalWrite(ledPin_one_red, (time / blinkDuration) % 2);
    } else {
        digitalWrite(ledPin_one_red, LOW);
    }
}


void loop() {
    blink_leds();
    if (digitalRead(buttonPin_one) && (millis() - lastPressTime1 > BOUNCE_TIME)) {
       lastPressTime1 = millis();
    // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
      if ((Serial.available() - lastMillis) > 0) {
        // serial available verifica se buffer tem algo a ser lido
        command = Serial.read();
        if (int(command) >= 30) || (int(command) <= 35) {
          green_on = true;
          red_on = false;
          pinState = !pinState; // inverter estad
          digitalWrite(ledPin, pinState);
        }
      }
    }
}