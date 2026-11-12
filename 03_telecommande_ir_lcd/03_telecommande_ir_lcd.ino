#include <IRremote.hpp>      // Bibliothèque télécommande IR
#include <Wire.h>            // Bibliothèque communication I2C
#include <LiquidCrystal_I2C.h> // Bibliothèque écran LCD

const int LED_PIN = 7;  // LED sur pin 7
const int IR_PIN = 6;   // Récepteur IR sur pin 6

// Initialisation du LCD : adresse I2C 0x27, 16 colonnes, 2 lignes
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED_PIN, OUTPUT); // Pin LED en sortie
  Serial.begin(9600);       // Démarrage du moniteur série
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK); // Démarrage du récepteur IR

  // Initialisation et message de démarrage sur le LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);      // Curseur en haut à gauche
  lcd.print("En attente...");
}

void loop() {
  // Si un signal IR est reçu
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData; // Lecture du code

    if (code == 0xEA15FF00) {       // Bouton +
      digitalWrite(LED_PIN, HIGH);  // Allume la LED
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED allumee");     // Affiche sur le LCD
    } else if (code == 0xF807FF00) { // Bouton -
      digitalWrite(LED_PIN, LOW);   // Eteint la LED
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED eteinte");     // Affiche sur le LCD
    }

    IrReceiver.resume(); // Prêt à recevoir le prochain signal
  }
}