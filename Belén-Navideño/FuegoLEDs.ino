// Pines PWM para los LEDs de la hoguera
const int ledPin1 = 3; // LED Amarillo / Naranja
const int ledPin2 = 5; // LED Rojo (brasa base)
const int ledPin3 = 6; // LED Naranja

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  // LED 1: Variación amplia de brillo para simular la llama principal
  analogWrite(ledPin1, random(100, 255));
  
  // LED 2: Mantener más bajo y con menos variación para simular el carbón/brasa
  analogWrite(ledPin2, random(40, 150));
  
  // LED 3: Destellos rápidos intermitentes
  analogWrite(ledPin3, random(120, 255));

  // Intervalo aleatorio corto entre cambios para un efecto dinámico
  delay(random(40, 110));
}