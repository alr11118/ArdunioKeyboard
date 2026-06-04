#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// 3x3 keypad wiring (matrix)
const int rows[] = {3, 4, 2};   // row pins (outputs)
const int cols[] = {6, 7, 5};   // column pins (inputs)

// T9 LETTERS
// Each key (0–8) has a "string" of possible letters
const char* keys[9] = {
  "ABC",   // key 0 (row 0 col 0)
  "DEF",   // key 1
  "GHI",   // key 2
  "JKL",   // key 3
  "MNO",   // key 4
  "PQRS",  // key 5
  "TUV",   // key 6
  "WXYZ",  // key 7
  "_"      // key 8 (space)
};

// VARIABLES 

int lastKey = -1;          // which key was last pressed (0–8)
int letterIndex = 0;       // which letter in that key we are cycling through

String output = "";        // final typed text shown on LCD

unsigned long lastPressTime = 0; // time of last button press

const int cycleDelay = 500; // ms wait before "locking in" a letter


void setup() {
  lcd.begin(16, 2);        // initialize LCD size (16 columns, 2 rows)
  lcd.print("Version 5");

  // SETUP ROWS (OUTPUTS)
  for (int r = 0; r < 3; r++) {
    pinMode(rows[r], OUTPUT);
    digitalWrite(rows[r], HIGH); // HIGH = inactive row
  }

  // SETUP COLUMNS (INPUTS)
  for (int c = 0; c < 3; c++) {
    pinMode(cols[c], INPUT_PULLUP);
    // INPUT_PULLUP means:
    // - not pressed = HIGH
    // - pressed = LOW (because row pulls it down)
  }

  Serial.begin(9600); // debugging output
}


// Convert (row, col) → single number (0–8)
// Example:
// (0,0)=0, (0,1)=1 ... (2,2)=8
int getKeyIndex(int r, int c) {
  return r * 3 + c;
}


// FINALIZE A LETTER (commit it to output string)
void commitLetter() {

  if (lastKey != -1) {

    const char* group = keys[lastKey]; // get letter group like "ABC"

    if (strlen(group) == 1) {
      // special case: space key
      output += group[0];
    } 
    else {
      // normal case: pick letter from group
      int len = strlen(group);
      output += group[letterIndex % len];
    }

    // update LCD display
    printScreen(output);
  }

  // reset selection state
  lastKey = -1;
  letterIndex = 0;
}


// MAIN LOOP: scan keypad constantly
void loop() {
  // scan each row one at a time
  for (int r = 0; r < 3; r++) {

    digitalWrite(rows[r], LOW); // activate this row
    delay(3); // small delay so signal stabilizes

    // check all columns in this row
    for (int c = 0; c < 3; c++) {

      if (digitalRead(cols[c]) == LOW) {
        // button is pressed

        int key = getKeyIndex(r, c); // convert to 0–8 key index

        // CASE 1: same key pressed again quickly
        // → cycle letters (A → B → C ...)
        if (key == lastKey && millis() - lastPressTime < cycleDelay) {
          letterIndex++;
        }
        // CASE 2: new key pressed
        // → commit previous letter first
        else {
          commitLetter();   // save previous letter
          lastKey = key;    // store new key
          letterIndex = 0;  // start at first letter
        }
        // update timing
        lastPressTime = millis();
      }
    }

    digitalWrite(rows[r], HIGH); // deactivate row
  }

  // If user stops pressing for a while:
  // → finalize the letter automatically
  if (lastKey != -1 && millis() - lastPressTime > cycleDelay) {
    commitLetter();
  }
}

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