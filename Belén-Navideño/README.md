# Belén Navideño

El objetivo de este proyecto es crear elementos que se puedan emplear en un Belén Navideño con luces y movimiento utilizando Arduino. El Belén contará con figuras tradicionales como el Niño Jesús, María, San José, los Reyes Magos, los Pastores y algunos animales. A todo ello se le añadirán luces y movimiento para hacerlo más atractivo y realista.

## Objetivos

* Crear fuego parpadeante con LEDs o con la matriz de LEDs WS2812B.
* Crear un molino de viento que gire con un motor paso a paso.
* Implementar un sistema de sonido con un buzzer para reproducir canciones navideñas.

El objetivo principal de este proyecto es la implementación de 3 sistemas independientes que puedan funcionar de manera autónoma utilizando la misma placa Arduino. Estos 3 sistemas son:
1. Sistema de fuego parpadeante con LEDs: funcionará siempre que el Belén permanezca encendido, simulando el fuego de una hoguera
2. Sistema de molino de viento con motor paso a paso: el molino girará de manera continua mientras el Belén esté encendido
3. Sistema de sonido con buzzer para reproducir villancicos: reproducirá melodías navideñas únicamente cuando se pulse un botón, de manera que el Belén pueda permanecer en silencio hasta que se desee escuchar música. Este botón permitirá reproducir un villancico diferente cada vez que se pulse, de manera secuencial. Si se pulsa el botón mientras se está reproduciendo un villancico, la reproducción se detendrá y la próxima pulsación del botón reproducirá el siguiente villancico de la lista.

## Listado de Villancicos Buzzer

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

## Posibles ampliaciones e ideas futuras

* Implementar un reloj para que el Belén tenga un ciclo de día y noche, con luces que se enciendan y apaguen según la hora del día
* Implementar un sistema para que suenen campanas a determinadas horas.

## Tools and Sources

- [Midi Editor](https://www.aisongmaker.io/es/midi-editor)

- [Villancicos en MIDI](https://choralmidisdigest.com/villancicos.htm)

- [Villancicos en MIDI](https://www.musicamidigratis.com/midis/142/infomidi.html)

- [Christmas Songs MIDI](https://freemidis.net/Christmas/)

- [Partituras Villancicos](https://www.camerataabulense.com/partituras-religiosas)

- [Otras canciones en MIDI](https://www.midiworld.com/files/)
