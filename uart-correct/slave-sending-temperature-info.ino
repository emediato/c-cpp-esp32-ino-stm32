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
/*

✔O “Dispositivo Slave” deve enviar ao “Dispositivo Master”
duas indicações:
✔Caso a temperatura esteja entre 30oC e 35oC, o LED verde
do “Dispositivo Master” deve piscar com frequência de 1 Hz
✔Caso a temperatura seja maior do que 35oC, o LED verde
deve ser manter aceso, e o LED vermelho deve piscar.

*/
//sensor de temperatura usando o LM35
const int LM35 = A0; //define o pino que lera a saida do LM35
int temperatura; // variavel que armazenara a temperatura medida
long lastMillis = 0;   // the time the LED started blinking
char c = 0;

//funcao que sera executada uma vez quando ligar ou resetar o arduino
void setup()
{
  Serial.begin(9600);//inicializa a comunicacao serial
}

float convert_to_celsius(float reading) {
        float voltage = reading * 5.0;
        voltage /= 1024;
        float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)

        return temperatureC;
}


void loop()
{
 // if ((millis() - lastMillis) > debounceDelay) {
    int reading = analogRead(LM35);

    temperatura = convert_to_celsius(reading);  // int((float(analogRead(LM35))*5/(1024.0))/0.01);

        if(Serial.available() > 0)
        {
                c = Serial.read();

        if(c == 'o') {
                Serial.println(temperatura);
        }
    //Serial.write('\n'); // send newline character to indicate end of message

    //lastMillis = millis();
  }

}
