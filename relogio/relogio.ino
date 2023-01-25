/*
 * 
 * 
 *Referências: 
 *https://roboticadiy.com/iot-based-digital-world-clock-using-esp8266/ 
 *https://simple-circuit.com/esp8266-nodemcu-dht11-ssd1306/
 *
 *https://www.electrofun.pt/blog/webserver-com-temperatura-e-humidade-com-o-nodemcu-e-dht11/
*/
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <DHT.h>
#define DHTPIN  14                    // DHT11 data pin is connected to ESP8266 GPIO14 (NodeMCU D5)
#define DHTTYPE DHT11                 // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);             // Configure DHT library
char temperature[] = "00.0 C";
char humidity[]    = "00.0 %";

const char *ssid = "GL INTERNET_C140";
const char *password = "Engenhari@2019";

long utcOffsetInSeconds = -3*60*60; // Initializing with Fortaleza Time, UTC -4 Hours
int h,m,s;
int q=1;
int activate = 1;

unsigned long previousMillis = 0; 
const long interval = 1000; 


char daysOfTheWeek[7][4] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "3.pool.ntp.org", utcOffsetInSeconds);
// ----------------------------------------------------------------
void setup(){
Serial.begin(115200);
pinMode(2, INPUT);
dht.begin();                // Initialize the DHT library
lcd.init(); /////////////////////// Correcao
lcd.backlight(); /////////////////////// Correcao
WiFi.begin(ssid, password);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Connecting Wifi");
lcd.setCursor(0, 1);

while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 ); /////////////////////// Correcao
lcd.print(".");
Serial.print ( "." );
}
timeClient.begin();
lcd.clear();
}
// ----------------------------------------------------------------
void loop() {
// Read humidity
byte RH = dht.readHumidity();
//Read temperature in degree Celsius
byte Temp = dht.readTemperature();

temperature[0] = Temp / 10 + '0';
temperature[1] = Temp % 10 + '0';
humidity[0]    = RH / 10   + '0';
humidity[1]    = RH % 10   + '0';
// print data on serial monitor
Serial.printf("Temperature = %02u°C\r\n", Temp);
Serial.printf("Humidity    = %02u %%\r\n\r\n", RH);

lcd.setCursor(9, 1);
lcd.print(Temp);
lcd.setCursor(11, 1);
lcd.print("C");

lcd.setCursor(13, 1);
lcd.print(RH);
lcd.setCursor(15, 1);
lcd.print("%");

unsigned long currentMillis = millis();
/*
int button_pressed = digitalRead(2); /// tirar
if (button_pressed == HIGH){ /// tirar
q++; /// tirar
if (q >= 16){
q=1;}
activate = 1;
}
Serial.println(q);
Serial.println(utcOffsetInSeconds);
*/

lcd.setCursor(0, 0);
lcd.print("Fortaleza");
// utcOffsetInSeconds = -3*60*60; //-4 UTC

// Contagem de horas
if (currentMillis - previousMillis >= interval) {
previousMillis = currentMillis;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

timeClient.forceUpdate();
h = timeClient.getHours();
m = timeClient.getMinutes();
s = timeClient.getSeconds();

Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(", ");
Serial.print(timeClient.getHours());
Serial.print(":");
Serial.print(timeClient.getMinutes());
Serial.print(":");
Serial.println(timeClient.getSeconds());
//Serial.println(timeClient.getFormattedTime());

// lcd.setCursor(0, 1);
//lcd.print(daysOfTheWeek[timeClient.getDay()]);

lcd.setCursor(0, 1);
if (h <= 9){
lcd.print("0");
lcd.print(h);}
else{
lcd.print(h);}
lcd.print(":");
if (m <= 9){
lcd.print("0");
lcd.print(m);}
else{
lcd.print(m);}
lcd.print(":");
if (s <= 9){
lcd.print("0");
lcd.print(s);}
else{
lcd.print(s);}
}
}
