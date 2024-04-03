int pinSensor = 2;    //pino do sensor Hall. Retorna LOW quando ima se aproxima.
int pinControle = 3;    //pino do PWM via MOSFET
int rpm;
float control = 0;
int msg;
String mensagem;
int erro;
int button = 4;
int led = 5;
int setpoint;
volatile byte pulsos;   //variavel auxiliar para 
unsigned long timeold;
//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 1;
void contador()   //Funcao contador para calculo de numero de rpm
{
   pulsos++;   //Incrementa contador
}
void setup()
{
  Serial.begin(9600);   //Inicia comunicacao serial
  pinMode(button, INPUT_PULLUP); //botao
  pinMode(pinSensor, INPUT);    //Pino do sensor como entrada
  pinMode(led, OUTPUT);
  //Aciona o contador a cada pulso
  attachInterrupt(digitalPinToInterrupt(pinSensor), contador, FALLING);    //Interrompe leitura do contador quando o sinal do sensor muda de HIGH para LOW
  pulsos = 0;
  rpm = 0;
  timeold = 0;
}

void controlador(int setpoint){

  erro = setpoint - rpm;

  if(erro > 0 && control <= 250){
    if(erro > 200 && control<= 205){control = control+25;}
    control = control + 5;
    }
  else if(erro < 0 && control >= 5){
    if(erro < -200 && control>= 50){control = control-25;}
    control = control - 5;
    }
  Serial.print("PWM: ");
  Serial.println(control);
  Serial.print("Referencia: ");
  Serial.println(setpoint);
  Serial.println();
  delay(1000);
  }


void loop(){

  if(digitalRead(button) == LOW){
    digitalWrite(led, HIGH);
    control = 0;
    setpoint = 0;
    Serial.println();
    Serial.println("BOTAO DE EMERGENCIA ATIVADO");
    Serial.println("");
    delay(5000);
    digitalWrite(led, LOW);
    }
  
  while (Serial.available()){
    mensagem = Serial.readString();
    Serial.print("Voce digitou:");
    Serial.println(mensagem);
    setpoint = mensagem.toInt();
    }
    
  if (millis() - timeold >= 1000){  //Atualiza contador a cada segundo
    
    detachInterrupt(digitalPinToInterrupt(pinSensor));   //Desabilita interrupcao durante o calculo
    rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos;    //Calculo de rpm
    timeold = millis();
    pulsos = 0;
    //Mostra o valor de RPM no serial monitor
    Serial.print("RPM = ");
    Serial.println(rpm, DEC);
    
    attachInterrupt(digitalPinToInterrupt(pinSensor), contador, FALLING);    //Habilita interrupcao
  }
  
  controlador(setpoint);
  analogWrite(pinControle, control);
  
}
