// contador que conta o numero de vezes que um botao push-button mudou de estado.botao

//  when u press a button, turn on LED

//  no boucing treatment

// O microcontrolador tende a interpretar que o usuário pressionou rapidamente várias vezes a chave, quando na verdade foi apenas uma vez.

// DEFINE CONST

// Ao apertar e soltar o botão, esperamos que o contador incremente várias vezes (efeito bouncing).


const int buttonPin = 2; // pin 2
const int ledPin = 13; // pin 13 - LED


bool last; // last state of the button
unsigned long print_timer = 0; // timer in serial port UART0 - miliseconds
// unsigned long because the value will be long in a period of time


uint8_t counter = 0; // count how many change state in the button
//usually int is 16 its
void setup(){
    Serial.begin(9600);
    pinMode(buttonPin, INPUT); // BUTTON as INPUT
    pinMode(ledPin, OUTPUT); // LED as OUTPUT
    last = digitalRead(buttonPin);

    // we expect that the counter is incremented many times (boucing effect)]

}

void loop(){
    bool now = digitalRead(buttonPin); // read actual butotn state
    if (now!=last){
        ++counter;
        last=now;
        if (now==true){
            digitalWrite(ledPin,HIGH); // valor de tensao alto = 5v Liga lED
        } else {
            digitalWrite(ledPin, LOW); // valor de tensao baixo = 0 v desliga lED
        }
    }
    if (millis() - print_timer > 1000) {// display quantity change every sec
        Serial.println(counter);
        print_timer = millis();

    }

}