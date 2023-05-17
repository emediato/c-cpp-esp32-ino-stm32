//Atividade 1: Implemente um sistema que acende 3 leds (A,B,C) 
// na seguinte sequência com intervalo de 500 ms entre estados: 
//(0,0,1) -> (0,1,0) -> (1,1,0) -> (1,1,1) -> (0,1,0) -> (1,0,1) -> (0,0,1)-> ....

// Utilize a função delay para regular o tempo de transição.

// Atividade 2: Repita a Atividade 1 usando a função millis (ver o código auxiliar BlinkWithoutDelay)


// Atividade 3: Repita a Atividade 2 com um botão. Caso o botão seja pressionado, a sequência deve ser reiniciada.

// Atividade 4: Implemente um semáforo de veículos (3 leds) - e de pedestres (2 leds) com um botão:

// - A sequência usual deve ser, (i) Semáforo Pedestre: Vermelho e Semáforo Veículos: Verde-> Amarelo -> Vermelho seguido de Semáforo Pedestres:Verde. Repetir. O tempo de transição deve ser 1 s (depende da velocidade do simulador)

// - Caso o botão seja pressionado, o tempo de transição do semáforo de veículos deve ser reduzido pela metade. Quando o semáforo de pedestre retornar ao vermelho, o tempo de transição do semáforo de veículos deve retornar ao normal.

//  Obs: Em toda atividade com botão, implementar o debounce.


//  no boucing treatment


const int buttonPin_one = 2; // pin 2
const int buttonPin_two = 3; // pin 2
const int buttonPin_three = 4; // pin 2

const int ledPin_one = 13; // pin 13 - LED
const int ledPin_two = 12; // pin 12 - LED
const int ledPin_three = 8; // pin 8 - LED

const long interval = 5000;  // interval at which to blink (milliseconds)

//usually int is 16 its
void setup(){
    Serial.begin(9600);
    pinMode(buttonPin_one, INPUT); // BUTTON as INPUT
    pinMode(buttonPin_two, INPUT); // BUTTON as INPUT
    pinMode(buttonPin_three, INPUT); // BUTTON as INPUT


    pinMode(ledPin_one, OUTPUT); // LED as OUTPUT
    pinMode(ledPin_two, OUTPUT); // LED as OUTPUT
    pinMode(ledPin_three, OUTPUT); // LED as OUTPUT

}

void change_pin_state(int state1, int state2, int state3) {
    digitalWrite(ledPin_one, state1); // turn off
    digitalWrite(ledPin_two, state2); //  turn off
    digitalWrite(ledPin_three, state3); // turn on
}


void loop(){

    delay(interval); // delay para debounce  
    change_pin_state(LOW, LOW, HIGH); 

    delay(interval); // delay para debounce  
    change_pin_state(LOW, HIGH, LOW); 

    delay(interval); // delay para debounce  
    change_pin_state(HIGH, HIGH, LOW); 

    delay(interval); // delay para debounce  
    change_pin_state(HIGH, HIGH, HIGH); 

    delay(interval); // delay para debounce  
    change_pin_state(LOW, HIGH, LOW); 

    delay(interval); // delay para debounce  
    change_pin_state(HIGH, LOW, HIGH); 
    
    delay(interval); // delay para debounce  
    change_pin_state(HIGH, LOW, HIGH); 


    delay(interval); // delay para debounce  
    change_pin_state(LOW, LOW, HIGH); 
}
