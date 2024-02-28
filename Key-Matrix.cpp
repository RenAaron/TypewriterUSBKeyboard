#include <Keyboard.h>

char A[12] = { '\t', '2', '3', '4', '5', '6', '7', '8', '9', '0', '<', '%' };
char B[12] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '@', 'x' };
char C[12] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '$', '&', 'x' };
char D[12] = { 'x', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '?', '.', '^', '-' };

int k[12] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16 };

char target[12];

#define row_A A0
#define row_B A1
#define row_C A2
//#define row_D A3


void setup() {

  delay(5000);

  Serial.begin(9600);

  pinMode(row_A, OUTPUT);
  pinMode(row_B, OUTPUT);
  pinMode(row_C, OUTPUT);
  //pinMode(row_D, OUTPUT);

  pinMode(2, INPUT_PULLUP);   // 1 GOOD
  pinMode(3, INPUT_PULLUP);   // 2 GOOD
  pinMode(4, INPUT_PULLUP);   // 3 GOOD
  pinMode(5, INPUT_PULLUP);   // 4 GOOD
  pinMode(6, INPUT_PULLUP);   // 5 GOOD
  pinMode(7, INPUT_PULLUP);   // 6 GOOD
  pinMode(8, INPUT_PULLUP);   // 7 GOOD
  pinMode(9, INPUT_PULLUP);   // 8 GOOD
  pinMode(10, INPUT_PULLUP);  // 9 GOOD
  pinMode(14, INPUT_PULLUP);  // 10 GOOD
  pinMode(15, INPUT_PULLUP);  // 11 GOOD
  pinMode(16, INPUT_PULLUP);  // 12 GOOD

  digitalWrite(row_A, HIGH);
  digitalWrite(row_B, HIGH);
  digitalWrite(row_C, HIGH);
  //digitalWrite(row_D, HIGH);
}

void keyPress(char c, bool down) {
  if (down) {
    // Serial.println(c);
    Keyboard.press(c);
  } else {
    //   Serial.println("up");
    Keyboard.release(c);
  }
}



void keyAction(char c, bool down) {
  if (isAlpha(c) || isDigit(c)) {  // alphanumeric
    keyPress(c, down);
  } else {
    switch (c) {
      case '\t':  // TAB
        keyPress(KEY_TAB, down);
        break;

      case '<':  // BACKSPACE
        keyPress(KEY_BACKSPACE, down);
        break;

      case '.':  // PERIOD KEY
        keyPress(0xBF, down);
        break;

      case '%':  // WINDOWS KEY
        keyPress(KEY_LEFT_GUI, down);
        break;

      case '#':  // ESCAPE
        keyPress(0xB1, down);
        break;

      case '$':  // SHIFT
        keyPress(0xE1, down);
        break;

      case '&':  // ENTER
        keyPress(0xB0, down);
        break;

      case '@':  // CAPS
        keyPress(0xC1, down);
        break;

      case '?':  // CTRL
        keyPress(0xE0, down);
        break;

      case '^':  // ALT
        keyPress(0x82, down);
        break;

      case '-':  // SPACE
        keyPress(0x20, down);
        break;
    }
  }
}

void assumeChars(char targ[], char assumer[]) {
  for (int i = 0; i < 12; i++) {
    targ[i] = assumer[i];
  }
}

String printCharArray(char charArray[]) {
  String rv = "";
  for (int i = 0; i < 12; i++) {
    rv += charArray[i];
  }

  return rv;
}

void scanStrokes() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(k[i]) == LOW) {
      keyAction(target[i], true);
    } else {
      keyAction(target[i], false);
    }
  }
}

void loop() {

  // digitalWrite(row_A, LOW);
  // Serial.print((String) (digitalRead(k[0])) + (String) (digitalRead(k[1])) + (String) (digitalRead(k[2])) + (String) (digitalRead(k[3])));
  // digitalWrite(row_A, HIGH);

  // Serial.print(" - ");

  // digitalWrite(row_B, LOW);
  // Serial.print((String) (digitalRead(k[0])) + (String) (digitalRead(k[1])) + (String) (digitalRead(k[2])) + (String) (digitalRead(k[3])));
  // digitalWrite(row_B, HIGH);

  // Serial.print(" - ");

  // digitalWrite(row_C, LOW);
  // Serial.println((String) (digitalRead(k[0])) + (String) (digitalRead(k[1])) + (String) (digitalRead(k[2])) + (String) (digitalRead(k[3])));
  // digitalWrite(row_C, HIGH);

  assumeChars(target, A);
  digitalWrite(row_A, LOW);
  scanStrokes();
  digitalWrite(row_A, HIGH);

  assumeChars(target, B);
  digitalWrite(row_B, LOW);
  scanStrokes();
  digitalWrite(row_B, HIGH);

  assumeChars(target, C);
  digitalWrite(row_C, LOW);
  scanStrokes();
  digitalWrite(row_C, HIGH);
}
