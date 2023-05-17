// contador que conta o numero de vezes que um botao push-button mudou de estado.botao

//  when u press a button, turn on LED

//  no boucing treatment

// O microcontrolador tende a interpretar que o usuário pressionou rapidamente várias vezes a chave, quando na verdade foi apenas uma vez.

// DEFINE CONST

// Ao apertar e soltar o botão, esperamos que o contador incremente várias vezes (efeito bouncing).
const int buttonPin_one = 2; // pin 2
const int buttonPin_two = 3; // pin 3
const int buttonPin_three = 4; // pin 4

const int ledPin_one_red = 13; // pin 13 - LED
const int ledPin_two_yellow = 12; // pin 12 - LED
const int ledPin_three_green = 8; // pin 8 - LED

unsigned long print_timer = 0; // timer in serial port UART0 - miliseconds
unsigned long previousMillis = 0;

unsigned long lastDebounceTime_one = 0; // the last time the output pin was toggled
unsigned long lastDebounceTime_two = 0; // the last time the output pin was toggled
unsigned long lastDebounceTime_three = 0; // the last time the output pin was toggled

// unsigned long because the value will be long in a period of time
unsigned long debounceDelay = 50; // the debounce time ; increase if the output flickers
// 50 miliseconds
const unsigned long blinkDuration = 1000;  // the duration of the blink in milliseconds
unsigned long blinkStartTime = 0;   // the time the LED started blinking

uint8_t counter_one = 0; // count how many change state in the button
uint8_t counter_two = 0; // count how many change state in the button

bool buttonState_one = false;
bool buttonState_two = false;
bool buttonPressed_three = false;
bool resetFlag = false;

//usually int is 16 its
void setup(){
    // Serial communication
    Serial.begin(9600);

    // Set the pin modes
    pinMode(buttonPin_one, INPUT);
    pinMode(buttonPin_two, INPUT);
    pinMode(buttonPin_three, INPUT);
    pinMode(ledPin_one_red, OUTPUT);
    pinMode(ledPin_two_yellow, OUTPUT);
    pinMode(ledPin_three_green, OUTPUT);
    
    // Turn off all the LEDs
    digitalWrite(ledPin_three_green, LOW);
    digitalWrite(ledPin_two_yellow, LOW);
    digitalWrite(ledPin_one_red, LOW);
    
    // last = digitalRead(buttonPin);
    // we expect that the counter is incremented many times (boucing effect)]
}

void blink_led(int led_pin, unsigned long duration) {
  unsigned long currentMillis = millis();

  if ((millis() - blinkStartTime) < duration) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
  /*if (currentMillis - previousMillis  >= 1000) { // flash at 1Hz
  //  previousMillis = currentMillis;
    digitalWrite(ledPin_one_red, !digitalRead(ledPin_one_red));
  }
  
  if (currentMillis >= duration) {
    resetFlag = true;
  }*/
}


void blink_led(int led_pin) {
  unsigned long currentMillis = millis();
  
  //if (currentMillis - previousMillis  >= 1000) { // flash at 1Hz
  //  previousMillis = currentMillis;
  //  digitalWrite(ledPin, !digitalRead(ledPin));
  //}

  if ((millis() - blinkStartTime) < blinkDuration) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }

}


unsigned long verify_last_debounce_time (int reading, int lastButtonState) {
  unsigned long lastDebounceTime = 0;
  
  if (reading != lastButtonState){
      // reset the bouncing timer
    lastDebounceTime = millis();
  }
  return lastDebounceTime;
}

void loop(){
    // read the state of the switch into a local variable
    int reading_one = digitalRead(buttonPin_one);

    // debounce the first button
    lastDebounceTime_one = verify_last_debounce_time(reading_one, buttonState_one);

    if ((millis() - lastDebounceTime_one) > debounceDelay) {
        // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
        // if the button state has changed
        if (reading_one != LOW) {
            buttonState_one = reading_one;

            // only toggle the LED if the new button state is HIGH
            if (buttonState_one == HIGH){
                counter_one++;
                Serial.println("Button 1 pressed");
                Serial.println(counter_one);
        }
      } 
    }

      // Check if the counts are even or odd
    if (counter_one % 2 == 0) {
        // If the count is even, turn on the yellow LED and turn off the green LED
        blink_led(ledPin_two_yellow);
        //digitalWrite(ledPin_two_yellow, HIGH);
        digitalWrite(ledPin_three_green, LOW);
    } else {
        // If the count is odd, turn on the green LED and turn off the yellow LED
         //igitalWrite(ledPin_two_yellow, LOW);
         //digitalWrite(ledPin_three_green, HIGH);
    }



    int reading_two = digitalRead(buttonPin_two);
    lastDebounceTime_two = verify_last_debounce_time(reading_two, buttonState_two);

    if ((millis() - lastDebounceTime_two) > debounceDelay) {
        // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
        // if the button state has changed
        if (reading_two != LOW) {
            buttonState_two = reading_two;

            // only toggle the LED if the new button state is HIGH
            if (buttonState_two == HIGH){
                counter_two++;
                Serial.println("Button 2 pressed");
                Serial.println(counter_two);
        }
      }  
    }

    // Check if the count is odd or even for button2 and blink accordingly
    if (counter_two % 2 == 1) {
      // If the count is odd, blink the green LED
      blink_led(ledPin_three_green);
      digitalWrite(ledPin_two_yellow, LOW);
    } else {
      // If the count is even, turn off the green LED
      digitalWrite(ledPin_three_green, LOW);
    }


    int reading_three = digitalRead(buttonPin_three);
    lastDebounceTime_three = verify_last_debounce_time(reading_three, buttonPressed_three);

    if ((millis() - lastDebounceTime_three) > debounceDelay) {
        // whatever the reading is at, its been there for longer that the debounce delay, so take it as the actual current state
        // if the button state has changed
        if (reading_three != LOW) {
            buttonPressed_three = reading_three;

            // only toggle the LED if the new button state is HIGH
            if (buttonPressed_three == HIGH){
                  buttonPressed_three = true;
                  Serial.println("Button 3 pressed");
                  // If button 3 was pressed, reset the counts and set the reset flag
                  counter_one = 0;
                  counter_two = 0;
                  resetFlag = true;
                  buttonPressed_three = false;
                  Serial.println("Count reset");
        }
      }  
    }

    // Check if the reset flag is set
    if (resetFlag) {
      // If the reset flag is set, blink the red LED for 10 seconds
      blink_led(ledPin_one_red, 10000);
      resetFlag = false;
      // digitalWrite(ledPin_one_red, LOW);
    }
}

