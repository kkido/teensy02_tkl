
#include "Keyboard.h"
//#define CPU_16MHz       0x00
const int BK1 = 23;
const int BK2 = 10;
const int BK3 = 9;
const int BK4 = 8;
const int BK5 = 7;
const int BK6 = 6;

const int R1 = 17;
const int R2 = 18;
const int R3 = 19;
const int R4 = 20;
const int R5 = 21;
const int R6 = 2;
const int R7 = 1;
const int R8 = 0;
const int R9 = 5;
const int R10 = 4;
const int R11 = 3;
const int R12 = 16;
const int R13 = 15;
const int R14 = 14;
const int R15 = 13;
const int R16 = 22;
const int R17 = 11;
const int R18 = 12;

const int rowNum = 6;
const int colNum = 18;

const int rowPin[rowNum] = {BK1, BK2, BK3, BK4, BK5, BK6};
const int colPin[colNum] = {R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15, R16, R17, R18};

bool activeState[rowNum][colNum];
bool staticState[rowNum][colNum];

//const byte keyMap[rowNum][colNum]  = {
//  { 0x1B, 0x00, 0xC2, 0xC3, 0xC4, 0xC5, 0x00, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0x0B, 0x19, 0x18 }, //BK1
//  { 0x60, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x2D, 0x3D, 0x08, 0x00, 0xD1, 0xD2, 0xD3 }, //BK2
//  { 0x09, 0x71, 0x77, 0x65, 0x72, 0x74, 0x79, 0x75, 0x69, 0x6F, 0x70, 0x5B, 0x5D, 0x5C, 0x00, 0xD4, 0xD5, 0xD6 }, //BK3
//  { 0xC1, 0x61, 0x73, 0x64, 0x66, 0x67, 0x68, 0x6A, 0x6B, 0x6C, 0x3B, 0x27, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x00 }, //BK4
//  { 0x81, 0x7A, 0x78, 0x63, 0x76, 0x62, 0x6E, 0x6D, 0x2C, 0x2E, 0x2F, 0x00, 0x00, 0x85, 0x00, 0x00, 0xDA, 0x00 }, //BK5
//  { 0x80, 0x82, 0x83, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x87, 0x00, 0x86, 0x00, 0x84, 0xD8, 0xD9, 0xD7 } //BK5
//};

const unsigned int teensyKeyMap[rowNum][colNum] = {
  {KEY_ESC, KEYPAD_0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINTSCREEN, KEY_SCROLL_LOCK, KEY_PAUSE},
  {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEYPAD_0, KEY_INSERT, KEY_HOME, KEY_PAGE_UP},
  {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEYPAD_0, KEY_DELETE, KEY_END, KEY_PAGE_DOWN},
  {KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEYPAD_0, KEY_ENTER, KEYPAD_0, KEYPAD_0, KEYPAD_0, KEYPAD_0},
  {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEYPAD_0, KEYPAD_0, KEY_RIGHT_SHIFT, KEYPAD_0, KEYPAD_0, KEY_UP, KEYPAD_0},
  {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEYPAD_0, KEYPAD_0, KEYPAD_0, KEY_SPACE, KEYPAD_0, KEYPAD_0, KEYPAD_0, KEY_RIGHT_GUI, KEYPAD_0, KEY_RIGHT_ALT, KEYPAD_0, KEY_RIGHT_CTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT}
};

int i, j;

void setup() {
  for(i = 0; i < colNum; i++) {
    pinMode(colPin[i], INPUT_PULLUP);
  }
  for(i = 0; i < rowNum; i++) {
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], HIGH);
  }
  for( i = 0; i < rowNum; i++) {
    for ( j = 0; j < colNum; j++) {
      activeState[i][j] = HIGH;
      staticState[i][j] = HIGH;
    }
  }
  Keyboard.begin();
}
void loop() {
  for(i = 0; i < rowNum; i++) {
    digitalWrite( rowPin[i], LOW);

    for( j = 0; j < colNum; j++ ) {
      activeState[i][j] = digitalRead(colPin[j]);

      //Debug
//      if( j+1 != colNum){
//        Serial.print("Row:");
//        Serial.print(i);
//        Serial.print("-");
//        Serial.print(digitalRead(rowPin[i]));
//        Serial.print(" Col:");
//        Serial.print(j);
//        Serial.print("-");
//        Serial.print(digitalRead(colPin[j]));
//        Serial.print(" State:");
//        Serial.print(activeState[i][j]);
//        Serial.print(" | ");
//      } else {
//        Serial.println("");
//      }


      if( activeState[i][j] != staticState[i][j] ) {
//        Serial.print("key(");
//        Serial.print(i);
//        Serial.print(",");
//        Serial.print(j);
//        Serial.print(")");
//        Serial.print(", ActiveState:");
//        Serial.print(activeState[i][j]);
//        Serial.print(", StaticState:");
//        Serial.println(staticState[i][j]);

        if( activeState[i][j] == LOW) {
          Keyboard.press(teensyKeyMap[i][j]);
//          Serial.print(":");
//          Serial.println(" Push!");
        } else {
          Keyboard.release(teensyKeyMap[i][j]);
//          Serial.print(":");
//          Serial.println(" Release!");
        }
        delay(10);
        staticState[i][j] = activeState[i][j];
        delay(10);
      }
    }
//  delayMicroseconds(20000);
  digitalWrite( rowPin[i], HIGH);
  }
//  Serial.println(""); // Debug
//  delay(3000);
}