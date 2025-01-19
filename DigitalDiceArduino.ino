byte seven_seg_digits[6] = {
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110  // 6
};

int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

const int buttonPin = 9; // Button input pin
int lastButtonState = HIGH; // Last known state of the button

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up for the button

  randomSeed(analogRead(0)); // Seed random generator
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) { // Button press detected
    int diceRoll = random(0, 6); // Generate random number (0-5)
    sevenSegWrite(diceRoll);     // Display the number
    delay(500);                  // Debounce delay
  }

  lastButtonState = buttonState; // Update button state
}

void sevenSegWrite(byte digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
  digitalWrite(latchPin, HIGH);
}
