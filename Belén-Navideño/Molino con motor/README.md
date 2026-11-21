# Molino con motor

En este apartado del Belén Navideño se implementará un molino de viento que gire de manera continua mientras el Belén esté encendido. Para ello, se empleará un motor paso a paso (28BYJ-48) controlado por un driver ULN2003 y una placa Arduino.

## Explicación

El motor paso a paso 28BYJ-48 es un motor de corriente continua que se mueve en pasos discretos, lo que permite un control preciso de su posición y velocidad. Este motor se controla mediante un driver ULN2003, que actúa como un intermediario entre la placa Arduino y el motor, permitiendo manejar la corriente necesaria para su funcionamiento.

## Componentes necesarios

* Motor paso a paso 28BYJ-48
* Driver ULN2003
* Placa Arduino Uno o similar
* Cables de conexión

## Esquema de conexión

El motor paso a paso se conecta al driver ULN2003. Este driver tiene 4 pines de señal que se conectan a los pines digitales y 2 pines de alimentación que se conectan a la fuente de alimentación. En este caso, alimentaremos el motor con 5V desde la placa Arduino, aunque en la práctica se recomienda usar una fuente de alimentación externa para evitar sobrecargar la placa.

```
IN1 ----> Pin 8 de Arduino
IN2 ----> Pin 9 de Arduino
IN3 ----> Pin 10 de Arduino
IN4 ----> Pin 11 de Arduino
VCC ----> 5V de Arduino
GND ----> GND de Arduino
```

> No es necesario usar resistencias en este circuito porque el driver ULN2003 ya incluye resistencias internas para limitar la corriente que llega al motor.

## Código de Arduino

Para controlar el motor paso a paso, se utilizará la librería `Stepper` de Arduino. Esta librería facilita el control del motor, permitiendo definir el número de pasos por revolución y la velocidad de giro.

```cpp
#include <Stepper.h>

// Configuración del motor 
const int STEPS_PER_REV = 2048;  // Número de pasos (mini giros) por vuelta completa del motor
// Nota: En la secuencia típica del ULN2003 se intercambian pines 9 y 10 (8, 10, 9, 11)
Stepper motorMolino(STEPS_PER_REV, 8, 10, 9, 11);


void setup() {
  motorMolino.setSpeed(4); // Velocidad inicial base (4 RPM)
}

void loop() {
  motorMolino.step(1); // Da 1 paso continuo sin bloquear el loop
}
```

Este programa configura el motor para que gire a una velocidad de 4 revoluciones por minuto (RPM) y da un paso continuo en cada iteración del bucle `loop()`, lo que permite que el molino gire de manera constante mientras el Belén esté encendido. 

## Recomendaciones

Es recomendable ajustar la velocidad según las necesidades del proyecto y la apariencia deseada del molino. Se propone realizar una manualidad para construir un molino de viento que se pueda colocar en el Belén, utilizando materiales como cartón, madera o plástico. Además, se puede añadir iluminación al molino para hacerlo más atractivo y realista.

## Referencias

https://solectroshop.com/es/content/43-arduino-mas-avanzadas-funccionalidades-de-motores-paso-a-paso