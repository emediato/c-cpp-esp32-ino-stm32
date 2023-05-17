
const int buttonPin = 2; // pin 2
const int ledPin = 13; // pin 13 - LED

//variables will change
int ledState = HIGH; // the current state of the output pin
int buttonState ; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
// unsigned long because the value will be long in a period of time
unsigned long debounceDelay = 50; // the debounce time ; increase if the output flickers
// 50 miliseconds


unsigned long blinkStartTime = 0;   // the time the LED started blinking
const unsigned long blinkDuration = 1000;  // the duration of the blink in milliseconds

unsigned long loopStartTime = 0;    // the time loop() started running
unsigned long loopCounter = 0;      // the number of times loop() has run


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
                blinkStartTime = millis();  // start the blink timer

            }
        }
    }

    //save the reading. next time through the loop, it will be the lastButtonState
    lastButtonState = reading;

        // blink the LED for 1 second after the button is pressed
    if ((millis() - blinkStartTime) < blinkDuration) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

}