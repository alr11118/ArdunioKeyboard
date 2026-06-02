#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int rows[] = {2, 3, 4};
const String rowsS[] = {"Yellow", "Blue", "Red"};
const int cols[] = {5, 6, 7};
const String colsS[] = {"Red", "Blue", "White"};

void setup() {
  lcd.begin(16, 2);
  lcd.print("Version 2");

  for (int r = 0; r < 3; r++) {
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], HIGH);
  }

  for (int c = 0; c < 3; c++) {
    pinMode(cols[c], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop() {
  for (int r = 0; r < 3; r++) {

    // Activate one row
    digitalWrite(rows[r], LOW);
    delay(5); // allow signal to settle

    // Check every column
    for (int c = 0; c < 3; c++) {
      if (digitalRead(cols[c]) == LOW) {
        Serial.print("Key pressed at row ");
        Serial.print(rowsS[r]);
        Serial.print(", column ");
        Serial.println(colsS[c]);

        // LCD Print
        lcd.clear();
        lcd.print(rowsS[r]);
        lcd.setCursor(0, 1);
        lcd.print(colsS[c]);

        delay(5000); // slow down output
      }
    }

    // Deactivate row
    digitalWrite(rows[r], HIGH);
  }
}