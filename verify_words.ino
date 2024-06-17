// Define the column and row pins
const int columnPins[] = {11, 12, 13}; // Columns
const int rowPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // Rows

const int numColumns = sizeof(columnPins) / sizeof(columnPins[0]);
const int numRows = sizeof(rowPins) / sizeof(rowPins[0]);

// Corrected words corresponding to each switch position
const char *words[numColumns][numRows] = {
  {"PM", "FIVE", "TO", "NINE", "THREE", "TWO", "-", "-", "-"},
  {"AM", "-", "TEN", "-", "SIX", "FIVE", "ELEVEN", "TWELVE", "OCLOCK"},
  {"A QUARTER", "TWENTY", "HALF", "PAST", "ONE", "FOUR", "EIGHT", "SEVEN", "TEN"}
};

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial Monitor to connect
  }

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
  for (int col = 0; col < numColumns; col++) {
    for (int row = 0; row < numRows; row++) {
      // Turn on the specific switch
      digitalWrite(columnPins[col], HIGH);
      digitalWrite(rowPins[row], HIGH);

      // Print the corresponding word to Serial Monitor
      Serial.print("Displayed word: ");
      Serial.println(words[col][row]);
      Serial.println("Verify the word and press Enter to continue...");

      // Wait for confirmation from Serial Monitor
      waitForConfirmation();

      // Turn off the switch
      digitalWrite(columnPins[col], LOW);
      digitalWrite(rowPins[row], LOW);
    }
  }
}

void waitForConfirmation() {
  while (!Serial.available()) {
    ; // Wait for user input in Serial Monitor
  }
  while (Serial.available()) {
    Serial.read(); // Clear the input buffer
  }
  Serial.println(); // Print a newline for clarity
}
