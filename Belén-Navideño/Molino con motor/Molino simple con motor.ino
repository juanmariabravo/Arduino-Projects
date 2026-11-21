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