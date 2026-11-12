#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const int LED_PIN = 5;       // LED sur pin 5
const String CODE_SECRET = "1234"; // Code à taper

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String saisie = "";           // Stocke les touches tapées
bool ledAllumee = false;      // Etat de la LED
unsigned long tempAllumage;   // Mémorise l'heure d'allumage

void setup() {
  pinMode(LED_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Code : ");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    saisie += key;            // Ajoute la touche à la saisie
    lcd.setCursor(0, 0);
    lcd.print("Code : ");
    lcd.print(saisie);        // Affiche la saisie en cours

    // Quand 4 touches ont été tapées
    if (saisie.length() == 4) {
      if (saisie == CODE_SECRET) {  // Bon code
        digitalWrite(LED_PIN, HIGH);
        ledAllumee = true;
        tempAllumage = millis();    // Mémorise l'heure d'allumage
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Acces autorise !");
      } else {                      // Mauvais code
        digitalWrite(LED_PIN, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mauvais code !");
      }
      saisie = "";            // Remet la saisie à zéro
    }
  }

  // Eteint la LED après 5 secondes
  if (ledAllumee && millis() - tempAllumage >= 5000) {
    digitalWrite(LED_PIN, LOW);
    ledAllumee = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Code : ");     // Réaffiche l'invite
  }
}