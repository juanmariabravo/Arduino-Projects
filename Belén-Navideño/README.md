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

La versión independiente `VillancicosPlay.ino` reproduce secuencialmente los 16 villancicos de la tabla. En esa versión el zumbador usa el pin 8 y el botón el pin 2 con `INPUT_PULLUP`; en el programa integrado el zumbador usa el pin 7 para no interferir con los pines del motor.

En Arduino IDE, abre [VillancicosPlay/VillancicosPlay.ino](VillancicosPlay/VillancicosPlay.ino). Esta carpeta ya contiene todas las melodías como archivos `.h` junto al boceto principal, por lo que no depende de subcarpetas ni de rutas externas.

* Primera pulsación: comienza el villancico actual.
* Pulsación durante la reproducción: detiene la melodía. La siguiente pulsación reproducirá el siguiente villancico.
* Pulsación cuando hay silencio: reproduce el siguiente villancico.

## Programa integrado

[BelenCompleto/BelenCompleto.ino](BelenCompleto/BelenCompleto.ino) combina el fuego, el motor y la reproducción secuencial de villancicos en un solo boceto. Las tareas se coordinan mediante `millis()` y no usan pausas largas, por lo que funcionan simultáneamente.

Este es el boceto recomendado para cargar en la placa Arduino UNO.

| Función | Conexión |
| --- | --- |
| Fuego | LEDs en los pines 3, 5 y 6 |
| Botón | Pin 2 a GND; usa `INPUT_PULLUP` |
| Zumbador | Pin 7 |
| Motor | Pines 8, 10, 9 y 11 |
| Velocidad del motor | Potenciómetro entre A0 y GND/VCC |

### Esquema de pines

| Componente | Pines UNO | Observaciones |
| --- | --- | --- |
| LEDs del fuego | 3, 5 y 6 | Pines PWM para variar el brillo. Utiliza resistencias adecuadas, por ejemplo de 220-330 ohmios |
| Botón | 2 y GND | Botón normalmente abierto. `INPUT_PULLUP` mantiene el pin 2 en HIGH y pulsa a LOW |
| Zumbador | 7 y GND | Pin positivo del zumbador pasivo o activo en 7 |
| Motor 28BYJ-48 | Entradas 1-4 del ULN2003 a 8, 10, 9 y 11 | Alimenta el módulo desde una fuente 5 V adecuada y conecta sus masas con GND |
| Potenciómetro | Señal en A0, extremos en 5 V y GND | Ajusta el intervalo entre pasos del motor |

El pin 8 se usa para el motor en este programa integrado. Por ello, el zumbador se ha cambiado del pin 8 al pin 7 para evitar que ambos componentes interfieran entre sí.

No hay que conectar el motor directamente a los pines de la placa: hay que usar el controlador ULN2003 y una alimentación externa si el consumo lo requiere. Siempre debe compartirse el GND entre la placa, el módulo del motor y la alimentación externa.

### Funcionamiento del sistema

El programa ejecuta estas operaciones en paralelo dentro de `loop()`:

* Cada 50 ms actualiza los tres LEDs del fuego con valores aleatorios de brillo.
* Lee continuamente A0 y calcula un intervalo de 10 a 40 ms para cada paso del motor. Al girar el potenciómetro cambia la velocidad de giro.
* Comprueba el botón con antirrebote y una duración de 35 ms.
* Si no hay reproducción y se pulsa el botón, comienza el villancico indicado por `currentSong`.
* Si se pulsa mientras suena un villancico, `stopSong()` detiene el zumbador y avanza `currentSong` al siguiente.
* Si se termina una melodía, el sistema queda en silencio y la siguiente pulsación inicia el siguiente villancico.
* Después del último villancico, la lista vuelve a comenzar desde el índice 0.

No se usan `delay()` largos en el programa integrado. `millis()` controla el fuego y la duración de las notas, mientras que `Stepper::step(1)` mueve el motor un paso cada vez. Así pueden ejecutarse las tres tareas sin que el zumbador bloquee el resto.

### Explicación del código completo

El código completo se encuentra en [BelenCompleto/BelenCompleto.ino](BelenCompleto/BelenCompleto.ino).

#### Dependencias e inicialización

* `<avr/pgmspace.h>` permite guardar las frecuencias y duraciones en la memoria Flash mediante `PROGMEM`, en lugar de consumir toda la RAM.
* `<Stepper.h>` proporciona la clase `Stepper` para controlar el motor 28BYJ-48 con el ULN2003.
* Los bloques `#define` temporales renombran `N`, `melody`, `dur`, `setup`, `loop` y `playSong` de cada villancico. Esto permite incluir los 16 archivos `.h` sin que se repliquen sus funciones o se ejecuten sus originales.
* `SONG_COUNT` indica el número de canciones. `currentSong` selecciona la canción y `currentNote` la nota actual.
* `playing` distingue entre reproducción activa y silencio.

#### Lectura de las melodías

Las funciones `getSongLength()`, `getFrequency()` y `getDuration()` usan `switch` para elegir los arrays almacenados en cada encabezado.

* `getSongLength()` devuelve el número de elementos de la canción.
* `getFrequency()` devuelve la frecuencia de la nota actual; el valor 0 representa un silencio.
* `getDuration()` devuelve la duración en milisegundos.
* `pgm_read_word()` lee cada valor desde PROGMEM.

`startNextNote()` inicia una frecuencia con `tone()`. Para un silencio llama a `noTone()`. En ambos casos guarda `millis()` en `noteStartTime` para pasar a la siguiente nota sin bloquear `loop()`.

#### Control del botón

`buttonPressed()` lee el botón y espera 35 ms antes de aceptar un cambio estable. Solo devuelve `true` al confirmar la transición de HIGH a LOW, es decir, al presionar el botón.

* `startSong()` vuelve a la primera nota y activa `playing`.
* `stopSong()` detiene el zumbador y avanza inmediatamente al siguiente índice.
* El bloque final de `loop()` avanza las notas y cambia al siguiente villancico cuando termina la actual.

#### Fuego y motor

`setup()` configura entradas y salidas y establece la velocidad base del motor.

En `loop()` se hace:

1. Leer el botón.
2. Actualizar el fuego cada 50 ms.
3. Leer A0 y calcular el intervalo del motor.
4. Ejecutar un paso del motor cuando vence ese intervalo.
5. Comprobar si ha terminado o debe avanzar la nota actual.

El uso de marcas de tiempo permite que las tareas compitan por poco tiempo de CPU sin ejecutar pausas generales que impidan reaccionar al botón.

### Canciones `.h`

Cada villancico integrado es un archivo `.h` situado junto al boceto principal:

```text
BelenCompleto/
├── BelenCompleto.ino
├── Dindon_dilindindan.h
├── Nunca_suenan_las_campanas.h
├── upsala_no_la_debemos_dormir_s.h
├── anonimo_25_de_diciembre.h
├── anonimo_ya_viene_la_vieja.h
├── Suite_Comercial_Navidena.h
├── El_tamborilero.h
├── Jingle_Bells_Pierpont.h
├── Santa_Claus_Is_Coming_To_Town_one_voice_main.h
├── Los_peces_en_el_rio_one_voice_main.h
├── anonimo_chiquirriquitin.h
├── O_Holy_Night.h
├── Campana_sobre_campana_one_voice_main.h
├── Noche_de_paz_one_voice_main.h
├── We_Wish_You_a_Merry_Christmas.h
└── ARRE_BORRIQUITO_one_voice.h
```

Cada `.h` contiene dos arrays `PROGMEM`: uno con frecuencias y otro con duraciones. La combinación de ambos reproduce una nota o silencio. Los archivos conservan los datos originales convertidos a encabezados para que Arduino IDE pueda encontrarlos desde el propio boceto.

No es necesario abrir ni cargar los archivos `.h` individualmente. Arduino los incluye mediante `#include "Nombre.h"` y los incorpora al compilar el `.ino`.

### Cargar el programa con Arduino IDE

1. Instala la biblioteca estándar **Stepper** si Arduino IDE no la incluye. Normalmente viene disponible en la instalación estándar.
2. Instala el soporte de placas Arduino AVR si aún no está instalado.
3. Abre [BelenCompleto/BelenCompleto.ino](BelenCompleto/BelenCompleto.ino) desde **Archivo → Abrir**. No abras el archivo desde una copia temporal sin guardar.
4. Comprueba que junto a él aparecen los 16 archivos `.h` indicados arriba.
5. Conecta el Arduino UNO por USB.
6. En **Herramientas → Placa**, selecciona **Arduino UNO**.
7. En **Herramientas → Puerto**, selecciona el puerto COM correspondiente.
8. Pulsa **Verificar** para compilar. Los encabezados deben resolverse como archivos locales.
9. Pulsa **Cargar** para grabar el programa.
10. Si hay error de memoria, revisa antes que no haya pegada una carpeta temporal o archivos antiguos duplicados. El programa carga los datos de las canciones en memoria Flash mediante `PROGMEM`.

Si Arduino IDE informa `No such file or directory` al buscar un `.h`, el boceto no está en la carpeta `BelenCompleto` o los archivos no están junto a `BelenCompleto.ino`. Cierra el boceto temporal, abre la ruta de este repositorio y vuelve a verificar.

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
