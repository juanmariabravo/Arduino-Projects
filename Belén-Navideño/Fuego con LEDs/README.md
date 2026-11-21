# Fuego con LEDs

En este apartado del proyecto se implementará un sistema de fuego parpadeante utilizando LEDs. Este sistema funcionará de manera continua mientras el Belén esté encendido, simulando el fuego de una hoguera. 

## Explicación

Utilizaremos 3 LEDs para crear un diferentes efectos visuales que imiten las llamas del fuego, aunque en la práctica real se puede usar un solo LED para simular el efecto que más nos guste. El parpadeo de los LEDs se logrará mediante la modulación de la intensidad de cada LED utilizando PWM (Pulse Width Modulation) en Arduino.

## Componentes necesarios
* 3 LEDs de colores del fuego (rojo, naranja, amarillo...)
* 3 resistencias de 220 ohmios
* Cables de conexión
* Arduino Uno o similar

## Esquema de conexión

Conectaremos los LEDs a los pines digitales 3, 5 y 6 de Arduino a través de resistencias de 220 ohmios:

```
PIN 3 ----> Resistencia 220 ohmios ----> ÁNODO (patilla larga) ----> CÁTODO ----> GND
PIN 5 ----> Resistencia 220 ohmios ----> ÁNODO (patilla larga) ----> CÁTODO ----> GND
PIN 6 ----> Resistencia 220 ohmios ----> ÁNODO (patilla larga) ----> CÁTODO ----> GND
```

## Código de Arduino
A continuación, se muestra un ejemplo de código para implementar el efecto de fuego parpadeante con los LEDs:

```cpp
void loop() {
  // LED 1: Variación amplia de brillo para simular la llama principal
  analogWrite(ledPin1, random(100, 255));
  
  // LED 2: Mantener más bajo y con menos variación para simular el carbón/brasa
  analogWrite(ledPin2, random(40, 150));
  
  // LED 3: Destellos rápidos intermitentes
  analogWrite(ledPin3, random(120, 255));

  // Intervalo aleatorio corto entre cambios para un efecto dinámico
  delay(random(40, 110));
}
```

## Recomendaciones prácticas

En muchos belenes navideños, se utiliza un solo LED para simular el fuego, ya que el efecto visual puede ser igualmente atractivo y más sencillo de implementar.
Además, muchos artistas añaden cristales rotos alrededor del LED para crear un efecto de luz más difusa y realista, simulando el brillo de las llamas. Si alguna vez rompes un vaso por accidente, recógelo con cuidado y utilízalo en tu Belén;)