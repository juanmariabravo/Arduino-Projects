int greenCarsPin = 13;
int yellowCarsPin = 12;
int redCarsPin = 11;
int greenPeoplePin = 10;
int redPeoplePin = 9;
int buttonPeoplePin = 2;
int buzzerPin = 7;

// Variables de tiempo
unsigned long tiempoInicioVerdeCoches = 0; // Controla los 20s automáticos
unsigned long tiempoUltimoPase = 0;        // Controla el cooldown del botón de 25s
const unsigned long tiempoAutoVerde = 20000; // 20 segundos automáticos
const unsigned long cooldown = 25000;        // 25 segundos de cooldown para el botón

void setup()
{
    Serial.begin(9600);
    pinMode(greenCarsPin, OUTPUT);
    pinMode(yellowCarsPin, OUTPUT);
    pinMode(redCarsPin, OUTPUT);
    pinMode(greenPeoplePin, OUTPUT);
    pinMode(redPeoplePin, OUTPUT);
    pinMode(buttonPeoplePin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);

    // Estado inicial: coches pasando
    vehiculosPasan();
    tiempoInicioVerdeCoches = millis();
}

void loop()
{
    unsigned long tiempoEnVerde = millis() - tiempoInicioVerdeCoches;
    unsigned long tiempoDesdePase = millis() - tiempoUltimoPase;
    bool cooldownListo = (tiempoDesdePase >= cooldown);
    //Serial.print("Cooldown:");
    //Serial.println(cooldown - tiempoDesdePase);
    // Caso 1: Alguien pulsa el botón y el cooldown ha llegado a 0
    if (digitalRead(buttonPeoplePin) == LOW && cooldownListo)
    {
        Serial.println("Botón pulsado: transición peatonal en 1s");
        delay(1000); // 1s
        cambiarASemaforoPeatones();
    }
    // Caso 2: Nadie pulsa, pero vencen los 20 segundos automáticos
    else if (tiempoEnVerde >= tiempoAutoVerde)
    {
        Serial.println("Paso automático por tiempo (20s)");
        cambiarASemaforoPeatones();
    }
}

void cambiarASemaforoPeatones()
{
    // 1. Aviso a vehículos (amarillo 3 s)
    vehiculosAviso();
    delay(3000);

    // Reinicia el contador de cooldown para el botón (25s)
    tiempoUltimoPase = millis();

    // 2. Peatones pasan (verde peatones y zumbador 10 s)
    peatonesPasan();
    delay(10000);

    // 3. Aviso a peatones (verde intermitente y pitidos 5 s)
    peatonesAviso();

    // 4. Volver a abrir el tráfico para los coches
    vehiculosPasan();
    
    // Reinicia el contador de los 20s automáticos para los coches
    tiempoInicioVerdeCoches = millis();
}

void vehiculosPasan() {
    digitalWrite(redCarsPin, LOW);
    digitalWrite(yellowCarsPin, LOW);
    digitalWrite(greenPeoplePin, LOW);
    noTone(buzzerPin);
    
    digitalWrite(greenCarsPin, HIGH);
    digitalWrite(redPeoplePin, HIGH);
}

void vehiculosAviso() {
    digitalWrite(greenCarsPin, LOW);
    digitalWrite(yellowCarsPin, HIGH);
}

void peatonesPasan() {
    digitalWrite(yellowCarsPin, LOW);
    digitalWrite(redCarsPin, HIGH);
    digitalWrite(redPeoplePin, LOW);
    digitalWrite(greenPeoplePin, HIGH);
    tone(buzzerPin, 294);
}

void peatonesAviso() {
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(greenPeoplePin, HIGH);
        tone(buzzerPin, 294);
        delay(500);
        digitalWrite(greenPeoplePin, LOW);
        noTone(buzzerPin);
        delay(500);
    }
}