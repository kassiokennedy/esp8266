#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// DHT 11
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11

// Replace with your network credentials
/*
//----------------Login---------------------------------
const char *ssid = "GL INTERNET_C140";          // WIFI password
const char *password = "Engenhari@2019"; // ID Password
//----------------IP definition ------------------------
IPAddress ip(10, 0, 0, 200);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
*/
  //----------------Login---------------------------------
  const char *ssid = "TVC";          // WIFI password
  const char *password = "504b2014"; // ID
  //----------------IP definition ------------------------
  IPAddress ip(192, 168, 10, 175);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

//-----------------DHT 11----------------------------------------------------
#define DHTPIN 4 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11
DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

float temperatura; //variável para armazenar a temperatura
float umidade; //Variável para armazenar a umidade
//---------------------------------------------------------------------------
int i = 0;

ESP8266WebServer server(80); // instantiate server at port 80 (http port)

String page = "";
String text = "";
double data;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void){
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  delay(100);
  Serial.begin(115200);
  WiFi.begin(ssid, password); // begin WiFi connection
  WiFi.config(ip, gateway, subnet);//Definicao do IP
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.localIP());

  server.on("/data.txt", []()
  {
    text = (String)data;
    server.send(200, "text/html", text);
  });
  server.on("/", handle_OnConnect);
  server.begin();
  Serial.println("Web server started!");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(void){
  
  server.handleClient();
  i++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handle_OnConnect() {
  temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  umidade = dht.readHumidity(); //Realiza a leitura da umidade
  Serial.print("Temperatura: ");
  Serial.print(temperatura); //Imprime no monitor serial o valor da temperatura lida
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade); //Imprime no monitor serial o valor da umidade lida
  Serial.println(" %");
  server.send(200, "text/html", EnvioHTML(temperatura, umidade)); //Envia as informações usando o código 200, especifica o conteúdo como "text/html" e chama a função EnvioHTML
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
String EnvioHTML(float Temperaturastat, float Umidadestat) { //Exibindo a página da web em HTML
  String ptr = "<!DOCTYPE html> <html>\n"; //Indica o envio do código HTML
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; //Torna a página da Web responsiva em qualquer navegador Web
  ptr += "<meta http-equiv='refresh' content='2'>";//Atualizar browser a cada 2 segundos
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Monitor de Temperatura e Umidade</title>\n"; //Define o título da página

  //Configurações de fonte do título e do corpo do texto da página web
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #000000;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Monitor de Temperatura e Umidade</h1>\n";
  ptr += "<h2>NODEMCU ESP8266 Web Server</h2>\n";

  //Exibe as informações de temperatura e umidade na página web
  ptr += "<p><b>Temperatura: </b>";
  ptr += (float)Temperaturastat;
  ptr += " Graus Celsius</p>";
  ptr += "<p><b>Umidade: </b>";
  ptr += (float)Umidadestat;
  ptr += " %</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;

}
