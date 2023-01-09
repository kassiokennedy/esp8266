/*
 * 
 * 
 *Referências: 
 *https://roboticadiy.com/iot-based-digital-world-clock-using-esp8266/ 
 *
 *
*/

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid = "GL INTERNET_C140";
const char *password = "Engenhari@2019";

long utcOffsetInSeconds = -3*60*60; // Initializing with Fortaleza Time, UTC -4 Hours
int h,m,s;
int q=1;
int activate = 1;

unsigned long previousMillis = 0; 
const long interval = 1000; 


char daysOfTheWeek[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "3.pool.ntp.org", utcOffsetInSeconds);

void setup(){
Serial.begin(115200);
pinMode(2, INPUT);
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

void loop() {

unsigned long currentMillis = millis();

int button_pressed = digitalRead(2); /// tirar
if (button_pressed == HIGH){ /// tirar
q++; /// tirar
if (q >= 16){
q=1;}
activate = 1;
}

Serial.println(q);
Serial.println(utcOffsetInSeconds);


lcd.setCursor(4, 0);
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

lcd.setCursor(2, 1);
lcd.print(daysOfTheWeek[timeClient.getDay()]);
lcd.setCursor(6, 1);
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
