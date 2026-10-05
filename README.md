### Arduino Projects - by Juan María Bravo

Este repositorio contiene diversos proyectos diferentes categorías realizados con un kit de Arduino. Podrás explorar todos ellos y entender el funcionamiento paso a paso.
Cada proyecto contiene documentación sobre la la preparación , la configuración, el desarrollo y una demostración del resultado final.

Si te gusta la electrónica y la programación, este repositorio es perfecto para ti. ¡Diviértete explorando y aprendiendo!

De momento puedes encontrar los siguientes proyectos:

| Proyecto | Tipo | Descripción | Dificultad | Estado |
|----------|------|-------------|------------|--------|
| [Semáforo](./Semáforo) | Control | Controla un semáforo utilizando Arduino y LEDs. | Fácil | En progreso |
| [Cerradura inteligente](./Cerradura-inteligente) | Seguridad | Sistema de acceso con doble factor de autenticación (RFID + PIN). | Media | En progreso |
| [Alarma antirrobo](./Alarma-antirrobo) | Seguridad | Sistema de alarma volumétrica y perimetral con sensores y zumbador. | Media | En progreso |
| [Detector de incendios](./Detector-incendios) | Seguridad | Sistema de detección y alarma de incendios con sensor de llama. | Media | En progreso |
| [Estación meteorológica](./Estación-meteorológica) | Domótica | Mide temperatura, humedad y luz ambiental, mostrando los datos en una pantalla LCD. | Media | En progreso |
| [Cierre automático de ventanas](./Cierre-automático-ventanas) | Domótica | Sistema que cierra automáticamente una ventana al detectar lluvia. | Media | En progreso |
| [Reloj despertador digital](./Reloj-despertador-digital) | Domótica | Reloj con alarma programable y visualización en display de 7 segmentos. | Media | En progreso |
| [Persiana domótica fotosensible](./Persiana-domótica-fotosensible) | Domótica | Controla la apertura y cierre de una persiana según la luz ambiental. | Media | En progreso |
| [Luz de lectura crepuscular inteligente](./Luz-lectura-crepuscular-inteligente) | Domótica | Iluminación automática y regulable según la luz ambiental. | Media | En progreso |
| [Minijuegos retro en matriz LED 8x8](./Minijuegos-retro-matriz-LED-8x8) | Ocio | Juegos clásicos como Snake y Pong en una matriz LED. | Media | En progreso |
| [Juego de memoria acústico-visual](./Juego-memoria-acústico-visual) | Ocio | Juego tipo "Simon Dice" con LED RGB y zumbador. | Media | En progreso |
| [Control robótico Pan & Tilt de cámara](./Control-robótico-Pan-Tilt-cámara) | Ocio | Controla la posición de una cámara o puntero láser con servomotores y joystick. | Media | En progreso |
| [Tacómetro / Contador óptico](./Tacómetro-Contador-óptico) | Instrumentación | Mide revoluciones por minuto utilizando un sensor óptico y muestra los datos en pantalla. | Media | En progreso |
| [Termostato digital con histéresis](./Termostato-digital-histéresis) | Instrumentación | Controla la temperatura de una carga térmica mediante un sensor y un relé. | Media | En progreso |
| [Control de riego automático](./Control-riego-automático) | Domótica | Sistema de riego que se activa según la humedad del suelo y la programación horaria. | Media | En progreso |

## Detalle de los proyectos

### Seguridad y Control de Acceso

* **Cerradura inteligente con doble factor de autenticación (RFID + PIN)**: Sistema de acceso donde el usuario pasa la tarjeta RFID y luego introduce un código de 4 dígitos en el teclado matricial. Si es correcto, un servomotor abre el cerrojo, el LED RGB se pone en verde y la pantalla LCD muestra un mensaje de bienvenida; si falla, suena el zumbador y el LED se ilumina en rojo.


* **Alarma antirrobo volumétrica y perimetral**: Utiliza el sensor de inclinación SW-520D para detectar vibraciones o aperturas no autorizadas y el módulo de sonido para detectar ruidos fuertes. Al dispararse, activa el relé (encendiendo una luz de potencia) y hace sonar una sirena modulada con el zumbador. Se desarma con el mando a distancia IR o un llavero RFID.


* **Detector y alarma de incendios**: Emplea el fotodiodo sensor de llama YG1006 para detectar fuego de forma instantánea. Al detectar radiación infrarroja, activa una señal acústica en el zumbador, muestra una advertencia en el display de 4 dígitos y conmuta el relé para desconectar una línea eléctrica o activar un extractor.


### Domótica y Automatización del Hogar

* **Estación meteorológica doméstica**: Lee datos ambientales de temperatura y humedad con el sensor DHT11 y la luz ambiental con la fotorresistencia LDR. Muestra los valores alternados en la pantalla LCD 16x2 mediante el bus I2C y, si la temperatura supera un umbral, enciende un ventilador conectado al módulo de relé.


* **Cierre automático de ventanas por lluvia**: El sensor resistivo de gotas detecta las primeras precipitaciones. Mediante el servomotor SG90 o el motor paso a paso 28BYJ-48 con su placa ULN2003, acciona un brazo mecánico para cerrar una compuerta o ventana simulada, mostrando el estado en la LCD.


* **Reloj despertador digital programable**: Emplea el módulo RTC DS1302 para mantener la fecha y hora reales de manera continua. La hora se visualiza en el display de 7 segmentos de 4 dígitos (con los dos puntos parpadeando a 1 Hz). Se pueden ajustar las alarmas mediante el teclado matricial 4x4 o el mando a distancia IR, sonando con el zumbador.


* **Persiana domótica fotosensible**: Utiliza la LDR para medir el nivel de luz solar y el motor paso a paso 28BYJ-48 para subir o bajar la persiana de forma gradual según la iluminación exterior o según órdenes recibidas desde el mando IR.


* **Luz de lectura crepuscular inteligente**: Con el transistor y la LDR, enciende automáticamente iluminación tenue cuando cae la noche. Con el potenciómetro o el mando IR se calibra la sensibilidad lumínica o el color del LED RGB.


### Ocio, Juegos e Interfaces Interactivas

* **Minijuegos retro en matriz LED 8x8**:
* **Snake (La serpiente)**: Controla el movimiento de la serpiente utilizando el joystick analógico de 2 ejes, generando comida aleatoria en la matriz de puntos y emitiendo pitidos con el zumbador al comer o chocar.


* **Pong de un jugador**: Mueve la pala en la fila inferior con el potenciómetro analógico mientras una bola rebota por los bordes de la matriz 8x8.


* **Juego de memoria acústico-visual (tipo *Simon Dice*)**: El sistema genera una secuencia de colores con el LED RGB y tonos en el zumbador. El jugador debe replicar la combinación exacta pulsando los botones táctiles del teclado matricial 4x4 o los pulsadores de la protoboard, mostrando la puntuación en el display de 7 segmentos.


* **Control robótico Pan & Tilt de cámara con joystick**: Monta los dos servomotores SG90 en configuración horizontal (paneo) y vertical (inclinación) para posicionar un soporte o puntero láser controlándolo en tiempo real con los ejes X e Y del joystick.


### Instrumentación y Medida

* **Tacómetro / Contador óptico**: Utiliza el LED negro receptor IR y un LED emisor para crear una barrera óptica; al ser interrumpida por las aspas de un ventilador o una rueda ranurada, cuenta revoluciones por minuto y las proyecta en la pantalla LCD 16x2 o en el display de 4 dígitos.


* **Termostato digital con histéresis**: Emplea el sensor de temperatura analógico TO-92 (LM35) para medir la temperatura con precisión decimal y regular el encendido/apagado de una carga térmica mediante el módulo de relé, fijando los límites deseados con el teclado 4x4.