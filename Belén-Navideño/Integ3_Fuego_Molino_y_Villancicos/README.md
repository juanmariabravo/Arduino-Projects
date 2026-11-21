# Integración 3: Fuego, molino y villancicos

Esta integración contiene el programa completo del Belén: fuego continuo, molino giratorio y reproducción de villancicos mediante botón y zumbador.

Puedes ver una demostración de la integración 3 en funcionamiento abriendo el siguiente [vídeo: demo.mp4](demo.mp4).

## Componentes

* 3 LEDs de fuego
* 3 resistencias de 220 ohmios
* Motor paso a paso 28BYJ-48
* Driver ULN2003
* Zumbador pasivo
* Pulsador normalmente abierto
* Arduino Uno o compatible
* Cables y alimentación adecuada

## Conexiones

| Elemento | Pin |
| --- | --- |
| LED 1 del fuego | PWM 3 |
| LED 2 del fuego | PWM 5 |
| LED 3 del fuego | PWM 6 |
| Zumbador pasivo | 7 |
| Pulsador | 2 |
| ULN2003 IN1-IN4 | 8, 9, 10 y 11 |

El pulsador usa `INPUT_PULLUP` y se conecta entre el pin 2 y GND. Los cátodos de los LEDs van a GND. Se recomienda una fuente externa para el motor.

## Coordinación de las tres tareas

El Arduino Uno no dispone de ejecución simultánea real de tareas independientes. Se usa concurrencia cooperativa basada en el bucle principal:

1. Se obtiene `now = millis()` una sola vez al comienzo de `loop()`.
2. El fuego se actualiza si han pasado 50 ms.
3. El motor recibe un paso si han pasado 5 ms.
4. El botón se lee y se antirrebota con 35 ms.
5. Si una canción está activa, se comprueba si debe terminar la nota actual.
6. `loop()` vuelve a comenzar y repite todas las comprobaciones.

Cada tarea conserva su propio instante o intervalo y ninguna usa `delay()` para esperar. El resultado aparente es que el fuego cambia, el motor avanza y la música sigue su secuencia al mismo tiempo.

## Fuego

Las tres salidas PWM reciben valores aleatorios cada 50 ms:

* LED 1: entre 100 y 254.
* LED 2: entre 40 y 149.
* LED 3: entre 120 y 254.

La diferencia de rangos crea una llama principal brillante, una brasa más tenue y destellos rápidos.

### Dato curioso: posible parpadeo sincronizado con la música

Como ocurría en la integración 2, el LED conectado al pin PWM 3 puede parecer que parpadea al ritmo de las notas del zumbador. Esto ocurre porque `tone()` utiliza internamente el temporizador asociado al zumbador, y ese temporizador también puede interferir con el PWM del pin 3.

## Molino

`Stepper` está configurado con 2048 pasos por revolución en los pines 8, 10, 9 y 11 y a 4 RPM. En cada intervalo de 5 ms se ejecuta `motorMolino.step(1)`.

Esta llamada forma parte de la tarea cooperativa del bucle; al finalizar el paso, el programa continúa con el botón y la reproducción musical.

## Reproducción musical

El programa incluye 16 villancicos almacenados en archivos `.h` con datos `PROGMEM`. El primer villancico está seleccionado al iniciar.

* Primera pulsación: inicia `currentSong`.
* Pulsación con música activa: detiene la melodía y avanza al siguiente villancico.
* Nueva pulsación en silencio: inicia el siguiente villancico.
* Al terminar una canción: vuelve a silencio y avanza `currentSong`.

Cada nota consulta su frecuencia y duración con `getFrequency()` y `getDuration()`. `tone()` suena durante el 90 % de la duración y la función principal cambia a la siguiente nota al vencer el tiempo registrado.

## Antirrebote

`buttonPressed()` requiere que el estado cambiado del botón permanezca estable durante al menos 35 ms antes de registrar una pulsación. Así se evita que el rebote mecánico genere varios cambios seguidos.

## Archivos necesarios

El boceto y todos los encabezados deben permanecer juntos:

* [Integ3 Fuego, Molino y Villancicos.ino](./Integ3%20Fuego,%20Molino%20y%20Villancicos.ino)
* Los 16 archivos `.h` contenidos en esta carpeta

Arduino IDE necesita que los encabezados estén en la misma carpeta que el archivo `.ino`.

## Resumen del flujo

1. `setup()` configura LEDs, motor, botón y zumbador.
2. `loop()` actualiza el fuego y el motor por sus temporizadores.
3. `buttonPressed()` detecta pulsaciones válidas.
4. `startNextNote()` reproduce cada nota del villancico seleccionado.
5. Todas las comprobaciones vuelven a empezar inmediatamente en la siguiente iteración.
