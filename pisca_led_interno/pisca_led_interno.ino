#define ESP12_LED 2 // GPIO2, D4
void setup() {
  pinMode(ESP12_LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}


void loop() {
  digitalWrite(ESP12_LED, LOW);   
  delay(20);                      
  digitalWrite(ESP12_LED, HIGH);  
  delay(20);                      
}
