// contador que conta o numero de vezes que um botao push-button mudou de estado.botao

//  when u press a button, turn on LED

//  with millis boucing treatment

#define BOUNCE_TIME 200

// Ao apertar e soltar o botão, esperamos que o contador incremente várias vezes (efeito bouncing).
const int buttonPin_one = 2;   // pin 2
const int buttonPin_two = 3;   // pin 3
const int buttonPin_three = 4; // pin 4

const int ledPin_one_red = 12;    // pin 13 - LED
const int ledPin_two_yellow = 8; // pin 12 - LED
const int ledPin_three_green = 13; // pin 8 - LED
const int ledPin_four_white = 9; // pin 9 - LED

unsigned long print_timer = 0; // timer in serial port UART0 - miliseconds
unsigned long previousMillis = 0;

unsigned long lastDebounceTime_one = 0;   // the last time the output pin was toggled
unsigned long lastDebounceTime_two = 0;   // the last time the output pin was toggled
unsigned long lastDebounceTime_three = 0; // the last time the output pin was toggled

// unsigned long because the value will be long in a period of time
unsigned long debounceDelay = 200; // the debounce time ; increase if the output flickers
// 50 miliseconds
const unsigned long blinkDuration = 1000; // the duration of the blink in milliseconds
unsigned long blinkStartTime = 0;         // the time the LED started blinking

uint8_t counter_one = 0; // count how many change state in the button
uint8_t counter_two = 0; // count how many change state in the button
uint8_t counter_three = 0; // count how many change state in the button

bool buttonState_three = false;
bool resetFlag = false;


bool buttonState_one = false;
bool buttonState_two = false;


bool green_on = false;
bool yellow_on = true;

bool last_state_yellow_led = false;
bool last_state_green_led = false;
bool last_state_red_led = false;

unsigned long time_green_led = 0;
unsigned long time_yellow_led = 0;
unsigned long time_red_led = 0;

// usually int is 16 its
void setup()
{
    // Serial communication
    Serial.begin(9600);
    // Set the pin modes
    pinMode(buttonPin_one, INPUT);
    pinMode(buttonPin_two, INPUT);
    pinMode(buttonPin_three, INPUT);
    pinMode(ledPin_one_red, OUTPUT);
    pinMode(ledPin_two_yellow, OUTPUT);
    pinMode(ledPin_three_green, OUTPUT);
    pinMode(ledPin_four_white, OUTPUT);

    // Turn off all the LEDs
    digitalWrite(ledPin_three_green, LOW);
    digitalWrite(ledPin_two_yellow, LOW);
    digitalWrite(ledPin_one_red, LOW);
    digitalWrite(ledPin_four_white, HIGH);

    // last = digitalRead(buttonPin);
    // we expect that the counter is incremented many times (boucing effect)]
  
}

static uint32_t lastPressTime1 = 0;
static uint32_t lastPressTime2 = 0;
static uint32_t lastPressTime3 = 0;
unsigned long time = 0;
unsigned long previous_time = 0;

void blink_leds()
{// millis eh um contador incremental na escala millisegundos
// usei variaveis globais como flag
  	previous_time = time;
    time = millis();
  	if (time < previous_time) // assim que chega no overflow reseta pra 0
    {
     return; 
    }
  	
    if (green_on && ((time - time_green_led >= blinkDuration) || time_green_led == 0) )
    {
        time_green_led = time;
        last_state_green_led = !last_state_green_led;
        digitalWrite(ledPin_three_green, last_state_green_led);
    }
    else
    {
        digitalWrite(ledPin_three_green, LOW);
    }

    if (yellow_on && ((time - time_yellow_led >= blinkDuration) || time_yellow_led == 0) )
    {
        time_yellow_led = time;
        last_state_yellow_led = !last_state_yellow_led;
        digitalWrite(ledPin_two_yellow, last_state_yellow_led);
    }
    else
    {
        digitalWrite(ledPin_two_yellow, LOW);
    }

    if (resetFlag && ((time - time_red_led >= blinkDuration) || time_red_led == 0) )
    {
      	time_red_led = time;
        last_state_red_led = !last_state_red_led;
        digitalWrite(ledPin_one_red, last_state_red_led);
      	counter_three++;
      	
      	if (counter_three % 2 == 0)
        {
          Serial.print("Seconds since reset: ");
      	  Serial.println(counter_three/2);
        }
        if (counter_three == 20)
        {
            resetFlag = false;
            counter_three = 0;
          	digitalWrite(ledPin_one_red, LOW);
          	counter_one = 0;
            counter_two = 0;
            yellow_on = false;
            green_on = false;
        }
    }
    else
    {
        digitalWrite(ledPin_one_red, LOW);
    }
}

void blink_led(int led_pin) {
  unsigned long currentMillis = millis();

  if ((millis() - blinkStartTime) < blinkDuration) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }

}
void loop() {
    blink_leds();

    if (digitalRead(buttonPin_one) && (millis() - lastPressTime1 > BOUNCE_TIME)) {
        lastPressTime1 = millis();
        counter_one++;
        Serial.println("Button 1 pressed");
        Serial.println(counter_one);
        if (counter_one % 2 == 0) {
            yellow_on = true;
            green_on = false;
        } else {
            yellow_on = false;
          	green_on = false;
          
        }
    }

    if (digitalRead(buttonPin_two) && (millis() - lastPressTime2 > BOUNCE_TIME)) {
      lastPressTime2 = millis();
      counter_two++;
      Serial.println("Button 2 pressed");
      Serial.println(counter_two);
      if (counter_two % 2 != 0) {
        yellow_on = false;
        green_on = true;
      } else {
        green_on = false;
        yellow_on = false;
      }
      Serial.println(counter_two);
      Serial.println(green_on);
	}
  
  if (digitalRead(buttonPin_three) && (millis() - lastPressTime3 > BOUNCE_TIME)) {
    lastPressTime3 = millis();
    buttonState_three = true;
    Serial.println("Button 3 pressed");
    // If button 3 was pressed, reset the counts and set the reset flag
    counter_one = 0;
    counter_two = 0;
    yellow_on = false;
    green_on = false;
    resetFlag = true;
    buttonState_three = false;
    Serial.println("Count reset");
	}
}