#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Pins
const int rows[] = {2, 3, 4};
const String rowsS[] = {"2", "0", "1"};
const int cols[] = {5, 6, 7};
const String colsS[] = {"2", "0", "1"};

// Letters
String letters[9] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ", "_"};

// Tracking Variables
int keyIndex = 0;
int lastKey = -1; // -1 when the last key pressed was confirmed
bool wasPressed[] = {false, false, false, false, false, false, false, false, false}; // Tracking to not count the same key twice


void setup() {
  lcd.begin(16, 2);
  lcd.print("Version 8");

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
    delay(1); // allow signal to settle

    // Check every column
    for (int c = 0; c < 3; c++) {
      if (digitalRead(cols[c]) == LOW) {
        // Check if key was pressed before
        if(wasPressed[toKeyNum(r, c)] == false) {
          // Logging
          Serial.print("Key pressed at row ");
          Serial.print(rowsS[r]);
          Serial.print(", column ");
          Serial.println(colsS[c]);

          // LCD Print
          lcd.clear();
          lcd.print("Row: " + rowsS[r]);
          lcd.setCursor(0, 1);
          lcd.print("Colunm: " + colsS[c]);

          delay(100); // slow down output

          if(lastKey == toKeyNum(r, c)) { //if same key pressed increase index
            keyIndex++;
          }
          else { // if not set index to 0
            keyIndex = 0;
          }
          Serial.print(getKey(toKeyNum(r, c)));
          Serial.print("Key num: " + toKeyNum(r, c) + " Rows & Cols: " + r + c + "\n");

          lastKey = toKeyNum(r, c);
        }
        // If the same key is still pressed dont do amything
        wasPressed[toKeyNum(r, c)] = true;
      }
      else { // Key is not pressed
        wasPressed[toKeyNum(r, c)] = false;
      }
    }
    // Deactivate row
    digitalWrite(rows[r], HIGH);
  }
}

// Helper for tracking
int toKeyNum(int row, int col) {
  return (3*row) + col;
}

String getKey(int keyNum) {
  return letters[keyNum].substring(keyIndex, keyIndex + 1) + "\n";
}
