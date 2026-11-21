// Reproductor secuencial de villancicos
// Zumbador pasivo: pin 7
// Botón a GND: pin 2, con INPUT_PULLUP

#include <Arduino.h>
#include <avr/pgmspace.h>

// Incluye las canciones existentes sin ejecutar sus setup()/loop()/playSong().
#define setup setup_source0
#define loop loop_source0
#define playSong playSong0
#define N N0
#define melody melody0
#define dur dur0
#include "Dindon_dilindindan.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source1
#define loop loop_source1
#define playSong playSong1
#define N N1
#define melody melody1
#define dur dur1
#include "Nunca_suenan_las_campanas.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source2
#define loop loop_source2
#define playSong playSong2
#define N N2
#define melody melody2
#define dur dur2
#include "upsala_no_la_debemos_dormir_s.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source3
#define loop loop_source3
#define playSong playSong3
#define N N3
#define melody melody3
#define dur dur3
#include "anonimo_25_de_diciembre.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source4
#define loop loop_source4
#define playSong playSong4
#define N N4
#define melody melody4
#define dur dur4
#include "anonimo_ya_viene_la_vieja.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source5
#define loop loop_source5
#define playSong playSong5
#define N N5
#define melody melody5
#define dur dur5
#include "Suite_Comercial_Navidena.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source6
#define loop loop_source6
#define playSong playSong6
#define N N6
#define melody melody6
#define dur dur6
#include "El_tamborilero.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source7
#define loop loop_source7
#define playSong playSong7
#define N N7
#define melody melody7
#define dur dur7
#include "Jingle_Bells_Pierpont.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source8
#define loop loop_source8
#define playSong playSong8
#define N N8
#define melody melody8
#define dur dur8
#include "Santa_Claus_Is_Coming_To_Town_one_voice_main.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source9
#define loop loop_source9
#define playSong playSong9
#define N N9
#define melody melody9
#define dur dur9
#include "Los_peces_en_el_rio_one_voice_main.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source10
#define loop loop_source10
#define playSong playSong10
#define N N10
#define melody melody10
#define dur dur10
#include "anonimo_chiquirriquitin.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source11
#define loop loop_source11
#define playSong playSong11
#define N N11
#define melody melody11
#define dur dur11
#include "O_Holy_Night.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source12
#define loop loop_source12
#define playSong playSong12
#define N N12
#define melody melody12
#define dur dur12
#include "Campana_sobre_campana_one_voice_main.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source13
#define loop loop_source13
#define playSong playSong13
#define N N13
#define melody melody13
#define dur dur13
#include "Noche_de_paz_one_voice_main.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source14
#define loop loop_source14
#define playSong playSong14
#define N N14
#define melody melody14
#define dur dur14
#include "We_Wish_You_a_Merry_Christmas.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

#define setup setup_source15
#define loop loop_source15
#define playSong playSong15
#define N N15
#define melody melody15
#define dur dur15
#include "ARRE_BORRIQUITO_one_voice.h"
#undef dur
#undef melody
#undef N
#undef playSong
#undef loop
#undef setup

const uint8_t BUTTON_PIN = 2;
const uint8_t BUZZER_PIN = 7;
const uint8_t SONG_COUNT = 16;

uint8_t currentSong = 0;
uint16_t currentNote = 0;
uint16_t currentDuration = 0;
bool playing = false;

bool stableButtonState = HIGH;
bool lastButtonState = HIGH;
uint32_t lastDebounceTime = 0;

bool buttonPressed() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((uint32_t)(millis() - lastDebounceTime) >= 35 &&
      reading != stableButtonState) {
    stableButtonState = reading;
    if (stableButtonState == LOW) {
      lastButtonState = reading;
      return true;
    }
  }

  lastButtonState = reading;
  return false;
}

uint16_t getSongLength() {
  switch (currentSong) {
    case 0:  return N0;
    case 1:  return N1;
    case 2:  return N2;
    case 3:  return N3;
    case 4:  return N4;
    case 5:  return N5;
    case 6:  return N6;
    case 7:  return N7;
    case 8:  return N8;
    case 9:  return N9;
    case 10: return N10;
    case 11: return N11;
    case 12: return N12;
    case 13: return N13;
    case 14: return N14;
    default: return N15;
  }
}

uint16_t getFrequency() {
  switch (currentSong) {
    case 0:  return pgm_read_word(&melody0[currentNote]);
    case 1:  return pgm_read_word(&melody1[currentNote]);
    case 2:  return pgm_read_word(&melody2[currentNote]);
    case 3:  return pgm_read_word(&melody3[currentNote]);
    case 4:  return pgm_read_word(&melody4[currentNote]);
    case 5:  return pgm_read_word(&melody5[currentNote]);
    case 6:  return pgm_read_word(&melody6[currentNote]);
    case 7:  return pgm_read_word(&melody7[currentNote]);
    case 8:  return pgm_read_word(&melody8[currentNote]);
    case 9:  return pgm_read_word(&melody9[currentNote]);
    case 10: return pgm_read_word(&melody10[currentNote]);
    case 11: return pgm_read_word(&melody11[currentNote]);
    case 12: return pgm_read_word(&melody12[currentNote]);
    case 13: return pgm_read_word(&melody13[currentNote]);
    case 14: return pgm_read_word(&melody14[currentNote]);
    default: return pgm_read_word(&melody15[currentNote]);
  }
}

uint16_t getDuration() {
  switch (currentSong) {
    case 0:  return pgm_read_word(&dur0[currentNote]);
    case 1:  return pgm_read_word(&dur1[currentNote]);
    case 2:  return pgm_read_word(&dur2[currentNote]);
    case 3:  return pgm_read_word(&dur3[currentNote]);
    case 4:  return pgm_read_word(&dur4[currentNote]);
    case 5:  return pgm_read_word(&dur5[currentNote]);
    case 6:  return pgm_read_word(&dur6[currentNote]);
    case 7:  return pgm_read_word(&dur7[currentNote]);
    case 8:  return pgm_read_word(&dur8[currentNote]);
    case 9:  return pgm_read_word(&dur9[currentNote]);
    case 10: return pgm_read_word(&dur10[currentNote]);
    case 11: return pgm_read_word(&dur11[currentNote]);
    case 12: return pgm_read_word(&dur12[currentNote]);
    case 13: return pgm_read_word(&dur13[currentNote]);
    case 14: return pgm_read_word(&dur14[currentNote]);
    default: return pgm_read_word(&dur15[currentNote]);
  }
}

uint32_t noteStartTime = 0;

void startNextNote() {
  uint16_t frequency = getFrequency();
  currentDuration = getDuration();

  if (frequency != 0) {
    tone(BUZZER_PIN, frequency, (uint32_t)currentDuration * 90 / 100);
  } else {
    noTone(BUZZER_PIN);
  }

  noteStartTime = millis();
}

void startSong() {
  currentNote = 0;
  playing = true;
  startNextNote();
}

void stopSong() {
  noTone(BUZZER_PIN);
  playing = false;
  currentNote = 0;
  currentSong = (currentSong + 1) % SONG_COUNT;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void loop() {
  if (buttonPressed()) {
    if (playing) {
      stopSong();
    } else {
      startSong();
    }
  }

  if (!playing) {
    return;
  }

  if ((uint32_t)(millis() - noteStartTime) >= currentDuration) {
    noTone(BUZZER_PIN);
    currentNote++;

    if (currentNote >= getSongLength()) {
      playing = false;
      currentNote = 0;
      currentSong = (currentSong + 1) % SONG_COUNT;
    } else {
      startNextNote();
    }
  }
}