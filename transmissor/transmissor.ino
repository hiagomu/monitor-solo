#include <VirtualWire.h>
#define Sensor1 A1  // Luminosidade: Cabo Azul 
#define Sensor2 A2  // Umidade: Cabo Vermelho 
#define Sensor3 A3 // PH: Cabo Verde

float iluminacaoFloat;
float umidadeFloat;
float phFloat;
int valores[3];

void setup() {
  Serial.begin(9600);
  
  analogReference(INTERNAL); // 1,1V para o ponto Vref do ADC; sinal de entrada: 0V a 1,1V
  
  vw_set_tx_pin(4); //Define o pino 4 como o transmissor de dados
  vw_setup(2000); // Bits per sec
  
  Serial.println("---Transmissor Iniciado---");
}

void loop() {
  
  iluminacaoFloat = analogRead(Sensor1);
  int iluminacao = calculaLuminosidade(iluminacaoFloat);
  
  umidadeFloat = analogRead(Sensor2);
  int umidade = calculaUmidade(umidadeFloat);
  
  phFloat = analogRead(Sensor3);
  int ph = calculaPh(phFloat);
  delay(1000);

  valores[0] = umidade;
  valores[1] = ph;
  valores[2] = iluminacao;

  Serial.println("------------------------");
  Serial.print("Umidade: ");
  Serial.println(valores[0]);
  Serial.print("PH: ");
  Serial.println(valores[1]);
  Serial.print("Luminosidade: ");
  Serial.println(valores[2]);
  

  send(valores);
}

// Funções
void send (int *message) {
  vw_send((uint8_t *)message, 10);
  vw_wait_tx(); // Aguarda o envio de dados
}

//Variação de 0 - 10
int calculaLuminosidade(float valor) {
  int luminosidade = 0;
  luminosidade = (valor / 0.23) / 220;
  return luminosidade;
}

//Variação de 0 - 10
int calculaUmidade(float valor) {
  int umidade = 0;
  umidade = valor / 100;
  return umidade;
}

int calculaPh(float valor) {
  int ph = 0;
  ph = valor / 58.75;
  if (ph > 14) {
    ph = 14;
  }
  return ph;
}
