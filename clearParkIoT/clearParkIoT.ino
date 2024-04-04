#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Code_Length 8
#define Max_Masters 3

char Data[Code_Length];
char Masters[Max_Masters][Code_Length] = {"123A456", "789B321", "456C789"}; // Example master codes

int lockOutput = 13;
byte data_count = 0;
char customKey;

const int ledRedPin = 12;
const int ledGreenPin = 11;
const int servoPin = 10;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  servo.attach(servoPin);
  pinMode(lockOutput, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Code:");

  customKey = customKeypad.getKey();
  if (customKey) {
    // Only add characters if the maximum password length is not reached
    if (data_count < Code_Length - 1) {
      Data[data_count] = customKey;
      lcd.setCursor(data_count, 1);
      lcd.print(Data[data_count]);
      Serial.print(Data[data_count]); // Print pressed key to serial monitor
      data_count++;
    }
  }

  // Check if the maximum password length is reached
  if (data_count == Code_Length - 1) {
    lcd.clear();

    bool isMaster = false;
    for (int i = 0; i < Max_Masters; i++) {
      if (!strcmp(Data, Masters[i])) {
        isMaster = true;
        break;
      }
    }

    if (isMaster) {
      lcd.print("Correct");
      digitalWrite(lockOutput, HIGH);
      digitalWrite(ledGreenPin, HIGH);
      servo.write(90); // Move servo to 90 degrees
      delay(5000); // Wait for 5 seconds
      servo.write(10); 
      digitalWrite(lockOutput, LOW);
      digitalWrite(ledGreenPin, LOW);
    }
    else {
      digitalWrite(ledRedPin, HIGH);
      lcd.print("Incorrect");
      delay(1000);
      digitalWrite(ledRedPin, LOW);
    }

    lcd.clear();
    clearData();
  }
}

void clearData() {
  // Clear the data array and reset the data counter
  for (byte i = 0; i < Code_Length; i++) {
    Data[i] = '\0'; // Null character
  }
  data_count = 0;
}
