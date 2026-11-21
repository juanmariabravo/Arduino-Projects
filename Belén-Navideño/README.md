# Belén Navideño

El objetivo de este proyecto es crear elementos que se puedan emplear en un Belén Navideño con luces y movimiento utilizando Arduino. El Belén contará con figuras tradicionales como el Niño Jesús, María, San José, los Reyes Magos, los Pastores y algunos animales. A todo ello se le añadirán luces y movimiento para hacerlo más atractivo y realista.

Puedes ver una demostración del funcionamiento final abriendo el siguiente [vídeo (ábrelo con el navegador web)](Integ3_Fuego_Molino_y_Villancicos\demo.mp4).

## Objetivos

* Crear fuego parpadeante con LEDs.
* Crear un molino de viento que gire con un motor paso a paso.
* Implementar un sistema de sonido con un buzzer para reproducir canciones navideñas.

## Sistemas

La implementación de estos 3 sistemas (fuego, molino y sonido) se realizará primero de manera independiente, para entender bien su funcionamiento individual. Más adelante, se integrarán en un único programa de manera incremental, permitiendo el funcionamiento de todos los elementos de forma simultánea.

Para ello, se organiza este proyecto en 3 carpetas, una para cada sistema, y un archivo `README.md` que explica el funcionamiento de cada uno de ellos:
```
Belén Navideño
|-- README.md (este archivo)
|-- Fuego con LEDs
|-- Molino con motor
|-- Villancicos con buzzer
```

## Integración incremental de los sistemas

Para poder utilizar los tres sistemas de manera conjunta, se han creado tres integraciones que combinan los sistemas de manera incremental:

1. [Integración 1: Fuego y Molino](Integ1%20Fuego%20y%20Molino/README.md): fuego con LEDs y motor paso a paso.
2. [Integración 2: Fuego y Villancicos](Integ2_Fuego_y_Villancicos/README.md): fuego con LEDs y reproducción mediante buzzer y botón.
3. [Integración 3: Fuego, Molino y Villancicos](Integ3_Fuego_Molino_y_Villancicos/README.md): fuego con LEDs, motor paso a paso y reproducción mediante buzzer y botón.

El proyecto mantiene las siguientes carpetas:
```
Belén Navideño
|-- README.md (este archivo)
|-- Integ1 Fuego y Molino
|-- Integ2_Fuego_y_Villancicos
|-- Integ3_Fuego_Molino_y_Villancicos
```

Los tres sistemas cooperan dentro de un único `loop()` de Arduino. El fuego usa un temporizador de 50 ms, el motor solicita un paso cada 5 ms y el reproductor controla las notas con `millis()` y `tone()`. El botón tiene un antirrebote de 35 ms. De este modo no hay bloqueos largos ni hilos reales: las tareas se comprueban por turno y el resultado se percibe como funcionamiento concurrente.

## Posibles ampliaciones e ideas futuras (no implementadas en este proyecto)

* Implementar un reloj para que el Belén tenga un ciclo de día y noche, con luces que se enciendan y apaguen según la hora del día
* Implementar un sistema para que suenen campanas a determinadas horas.