const int BUTTON_PIN = 2;  // the pin number for the button
const int LED_PIN = 13;    // the pin number for the LED

int buttonState = LOW;     // variable for storing the button state
int lastButtonState = LOW; // variable for storing the previous button state
unsigned long lastDebounceTime = 0;  // the last time the button was debounced
unsigned long debounceDelay = 50;    // the debounce time in milliseconds

unsigned long blinkStartTime = 0;   // the time the LED started blinking
const unsigned long blinkDuration = 1000;  // the duration of the blink in milliseconds

unsigned long loopStartTime = 0;    // the time loop() started running
unsigned long loopCounter = 0;      // the number of times loop() has run

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // set the button pin as input with internal pullup resistor
  pinMode(LED_PIN, OUTPUT);           // set the LED pin as output
  Serial.begin(9600);                 // initialize the serial communication for debugging
}

void loop() {
  loopStartTime = millis();  // record the start time of loop()

  // debounce the button
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {  // button is pressed
        blinkStartTime = millis();  // start the blink timer
      }
    }
  }
  lastButtonState = reading;

  // blink the LED for 1 second after the button is pressed
  if ((millis() - blinkStartTime) < blinkDuration) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // count the times loop() has run
  loopCounter++;

  // print the loop time and counter for debugging
  Serial.print("Loop time: ");
  Serial.print(millis() - loopStartTime);
  Serial.print(", Loop counter: ");
  Serial.println(loopCounter);
}

/*
The loop() function runs continuously, 
and it first records the start time of the loop using millis(). 
It then debounces the button using a simple algorithm that compares
 the current reading with the previous reading and the last debounce time. 
 If the button is pressed, it starts the blink timer using millis().
 
  The LED is turned on for the duration of the blink using digitalWrite(). 
  The number of times the loop() function has run is counted using the 
  loopCounter variable, which is printed to the serial monitor for debugging 
  purposes along with the loop time.
*/
