#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const int LED_PIN    = 5;
const int BUZZER_PIN = 4;

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

String saisie            = "";
String codeSecret        = "1234";  // Code modifiable
const String CODE_GARDIEN = "0000"; // Code gardien fixe
bool ledAllumee          = false;
bool modeChangement      = false;   // Mode changement de code actif
unsigned long tempAllumage;

// Son de succès : deux bips courts
void sonSucces() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
}

// Son d'erreur : un bip long
void sonErreur() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZER_PIN, LOW);
}

// Son de confirmation changement de code : trois bips
void sonChangement() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);  // Buzzer éteint au démarrage
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Code : ");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    saisie += key;

    // Affichage selon le mode
    if (modeChangement) {
      lcd.setCursor(0, 0);
      lcd.print("Nouveau code:   ");
      lcd.setCursor(0, 1);
      lcd.print(saisie);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Code : ");
      lcd.print(saisie);
    }

    if (saisie.length() == 4) {

      // --- MODE CHANGEMENT DE CODE ---
      if (modeChangement) {
        codeSecret = saisie;       // Enregistre le nouveau code
        modeChangement = false;
        sonChangement();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Code modifie !");
        lcd.setCursor(0, 1);
        lcd.print("-> " + codeSecret);
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Code : ");

      // --- CODE GARDIEN ---
      } else if (saisie == CODE_GARDIEN) {
        modeChangement = true;     // Active le mode changement
        sonSucces();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mode gardien");
        lcd.setCursor(0, 1);
        lcd.print("Nouveau code:");

      // --- BON CODE ---
      } else if (saisie == codeSecret) {
        digitalWrite(LED_PIN, HIGH);
        ledAllumee = true;
        tempAllumage = millis();
        sonSucces();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Acces autorise");

      // --- MAUVAIS CODE ---
      } else {
        digitalWrite(LED_PIN, LOW);
        sonErreur();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mauvais code !");
      }

      saisie = "";  // Remet la saisie à zéro
    }
  }

  // Eteint la LED après 5 secondes
  if (ledAllumee && millis() - tempAllumage >= 5000) {
    digitalWrite(LED_PIN, LOW);
    ledAllumee = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Code : ");
  }
}
