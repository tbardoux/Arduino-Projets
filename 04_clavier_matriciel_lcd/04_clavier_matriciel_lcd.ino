#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>  // Bibliothèque clavier matriciel

// Disposition des touches du clavier 4x4
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Pins du clavier : de digital 13 à 6 dans l'ordre
byte rowPins[ROWS] = {13, 12, 11, 10}; // 4 lignes
byte colPins[COLS] = {9, 8, 7, 6};     // 4 colonnes

// Initialisation du clavier et du LCD
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Appuyez...");  // Message d'accueil
}

void loop() {
  char key = keypad.getKey();  // Lecture de la touche appuyée

  if (key) {                   // Si une touche est détectée
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Touche :");
    lcd.setCursor(0, 1);       // Deuxième ligne
    lcd.print(key);            // Affiche la touche
  }
}