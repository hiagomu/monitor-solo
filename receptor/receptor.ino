#include <VirtualWire.h>
#include <EEPROM.h>

#define espacoEEPROM 1000

int valor_recebido_RF;
char recebido_RF_char[40];
int newmessage;

void EEPROMWriteLong(int address, long value);
long EEPROMReadLong(int address);


byte message[VW_MAX_MESSAGE_LEN];    // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN; // Armazena o tamanho das mensagens

void setup()   {
  Serial.begin(9600);

  vw_set_rx_pin(4); //Define o pino 4 do Arduino como entrada de dados do receptor
  vw_setup(2000); //Bits por segundo
  vw_rx_start();  //Inicializa o receptor

  newmessage = EEPROMReadInt(1);
}
 
void loop(){
  
  uint8_t message[VW_MAX_MESSAGE_LEN];    
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(message, &msgLength)) {
      Serial.print(message[0]);
      Serial.print(",");
      Serial.print(message[2]);
      Serial.print(",");
      Serial.println(message[4]);
      
      newmessage = atol(recebido_RF_char);
      EEPROMWriteInt(1, newmessage);
  }
}

//Funções
void EEPROMWriteInt(int address, int value) {
   byte hiByte = highByte(value);
   byte loByte = lowByte(value);

   EEPROM.write(address, hiByte);
   EEPROM.write(address + 1, loByte);   
}

int EEPROMReadInt(int address) {
   byte hiByte = EEPROM.read(address);
   byte loByte = EEPROM.read(address + 1);
   
   return word(hiByte, loByte); 
}
