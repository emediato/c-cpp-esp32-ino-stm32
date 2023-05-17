
const int buttonPin = 2; // pin 2
const int ledPin = 13; // pin 13 - LED

//variables will change
int ledState = HIGH; // the current state of the output pin
int buttonState ; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
// unsigned long because the value will be long in a period of time
unsigned long debounceDelay = 5; // the debounce time ; increase if the output flickers
// 50 miliseconds

void setup(){

    pinMode(buttonPin, INPUT); // BUTTON as INPUT
    pinMode(ledPin, OUTPUT); // LED as OUTPUT
    //set initial LED state
    digitalWrite(ledPin, ledState);
    // we expect that the counter is incremented many times (boucing effect)]
}

void loop(){
    // read the state of the switch into a local variable

    int reading = digitalRead(buttonPin);

    if (reading != lastButtonState){
        // reset the bouncing timer
        lastDebounceTime = millis();
    }

    // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
    if ((millis() - lastDebounceTime) > debounceDelay) {

        // if the button state has changed
        if (reading != buttonState) {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH){
                ledState = !ledState;
            }
        }
    }

    digitalWrite(ledPin, ledState); // set the LED

    //save the reading. next time through the loop, it will be the lastButtonState
    lastButtonState = reading;
}