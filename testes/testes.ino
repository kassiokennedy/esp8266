/*
 * 
#include <Wire.h>
#define TEMPOLEITURA 100
#define TEMPOESPERA 3000
byte endereco;
byte codigoResultado=0;
byte dispositivosEncontrados=0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!Serial); 
  scanI2c();           
}
void scanI2c(){
    for (endereco=0; endereco<128; endereco++){
    Wire.beginTransmission(endereco);
    codigoResultado = Wire.endTransmission();
    if (codigoResultado==0){
      Serial.print ("Dispositivo I2c detectado no endereço: ");
      Serial.println(endereco,HEX);
      dispositivosEncontrados++;
      delay(TEMPOESPERA);
    }
    delay(TEMPOLEITURA);
  }
  if (dispositivosEncontrados>0){
    Serial.print("Foi encontrado um total de: ");
    Serial.print(dispositivosEncontrados);
    Serial.println(" dispositivos");
  }
  else{
    Serial.println("Nenhum dispositivo foi encontrado !!!");
  }
}
void loop() {
}
 */
#include <Wire.h>
 
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
}
 
void loop() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);          
}
