// Séance 2 : piloter un servomoteur SG90 avec un potentiomètre
// Composants : potentiomètre sur A1, servomoteur sur la pin 6

#include <Servo.h>

Servo monServo;

void setup() {
  monServo.attach(6);
}

void loop() {
  int valeurPot = analogRead(A1);
  int angle = map(valeurPot, 0, 1023, 0, 180);  // 0-1023 -> 0-180°
  monServo.write(angle);
  delay(15);
}
