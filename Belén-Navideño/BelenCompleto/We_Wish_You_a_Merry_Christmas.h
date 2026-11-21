// Generado con Partitura → Arduino
// 55 notas/silencios · duración ≈ 21.8 s · 132 BPM
#include <avr/pgmspace.h>
#if !defined(PROGMEM)
  #define PROGMEM
  #define pgm_read_word(p) (*(p))
#endif

#define BUZZER 8
const uint16_t N = 55;

// Frecuencias en Hz (0 = silencio)
const uint16_t melody[] PROGMEM = {
  294, 392, 392, 440, 392, 370, 330, 330, 330, 440, 440, 494, 
  440, 392, 370, 294, 294, 370, 494, 494, 523, 494, 440, 392, 
  330, 294, 294, 330, 440, 370, 392, 294, 392, 392, 392, 370, 
  370, 392, 370, 330, 294, 440, 494, 440, 440, 392, 392, 587, 
  294, 294, 294, 330, 440, 370, 392
};
// Duraciones en ms
const uint16_t dur[] PROGMEM = {
  455, 455, 227, 227, 227, 227, 455, 455, 455, 455, 227, 227, 
  227, 227, 455, 455, 455, 455, 455, 227, 227, 227, 227, 455, 
  455, 227, 227, 455, 455, 455, 455, 455, 455, 455, 455, 909, 
  455, 455, 455, 455, 909, 455, 455, 227, 227, 227, 227, 455, 
  455, 227, 227, 455, 455, 455, 909
};

void playSong() {
  for (uint16_t i = 0; i < N; i++) {
    uint16_t f = pgm_read_word(&melody[i]);
    uint16_t d = pgm_read_word(&dur[i]);
    if (f) tone(BUZZER, f, (uint32_t)d * 90 / 100);
    delay(d);
    noTone(BUZZER);
  }
}

void setup() {
  pinMode(BUZZER, OUTPUT);
  playSong();
}

void loop() {
}
