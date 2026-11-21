# Integración 2: Fuego y villancicos

Esta integración combina el efecto continuo del fuego con la reproducción controlada por botón de 16 villancicos.

## Componentes

* 3 LEDs de fuego
* 3 resistencias de 220 ohmios
* Zumbador pasivo
* Pulsador
* Arduino Uno o similar
* Cables

## Conexiones

| Componente | Pin |
| --- | --- |
| LED 1 del fuego | PWM 3 |
| LED 2 del fuego | PWM 5 |
| LED 3 del fuego | PWM 6 |
| Zumbador pasivo | 7 |
| Botón a GND | 2 |

El botón utiliza `INPUT_PULLUP`, por lo que se conecta entre el pin 2 y GND. Cuando no se pulsa se lee como `HIGH`; al pulsarlo pasa a `LOW`. De este modo, el botón no necesita resistencia.

## Concurrencia entre fuego y música

El programa no ejecuta el fuego y la música en hilos separados. Los integra mediante comprobaciones no bloqueantes dentro del mismo `loop()`:

* El fuego consulta cada 50 ms si debe cambiar sus tres niveles PWM.
* La música calcula el instante de inicio de cada nota con `millis()` y cambia a la siguiente cuando vence su duración.
* El botón se lee y se antirrebota en cada iteración.
* El Arduino conserva el tiempo disponible para atender las tres tareas porque no usa `delay()` para el fuego ni para la secuencia de notas.

`tone()` controla el zumbador durante la duración indicada sin bloquear permanentemente el bucle. Esto permite que el fuego siga actualizándose mientras suena una nota.

### Dato curioso: posible parpadeo sincronizado con la música

En Arduino Uno, el LED conectado al pin PWM 3 puede parecer que parpadea al ritmo de las notas del zumbador. La causa probable es una interferencia entre temporizadores: `tone()` utiliza el temporizador asociado al zumbador y el pin 3 comparte recursos PWM con ese temporizador.

Esto puede hacer que el valor PWM del `FIRE_LED_1` se vea alterado por el cambio de frecuencia o duración de cada nota. Para evitarlo, se puede conectar ese LED al pin PWM 9 o 10 y cambiar `const uint8_t FIRE_LED_1 = 3;` por el pin elegido.

## Control del botón

`buttonPressed()` incorpora antirrebote de 35 ms:

* Primera pulsación: comienza el villancico indicado por `currentSong`.
* Pulsación durante la reproducción: detiene la nota y avanza al siguiente índice de canción.
* Nueva pulsación en silencio: empieza el siguiente villancico.

Al terminar una melodía, `currentSong` avanza cíclicamente entre las 16 canciones.

## Melodías

Las melodías están incluidas como tablas `PROGMEM` y se cargan desde los 16 archivos `.h` que están junto al boceto. Las canciones disponibles son:

1. Dindon dilindindan
2. Nunca suenan las campanas
3. Upsala no la debemos dormir
4. 25 de diciembre
5. Ya viene la vieja
6. Suite comercial navidena
7. El tamborilero
8. Jingle Bells
9. Santa Claus is Coming to Town
10. Los peces en el rio
11. Chiquirriquitin
12. O Holy Night
13. Campana sobre campana
14. Noche de paz
15. We Wish You a Merry Christmas
16. Arre Borriquito

## Estados de reproducción

Las variables principales son:

* `playing`: indica si hay una melodía activa.
* `currentSong`: selecciona una de las 16 canciones.
* `currentNote`: apunta a la nota actual.
* `currentDuration`: contiene la duración temporal de esa nota.
* `noteStartTime`: guarda cuándo comenzó la nota.

`startNextNote()` lee frecuencia y duración de las tablas, genera el tono y registra el instante inicial. Cuando vence `currentDuration`, `loop()` pasa a la siguiente nota.

## Funcionamiento

1. `setup()` configura el botón, el zumbador y los LEDs.
2. `loop()` actualiza el fuego cada 50 ms.
3. Se lee el botón con antirrebote.
4. Si `playing` es verdadero, se controla el cambio de notas.
5. Al finalizar todas las notas se para la reproducción y se selecciona la siguiente canción.

## Codigo

El programa completo se encuentra en [Integ2 Fuego y Villancicos.ino](./Integ2%20Fuego%20y%20Villancicos.ino). Los archivos de melodías deben permanecer en la misma carpeta.
