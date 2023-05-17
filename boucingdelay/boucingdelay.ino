// cont that counts how many times the button push-button changed state
// this change appears in the serial monitor every time the button change

//boucing treatment is done via software by "delay"



const int buttonPin = 2; // pin 2
const int ledPin = 13; // pin 13 - LED


int buttonState = 0 ; // var to read the  button state
int counter = 0;
int flag = 0;


void setup(){
    pinMode(buttonPin, INPUT); // BUTTON as INPUT
    pinMode(ledPin, OUTPUT); // LED as OUTPUT
    Serial.begin(9600);
}

void loop(){
    delay(100); // delay to debounce

    buttonState = digitalRead(buttonPin); // read the state of the button

    if ((buttonState = HIGH) && (flag==0)){ // verify if the button is pressed
    // flag needs to be 0 because the button is down
        digitalWrite(ledPin, HIGH); // LED on
        counter = counter +1 ;
        Serial.println(counter);
        flag = 1  ;

    }

    if ((buttonState == LOW ) && (flag==1){
        digitalWrite(ledPin, LOW); // LED off
        counter = counter +1 ;
        Serial.println(counter);
        flag = 0 ;
    }

}