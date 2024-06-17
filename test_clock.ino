// Define the column and row pins
const int columnPins[] = {11, 12, 13}; // Columns
const int rowPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // Rows

const int numColumns = sizeof(columnPins) / sizeof(columnPins[0]);
const int numRows = sizeof(rowPins) / sizeof(rowPins[0]);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize column pins as OUTPUT
  for (int i = 0; i < numColumns; i++) {
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], LOW); // Ensure columns are initially LOW
  }

  // Initialize row pins as OUTPUT
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW); // Ensure rows are initially LOW
  }
}

void loop() {
  // Rapidly cycle through the switches to create the illusion that they are all on at once
  displayTestMessage();
}

void resetAllSwitches() {
  for (int col = 0; col < numColumns; col++) {
    digitalWrite(columnPins[col], LOW);
  }
  for (int row = 0; row < numRows; row++) {
    digitalWrite(rowPins[row], LOW);
  }
}

void turnOnSwitch(int col, int row) {
  digitalWrite(columnPins[col], HIGH);
  digitalWrite(rowPins[row], HIGH);
}

void turnOffSwitch(int col, int row) {
  digitalWrite(columnPins[col], LOW);
  digitalWrite(rowPins[row], LOW);
}

void displayTestMessage() {
  const int delayTime = 500; // Increase this value to improve brightness
  const int cycleTime = 8;   // Number of active switches in one cycle

  // A QUARTER TO NINE O'CLOCK
  for (int i = 0; i < delayTime; i++) {
    turnOnSwitch(2, 0); // A QUARTER
    delayMicroseconds(cycleTime);
    turnOffSwitch(2, 0);
  
    turnOnSwitch(0, 2); // TO
    delayMicroseconds(cycleTime);
    turnOffSwitch(0, 2);
  
    turnOnSwitch(0, 3); // NINE
    delayMicroseconds(cycleTime);
    turnOffSwitch(0, 3);
  
    turnOnSwitch(1, 8); // OCLOCK
    delayMicroseconds(cycleTime);
    turnOffSwitch(1, 8);
  }
}
