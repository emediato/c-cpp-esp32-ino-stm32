////sensor de temperatura usando o LM35
//
//const int LM35 = A0; //define o pino que lera a saida do LM35
//int temperatura; // variavel que armazenara a temperatura medida
//
////funcao que sera executada uma vez quando ligar ou resetar o arduino
//void setup()
//{
//  Serial.begin(9600);//inicializa a comunicacao serial
//}
//
//void loop()
//{
//
//  //getting the voltage reading from the temperature sensor
// int reading = analogRead(LM35);  
// 
// // converting that reading to voltage, for 3.3v arduino use 3.3
// float voltage = reading * 5.0;
// voltage /= 1024.0; 
// 
// // print out the voltage
// Serial.print(voltage); Serial.println(" volts");
// 
// // now print out the temperature
// float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
//                                               //to degrees ((voltage - 500mV) times 100)
// Serial.print(temperatureC); Serial.println(" degrees C");
// 
// // now convert to Fahrenheit
// float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
// Serial.print(temperatureF); Serial.println(" degrees F");
// 
// delay(1000);    
//}

//sensor de temperatura usando o LM35
#define ledRed 5
#define ledGreen 6

int ledPin = 13; // internal LED is connected to built-in LED pin
int ledState = LOW; 

int temp = 0 ; // variable to store temperature reading from slave

const int buttonPin = 7;   // pin 2

bool green_on = false;
bool red_on  = false;
bool pinState = LOW;

String inString = "";  // string to hold input

unsigned long lastMillis = 0;   // the time the LED started blinking

const unsigned long blinkDuration = 1000; // the duration of the blink in milliseconds
static uint32_t lastPressTime1 = 0;

//BUTTON DEBOUNCING
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int time_green_led = 0;
int time_red_led = 0;
bool last_state_green_led = false;
bool last_state_red_led = false;

unsigned long time = 0;
unsigned long previous_time = 0;
/*


✔O “Dispositivo Master” deve
✔Solicitar a temperatura ao “Dispositivo Slave” quando o
botão for pressionado e receber o valor correspondente. Se
a temperatura estiver acima de 25oC, o LED Interno da
placa do “Dispositivo Master” deve ser aceso. Caso
contrário, deve se manter apagado.


*/

//funcao que sera executada uma vez quando ligar ou resetar o arduino
void setup()
{
  pinMode(ledPin, OUTPUT); // LED as OUTPUT
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buttonPin, INPUT); //BUTTON INPUT  
  
  Serial.begin(9600);//inicializa a comunicacao serial
}


void blink_leds() {
  	previous_time = time;
    time = millis();
  	if (time < previous_time)
    {
     return; 
    }
    if (red_on && ((time - time_red_led >= blinkDuration) || time_red_led == 0) )
    {
        time_red_led = time;
        last_state_red_led = !last_state_red_led;
        digitalWrite(ledRed, last_state_red_led);
    } else {
        digitalWrite(ledRed, LOW);
    }
 	if (green_on && ((time - time_green_led >= blinkDuration) || time_green_led == 0) )
    {
        time_green_led = time;
        last_state_green_led = !last_state_green_led;
        digitalWrite(ledGreen, last_state_green_led);
    }
    else
    {
        digitalWrite(ledGreen, LOW);
    }

  
    /*if (green_on) {
        digitalWrite(ledGreen, (time / blinkDuration) % 2);
    } else {
        digitalWrite(ledGreen, LOW);
    }*/

}

int read_serial() {
    // clear the string for new input:
  	inString = "";
  	while (Serial.available() > 0) {
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string, then the string's value:
      if (inChar == '\n') {
        Serial.print("Value:");
        Serial.println(inString.toInt());

        return inString.toInt();
            
    }
  }
}

void loop() {
  blink_leds();
  digitalWrite(ledPin, LOW);
  
  int reading = digitalRead(buttonPin);
  //temp =0;
   
  //BUTTON DEBOUNCING
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
    
  if ((millis() - lastDebounceTime) > debounceDelay) {
  	// if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {

        //write it down in the slave serial 
      	Serial.println('o'); 
      } 
      else {
        temp = read_serial();

        //button state is LOW
        //call to read Serial console
        Serial.println(temp);
      }
    }
  } 


  if (int(temp) > 25) {
  	//pinState = !pinState; // inverter estad
    digitalWrite(ledPin, HIGH);
    //Serial.println(temp);
  }
  if (temp >= 30 && temp <= 35) {
    Serial.println(temp);
    green_on = true;
    red_on = false;
    digitalWrite(ledPin, pinState);
  }
  else if (temp > 35){  
    green_on = false;
    red_on = true;
  }
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}



