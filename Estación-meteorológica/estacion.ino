#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define R_LED 9
#define G_LED 10
#define B_LED 11
#define ON_LED 5
#define SERVO 3

// Pines analógicos
#define POTENC A0
#define LM35 A1
#define LDR_PIN A2

// Pin sensor digital
#define DHT_PIN 2

DHT11 dhtSensor(DHT_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo miServo;  // Crea el objeto servo
int pos = 0;    // Posición del servo

// Iconos personalizados
byte termometro[8] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

byte gota[8] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B10111,
  B11111,
  B01110
};

byte corazon[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte sol[8] = {
  B10101,
  B01110,
  B11111,
  B11011,
  B11111,
  B01110,
  B10101,
  B00000
};

// º
byte simboloGrados[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  Serial.begin(9600);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  pinMode(ON_LED, OUTPUT);

  miServo.attach(SERVO);

  lcd.init();
  lcd.backlight();
  digitalWrite(ON_LED, HIGH);
  // Registro de caracteres especiales en la memoria CGRAM (0 a 4)
  lcd.createChar(0, termometro);
  lcd.createChar(1, gota);
  lcd.createChar(2, corazon);
  lcd.createChar(3, sol);
  lcd.createChar(4, simboloGrados);
}

void loop() {
    float t = temperaturaHumedad(); // lectura+escritura DHT11 y LM35
    float td = temperaturaDeseada(); // lectura+escritura potenciómetro
    if (t>td) {
      rgb_color("rojo");
      abanicar_con_servo();
    } else {
      rgb_color("azul");
    }
    luminosidad(); // lectura+escritura LDR
    delay(1000);
}

void abanicar_con_servo() {
  for (int i=0; i<10; i++) {
    if (i%2==0) {
      miServo.write(180); 
    } else {
      miServo.write(0); 
    }
    delay(200);
  }
}

float temperaturaHumedad() {
  // 1. Lectura DHT11
  int dhtTemp = 0;
  int dhtHum = 0;
  dhtSensor.readTemperatureHumidity(dhtTemp, dhtHum);

  // 2. Lectura LM35 con referencia interna de 1.1 V
  analogReference(INTERNAL);
  analogRead(LM35); // Lectura de descarte para estabilizar ADC tras cambio de referencia
  delay(10);
  
  long sumaLM35 = 0;
  for (int i = 0; i < 10; i++) {
    sumaLM35 += analogRead(LM35);
    delay(2);
  }
  float readingLM35 = (float)sumaLM35 / 10.0;
  float lm35Temp = (readingLM35 * (1100.0 / 1024.0)) / 10.0;

  // Cálculo de temperatura media
  float tempMedia = (lm35Temp + (float)dhtTemp) / 2.0;

  // Actualización TºC y H% en LCD
  // Fila 0: [Termometro] TempMedia°C  [Gota] Humedad%
  lcd.setCursor(0, 0);
  lcd.write(byte(0)); // Termómetro
  lcd.setCursor(2, 0);
  if (tempMedia < 10.0) lcd.print(" ");
  lcd.print(tempMedia, 1);
  lcd.write(byte(4)); // Grado °
  lcd.print("C");

  lcd.setCursor(10, 0);
  lcd.write(byte(1)); // Gota
  if (dhtHum < 10) lcd.print("  ");
  else if (dhtHum < 100) lcd.print(" ");
  lcd.print(dhtHum);
  lcd.print("% ");

  return tempMedia;
}

float temperaturaDeseada() {
  analogReference(DEFAULT);
  analogRead(POTENC); // Lectura de descarte para estabilizar ADC a 5 V
  delay(10);

  int potVal = analogRead(POTENC);
  float temp_deseada = obtenerTemperatura(potVal);

  // Fila 1 izquierda: [Corazon] TempDeseada°C  [Sol]
  lcd.setCursor(0, 1);
  lcd.write(byte(2)); // Corazón
  lcd.setCursor(2, 1);
  if (temp_deseada < 10.0) lcd.print(" ");
  lcd.print(temp_deseada, 1);
  lcd.write(byte(4)); // Grado °
  lcd.print("C");

  return temp_deseada;
}

void luminosidad() {
  int ldrVal = analogRead(LDR_PIN);
  int luzPorcentaje = map(ldrVal, 0, 1023, 0, 100);
  luzPorcentaje = constrain(luzPorcentaje, 0, 100);

  // Fila 1 derecha: [Sol] Luz%
  lcd.setCursor(10, 1);
  lcd.write(byte(3)); // Sol
  if (luzPorcentaje < 10) lcd.print("  ");
  else if (luzPorcentaje < 100) lcd.print(" ");
  lcd.print(luzPorcentaje);
  lcd.print("% ");
}

float obtenerTemperatura(int x) {
  int indice = map(x, 0, 1023, 0, 44);
  return 10.0 + (indice * 0.5);
}

void rgb_color(String color) {
  // Convertimos el texto a minúsculas para evitar errores de mayúsculas
  color.toLowerCase(); 

  if (color == "white" || color == "blanco") {
    analogWrite(R_LED, 180);
    analogWrite(G_LED, 200);
    analogWrite(B_LED, 100);
  } 
  else if (color == "red" || color == "rojo") {
    analogWrite(R_LED, 255);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
  else if (color == "green" || color == "verde") {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 255);
    analogWrite(B_LED, 0);
  }
  else if (color == "blue" || color == "azul") {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 255);
  }
  else if (color == "yellow" || color == "amarillo") {
    analogWrite(R_LED, 255);
    analogWrite(G_LED, 255);
    analogWrite(B_LED, 0);
  }
  else if (color == "cyan" || color == "celeste") {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 255);
    analogWrite(B_LED, 255);
  }
  else if (color == "magenta" || color == "rosa") {
    analogWrite(R_LED, 255);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 255);
  }
  else if (color == "orange" || color == "naranja") {
    analogWrite(R_LED, 255);
    analogWrite(G_LED, 128); // El verde a la mitad da el tono naranja
    analogWrite(B_LED, 0);
  }
  else if (color == "purple" || color == "morado") {
    analogWrite(R_LED, 128);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 128);
  }
  else if (color == "off" || color == "apagado") {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
  else {
    // Si el color no existe, parpadea en rojo como alerta de error
    for(int i = 0; i < 3; i++) {
      analogWrite(R_LED, 255); delay(100);
      analogWrite(R_LED, 0);   delay(100);
    }
  }
}