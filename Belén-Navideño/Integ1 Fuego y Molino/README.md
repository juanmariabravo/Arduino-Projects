# Integración 1: Fuego y molino

Esta integración combina el fuego parpadeante y el giro continuo del molino.

## Componentes necesarios

* 3 LEDs del color del fuego (rojo, naranja o amarillo)
* 3 resistencias de 220 ohmios
* Motor paso a paso 28BYJ-48
* Driver ULN2003
* Arduino Uno o similar
* Cables y fuente de alimentación adecuada

## Conexiones

| Elemento | Pines |
| --- | --- |
| LEDs del fuego | PWM 3, 5 y 6, mediante resistencias de 220 ohmios |
| Entradas del ULN2003 IN1-IN4 | Pines digitales 8, 9, 10 y 11 |

Los cátodos de los LEDs se conectan a GND. Las alimentaciones del ULN2003 se conectan a 5 V y GND (sin resistencia). El motor se conecta al conector del driver. Para evitar sobrecargar el Arduino, se recomienda una fuente externa adecuada para el motor, aunque el motor puede funcionar con la alimentación del Arduino.

## Cómo trabajan juntos

El Arduino ejecuta una sola tarea principal. El programa simula la concurrencia separando las comprobaciones temporales en `loop()`:

* `fireLastUpdate` registra la última actualización del fuego.
* Si han pasado al menos 50 ms, se generan tres valores aleatorios y se escriben con `analogWrite()`.
* `motorLastStep` registra la última orden al motor.
* Si han pasado al menos 5 ms, se ejecuta `motorMolino.step(1)`.

La comprobación se realiza con restas sin signo:

```cpp
uint32_t now = millis();
(uint32_t)(now - fireLastUpdate) >= 50
(uint32_t)(now - motorLastStep) >= 5
```

Esta forma también controla correctamente el desbordamiento natural del contador `millis()` después de varios días de funcionamiento.

No existen hilos ni tareas en paralelo. Cada iteración comprueba primero el fuego y después el motor. El hecho de no usar `delay()` para el parpadeo permite que el bucle siga observando el motor con regularidad.

Al llamar a `motorMolino.step(1)`, la biblioteca `Stepper` ejecuta el movimiento de ese paso antes de devolver el control a `loop()`.

## Configuración del motor

```cpp
const int MOTOR_STEPS_PER_REV = 2048;
Stepper motorMolino(MOTOR_STEPS_PER_REV, 8, 10, 9, 11);
motorMolino.setSpeed(4);
```

La velocidad se configura a 4 RPM, mientras que el bucle solicita un paso cada 5 ms.

## Funcionamiento

1. `setup()` configura los pines PWM y fija el motor a 4 RPM.
2. `loop()` obtiene una sola lectura del tiempo.
3. Cuando vencen 50 ms, cambian los valores PWM del fuego.
4. Cuando vencen 5 ms, se envía un paso al motor.
5. Las dos comprobaciones se repiten durante toda la ejecución.

## Codigo

El programa completo se encuentra en [Integ1 Fuego y Molino.ino](./Integ1%20Fuego%20y%20Molino.ino).
