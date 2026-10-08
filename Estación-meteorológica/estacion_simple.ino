#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>

#define ON_LED 5
#define LM35 A1
#define LDR_PIN A2
#define DHT_PIN 4
#define CONSULT_BTN 2

DHT11 dhtSensor(DHT_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

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

void despertar() {
  // Solo despierta el microcontrolador, no necesita código dentro
}

void setup() {
  Serial.begin(9600);

  pinMode(ON_LED, OUTPUT);
  pinMode(CONSULT_BTN, INPUT_PULLUP);

  lcd.init();

  // Registro de caracteres especiales en la memoria CGRAM (0 a 4)
  lcd.createChar(0, termometro);
  lcd.createChar(1, gota);
  lcd.createChar(2, corazon);
  lcd.createChar(3, sol);
  lcd.createChar(4, simboloGrados);
}

void loop() {
    // 1. Encender pantalla LCD y LED
    digitalWrite(ON_LED, HIGH);
    lcd.backlight();
    // 2. Medir y mostrar en pantalla
    temperaturaHumedad(); // lectura+escritura DHT11 y LM35
    temperaturaDeseada(); // establecida por defecto en 26.0ºC
    luminosidad(); // lectura+escritura LDR
    // 3. Mantener encendido 3 segundos para leer los datos
    delay(3000); // 3s para ver info
    // 4. Apagar pantalla y LED para ahorrar energía
    lcd.clear();
    lcd.noBacklight();
    digitalWrite(ON_LED, LOW);
    // 5. Entrar en modo suspensión profunda
    entrarEnSuspension();
}

void entrarEnSuspension() {
    attachInterrupt(digitalPinToInterrupt(CONSULT_BTN), despertar, LOW);

    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

    detachInterrupt(digitalPinToInterrupt(CONSULT_BTN));
}

void temperaturaHumedad() {
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
}

void temperaturaDeseada() {
  float temp_deseada = 24.0; // hardcoded

  // Fila 1 izquierda: [Corazon] TempDeseada°C  [Sol]
  lcd.setCursor(0, 1);
  lcd.write(byte(2)); // Corazón
  lcd.setCursor(2, 1);
  if (temp_deseada < 10.0) lcd.print(" ");
  lcd.print(temp_deseada, 1);
  lcd.write(byte(4)); // Grado °
  lcd.print("C");
}

void luminosidad() {
    analogReference(DEFAULT);
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