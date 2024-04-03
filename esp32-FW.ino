/*

power (W)
battery life (hours)
reliability (MTTF)
CPU freq (Hz
device temp (degrees )
MFG yield
throughput (flops/sec)
mem size (GB)
latency (us)
die area (mm^2)
************************************************************************************************
************************************************************************************************

// esp32

// SPI will hold our prgram storage and memory

// USB connection
// USB TO UART inside the chip


inertial measurement unit so an integrated circuit a sensor containyn gyroscopes
this is used with SPI



************************************************************************************************
************************************************************************************************
FLASHING


// setup arduino with
// file > preferences
// additional boards managers https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


//tools > boards > managers > esp32 by espressif systems

// Hardware

// tools > borads > esp32 > esp32C3 Dev Module


// TOOLS > USB CDC ON BOOT -> ENABLED -> USB TO UART ADAPTER TO DEBU IN ARDUINO
serial monitor to be plot

// TOOLS >  CORE DEBUG LEVEL -: INFO
CPU FREQ 160 MHz
TOOLS >  FLASH FREQUENCY 400 MHZ

SPI QIO

FLASH SIZE  > PARTITION MINIMAL

UPLOAD SPEED 115200 
921600

// TOOLS > port COMX (ESP32-S3-USB-OTG)>   


end 

hard resetting via RTS pin.........

************************************************************************************************
18.33

https://www.youtube.com/watch?v=m6njN9Y7PF0
************************************************************************************************
************************************************************************************************




*/

//u want to use the GPIO number

#define L3 0 //led L3 ligando no pino GPIO-0
#define L8 15 //led L8 ligando no pino GPIO-15
#define LED_A_PIN 3 //led L8 ligando no pino GPIO-15
#define LED_B_PIN 15 //led L8 ligando no pino GPIO-15

#define SPI_MOSI 7
#define SPI_MISO 2
#define SPI_CLK 6 
#define SPI_ACC_NCS 10


#include <SPI.h>


SPIClass *spiAcc;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_A_PIN, OUTPUT);
  pinMode(LED_A_PIN, OUTPUT);

  //instantiate class and chip select pin 
  spiAcc->begin(SPI_MOSI, SPI_MISO, SPI_CLK, SPI_ACC_NCS);
  pinMode(SPI_ACC_NCS_PIN, OUTPUT);
  digitalWrite(SPI_ACC_NCS_PIN, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_A_PIN, LOW);
  digitalWrite(LED_B_PIN, HIGH);
  Serial.println("Toggele 1 ");
  delay(250);

  digitalWrite(LED_B_PIN, LOW);
  digitalWrite(LED_A_PIN, HIGH);
  Serial.println("Toggele 2 ");
  delay(250);
}

  /*
  ************************************************************************************************
  Taxa de comunicação: até 10Mbit/s (depende do dispositivo destino);
  Método de transmissão: síncrona;
  Número de fios: 3 fios, mais um fio para cara escravo e um fio para Gnd;
  Máximo de dispositivos comunicando: não há limitação, depende do quanto se pode selecionar
  os escravos
  ************************************************************************************************
  SPI GPIO NUMBERS
    s SCLK (gera o sinal de sincronismo), MOSI (que transmite o dado do mestre para
    o escravo) e o MISO (que transmite o dado do escravo para o mestre). Há também o sinal de CS (Chip
    Select) ou SS (Select Slave) que habilita o escravo que irá se comunicar 

  */
uint8_t calculateChecksum(uint8_t* payload, bool excludeLastByte) {
    uint8_t checksum = 0;
    uint8_t payloadSize = excludeLastByte ? 254 : 255;
    // Long code here...
}

/*

Insecure of Code Stability → Kill with Unit Test
We have reduced code bloats into a single function. And this gives us one more benefit: we can test it individually. By using unit test, we can ensure that the code is consistent and outputs the correct value as we expect.

Unit testing is basically calling calculateChecksum() with known payload, we compare the actual checksum with the expected value. If they match, we’re fine.

Remember that unit testing doesn’t necessarily use any testing framework like Catch2, Google Test. As long as you could verify the output, you’re doing unit test (However, manual testing is painful as the code grows, that’s why we use testing framework, to do automated unit testing)

*/
