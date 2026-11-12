// Séance 1 : allumer une LED en fonction de la luminosité ambiante
// Composants : photorésistance (LDR) sur A0, LED sur la pin 2

const int pinLED = 2;
const int pinLDR = A0;

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinLDR, INPUT);

  Serial.begin(9600);
}

void loop() {
  int valeurLumiere = analogRead(pinLDR);

  Serial.print("Valeur LDR : ");
  Serial.println(valeurLumiere);

  if (valeurLumiere < 1025) {
    digitalWrite(pinLED, HIGH);
  }
  else {
    digitalWrite(pinLED, LOW);
  }

  delay(100);
}
