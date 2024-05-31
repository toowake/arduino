const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; // Pins connected to keypad rows
byte colPins[COLS] = {6, 7, 8, 9}; // Pins connected to keypad columns

char password[] = "1234"; // Set your desired password

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  char input = readKeypad();
  if (input != '\0') {
    Serial.print(input);
  }
  if (checkPassword()) {
    Serial.println(" - Access Granted!");
    // Add actions to perform when password is correct
  }
}

char readKeypad() {
  for (int i = 0; i < ROWS; i++) {
    digitalWrite(rowPins[i], LOW);
    for (int j = 0; j < COLS; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        delay(10);
        if (digitalRead(colPins[j]) == LOW) {
          digitalWrite(rowPins[i], HIGH);
          return keys[i][j];
        }
      }
    }
    digitalWrite(rowPins[i], HIGH);
  }
  return '\0';
}

bool checkPassword() {
  String enteredPassword = "";
  while (Serial.available()) {
    enteredPassword += Serial.readStringUntil('\n');
  }
  return (enteredPassword == password);
}
