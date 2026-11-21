# Villancicos con buzzer

En esta parte del proyecto se implementará un sistema de reproducción de villancicos utilizando un buzzer, una biblioteca de 16 villancicos populares y un botón para gestionar la reproducción. 

## Explicación

El objetivo es que el Belén Navideño pueda reproducir melodías navideñas de manera secuencial cada vez que se pulse el botón, de manera que el Belén pueda permanecer en silencio hasta que se desee escuchar música. Además, se desea que la reproducción se detenga si se pulsa el botón mientras se está reproduciendo un villancico. La siguiente pulsación del botón reproducirá el siguiente villancico de la lista, permitiendo así un control sencillo y efectivo de la música en el Belén.

## Listado de Villancicos Buzzer

En este proyecto se proporciona una lista de 16 villancicos preparados para reproducir con el buzzer. Puede reproducirlos de manera independient con cada uno de los códigos proporcionados en la carpeta `Villancicos .ino`. A continuación se muestra la tabla con los detalles de cada villancico:

| Índice | Título | N vueltas | Duración | Ruta |
| --- | --- | --- | --- | --- |
| 0 | Din Don Dilin Din Dan | 1 vuelta | 40.23s | Villancicos .ino/Dindon_dilindindan.ino |
| 1 | Nunca suenan las campanas | 2 vueltas | 61.79s | Villancicos .ino/Nunca suenan las campanas.ino |
| 2 | No la debemos dormir la noche Santa | 1 vuelta | 60.79s | Villancicos .ino/upsala_no_la_debemos_dormir_s.ino |
| 3 | 25 de diciembre | 1 vuelta | 35.29s | Villancicos .ino/anonimo_25_de_diciembre.ino |
| 4 | Ya viene la vieja | 2 vueltas | 53.5s | Villancicos .ino/anonimo_ya_viene_la_vieja.ino |
| 5 | Suite Comercial Navideña | 1 vuelta, varias canciones |  167.34s | Villancicos .ino/Suite Comercial Navideña.ino |
| 6 | El tamborilero | 3 vueltas | 128.28s | Villancicos .ino/El tamborilero.ino |
| 7 | Jingle Bells | 1 vuelta | 48.0s | Villancicos .ino/Jingle_Bells_Pierpont.ino |
| 8 | Santa Claus Llegó a la ciudad | 1 vuelta | 46.84s | Villancicos .ino/Santa_Claus_Is_Coming_To_Town_one_voice_main.ino |
| 9 | Los peces en el río | 2 vueltas | 62.4s | Villancicos .ino/Los_peces_en_el_rio_one_voice_main.ino |
| 10 | Ay del chiquirritín | 2 vueltas | 42.2s | Villancicos .ino/anonimo_chiquirriquitin.ino |
| 11 | Oh Holy Night | 1 vuelta | 88.2s | Villancicos .ino/O_Holy_Night.ino |
| 12 | Campana sobre campana | 1 vuelta | 58.3s | Villancicos .ino/Campana_sobre_campana_one_voice_main.ino |  
| 13 | Noche de paz | 2 vueltas | 71.0s | Villancicos .ino/Noche de paz_one_voice_main.ino |
| 14 | We Wish You a Merry Christmas | 1 vuelta | 21.83s | Villancicos .ino/We_Wish_You_a_Merry_Christmas.ino |
| 15 | Arre Borriquito | 2 vueltas | 174.0s | Villancicos .ino/ARRE_BORRIQUITO_one_voice.ino |

> Todos los villancicos se han preparado a partir de fuentes, recursos y herramientas online y gratuitas, como las incluidos en el apartado final de [Referencias](#referencias). Se han adaptado para su reproducción con un buzzer en Arduino, utilizando la biblioteca `tone()` para generar los tonos correspondientes a cada nota musical.

## Reproducción del listado de villancicos con control de botón

Para la reproducción de los villancicos, se ha implementado un sistema de control mediante un botón con configuración `INPUT_PULLUP`, conectado al pin 2 de la placa Arduino. Cada vez que se pulsa el botón, se reproduce el siguiente villancico de la lista. Si se pulsa el botón mientras se está reproduciendo un villancico, la reproducción se detendrá y la próxima pulsación del botón reproducirá el siguiente villancico de la lista.

Para incluir todas las canciones en un único programa, se ha creado un archivo `VillancicosPlay.ino` que contiene la implementación de la reproducción secuencial de los 16 villancicos, gestionando el control del botón y la reproducción de los tonos correspondientes a cada villancico. Además, se han creado en el mismo directorio 16 archivos `.h` para poder importar todos los villancicos en un único programa, de manera que se pueda gestionar la reproducción de todos ellos de forma sencilla y organizada.

## Explicación del código

### Bucle principal
```cpp
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
```
Como se puede observar, el bucle principal del programa gestiona la reproducción de los villancicos y el control del botón. Si se pulsa el botón, se detiene la reproducción si se está reproduciendo un villancico, o se inicia la reproducción del siguiente villancico si no se está reproduciendo ninguno. Además, se comprueba si ha transcurrido el tiempo de duración de la nota actual y, en caso afirmativo, se detiene el tono y se pasa a la siguiente nota o al siguiente villancico si se ha llegado al final de la canción.

## Cómo cargar el programa en la placa con Arduino IDE

En Arduino IDE, abre [VillancicosPlay/VillancicosPlay.ino](VillancicosPlay/VillancicosPlay.ino). Esta carpeta ya contiene todas las melodías como archivos `.h` junto al boceto principal, por lo que no depende de subcarpetas ni de rutas externas.

> Esto es necesario porque Arduino IDE no permite importar archivos `.h` que estén en subcarpetas, por lo que se han incluido todos los villancicos en la misma carpeta que el archivo principal `VillancicosPlay.ino`.

### Control del botón

* Primera pulsación: comienza el villancico actual.
* Pulsación durante la reproducción: detiene la melodía. La siguiente pulsación reproducirá el siguiente villancico.
* Pulsación cuando hay silencio: reproduce el siguiente villancico.


## Referencias

- [Midi Editor](https://www.aisongmaker.io/es/midi-editor)

- [Villancicos en MIDI](https://choralmidisdigest.com/villancicos.htm)

- [Villancicos en MIDI](https://www.musicamidigratis.com/midis/142/infomidi.html)

- [Christmas Songs MIDI](https://freemidis.net/Christmas/)

- [Partituras Villancicos](https://www.camerataabulense.com/partituras-religiosas)

- [Otras canciones en MIDI](https://www.midiworld.com/files/)
