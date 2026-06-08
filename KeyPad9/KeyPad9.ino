#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Pins
const int rows[] = {3, 4, 2};
const String rowsS[] = {"2", "0", "1"};
const int cols[] = {6, 7, 5};
const String colsS[] = {"2", "0", "1"};
int buzzerPin = A3;

// Letters
String letters[9] = {"ABCD", "EFGH", "IJKL", "MNOP", "QRS", "TUV", "WXYZ", "_", ""};

// Tracking Variables
int lastKey = -1; // -1 when the last key pressed was confirmed
int keyIndex[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
bool wasPressed[] = {false, false, false, false, false, false, false, false, false}; // Tracking to not count the same key twice

String text = "";


void setup() {
  lcd.begin(16, 2);
  lcd.print("Version 10");

  pinMode(buzzerPin, OUTPUT);

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
          /*
          Serial.print("Key pressed at row ");
          Serial.print(rowsS[r]);
          Serial.print(", column ");
          Serial.println(colsS[c]);
          */

          // LCD Print
          /*
          lcd.clear();
          lcd.print("Row: " + rowsS[r]);
          lcd.setCursor(0, 1);
          lcd.print("Colunm: " + colsS[c]);
          */
          tone(buzzerPin, 350, 100);
          //delay(100); // slow down output

          if(lastKey == toKeyNum(r, c)) { //if same key pressed increase index
            keyIndex[toKeyNum(r, c)]++;
          }
          else { // if not set index to 0
            keyIndex[toKeyNum(r, c)] = 0;
          }
          // Cehck if the last key is pressed then confirm letter and print
          if(toKeyNum(r, c) == 8 && lastKey != -1) {
            text += getKey(lastKey, keyIndex[lastKey]);
            printScreen(text);
          }
          else {
            printScreen(text + getKey(toKeyNum(r, c), keyIndex[toKeyNum(r, c)]));
            //lcd.print(getKey(toKeyNum(r, c), keyIndex[toKeyNum(r, c)]));
            Serial.print(getKey(toKeyNum(r, c), keyIndex[toKeyNum(r, c)]) + "\n");
          }
          // Many lines because of integers :(
          Serial.print("Key num: ");
          Serial.print(toKeyNum(r, c));
          Serial.print(" Rows & Cols: ");
          Serial.print(r);
          Serial.print(c);
          Serial.print("\n");

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

// pass true index
String getKey(int keyNum, int index) {
  String letterGroup = letters[keyNum];
  return letterGroup.substring(index % letterGroup.length(), index % letterGroup.length() + 1);
}

// For Pringting LCD
void printScreen(String text) {
  lcd.clear();
  if(text.length() <= 16) {
    lcd.print(text);
  }
  else {
    lcd.print(text.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(text.substring(16));
  }
}
