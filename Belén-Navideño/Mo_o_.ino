// https://solectroshop.com/es/content/43-arduino-mas-avanzadas-funccionalidades-de-motores-paso-a-paso?srsltid=AYCX9vLRAiKOzNf3fK42gHiTYS3JoOy7KLk31mRCFpnYn8RoNGzvaddE
#include <Stepper.h>
#include <avr/pgmspace.h>

// -------------------------------------------------------------
// 1. CONFIGURACIÓN DEL MOTOR PASO A PASO (28BYJ-48 + ULN2003)
// -------------------------------------------------------------
const int STEPS_PER_REV = 2048; 
// Nota: En la secuencia típica del ULN2003 se intercambian pines 9 y 10 (8, 10, 9, 11)
Stepper motorMolino(STEPS_PER_REV, 8, 10, 9, 11);

// -------------------------------------------------------------
// 2. CONFIGURACIÓN DE ILUMINACIÓN Y ZUMBADOR
// -------------------------------------------------------------
const int pinLed1 = 5;      // PWM (evitamos pines 3 y 11 por conflicto con tone())
const int pinLed2 = 6;      // PWM
const int pinBuzzer = 7;    // Salida para el zumbador pasivo
const int pinPot = A0;      // Potenciómetro para ajustar velocidad del molino

// -------------------------------------------------------------
// 3. MELODÍA EN MEMORIA FLASH (PROGMEM) - "Noche de Paz" (fragmento)
// -------------------------------------------------------------
// Definición de notas (frecuencia en Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440

const int melodia[] PROGMEM = {
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_B3, NOTE_C4, NOTE_C4, NOTE_G4
};

// Duraciones: 4 = negra, 2 = blanca, 8 = corchea
const byte duraciones[] PROGMEM = {
  4, 4, 4, 2,
  4, 4, 4, 2,
  2, 4, 2, 2, 4, 2
};

const int numNotas = sizeof(melodia) / sizeof(melodia[0]);

// -------------------------------------------------------------
// VARIABLES DE TEMPORIZACIÓN (millis)
// -------------------------------------------------------------
unsigned long tiempoFuego = 0;
unsigned long tiempoMotor = 0;
unsigned long tiempoMusica = 0;

int notaActual = 0;
bool notaSonando = false;
unsigned long duracionNotaMs = 0;

void setup() {
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinPot, INPUT);

  motorMolino.setSpeed(2); // Velocidad inicial base (2 RPM)
}

void loop() {
  unsigned long ahora = millis();

  // =============================================================
  // TAREA 1: Efecto Fuego (Actualización cada 50 ms)
  // =============================================================
  if (ahora - tiempoFuego >= 50) {
    tiempoFuego = ahora;
    analogWrite(pinLed1, random(90, 255));
    analogWrite(pinLed2, random(40, 170));
  }

  // =============================================================
  // TAREA 2: Giro del Molino (Regulado por Potenciómetro)
  // =============================================================
  // Lee el potenciómetro para variar el intervalo entre pasos (entre 10ms y 40ms)
  int valPot = analogRead(pinPot);
  int intervaloPaso = map(valPot, 0, 1023, 10, 40); 

  if (ahora - tiempoMotor >= intervaloPaso) {
    tiempoMotor = ahora;
    motorMolino.step(1); // Da 1 paso continuo sin bloquear el loop
  }

  // =============================================================
  // TAREA 3: Villancico en Zumbador (Lectura desde PROGMEM)
  // =============================================================
  if (!notaSonando) {
    // Leer frecuencia y duración desde la memoria Flash
    int frecuencia = pgm_read_word_near(melodia + notaActual);
    byte duracionDiv = pgm_read_byte_near(duraciones + notaActual);

    int duracionBase = 1200 / duracionDiv;
    tone(pinBuzzer, frecuencia, duracionBase);

    duracionNotaMs = duracionBase * 1.25; // 25% de silencio entre notas
    tiempoMusica = ahora;
    notaSonando = true;
  } else {
    // Transcurrido el tiempo de la nota, pasar a la siguiente
    if (ahora - tiempoMusica >= duracionNotaMs) {
      noTone(pinBuzzer);
      notaSonando = false;
      notaActual = (notaActual + 1) % numNotas; // Repetir al terminar
    }
  }
}