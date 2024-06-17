#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

const int columnPins[] = {11, 12, 13}; // Columns
const int rowPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // Rows

const int numColumns = sizeof(columnPins) / sizeof(columnPins[0]);
const int numRows = sizeof(rowPins) / sizeof(rowPins[0]);

const char *words[numColumns][numRows] = {
  {"PM", "FIVE_", "TO", "NINE", "THREE", "TWO", "-", "-", "-"},
  {"AM", "-", "TEN_", "-", "SIX", "FIVE", "ELEVEN", "TWELVE", "OCLOCK"},
  {"A QUARTER", "TWENTY", "HALF", "PAST", "ONE", "FOUR", "EIGHT", "SEVEN", "TEN"}
};

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < numColumns; i++) {
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], LOW);
  }

  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (true);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  int hour = now.hour() % 12;
  if (hour == 0) hour = 12; // Convert hour 0 to 12 for 12-hour clock
  int minute = now.minute();

  clearDisplay();

  if (minute >= 0 && minute < 5) {
    // HOUR OCLOCK
    displayWord("OCLOCK");
    displayHour(hour);
  } else if (minute >= 5 && minute < 10) {
    // FIVE PAST HOUR
    displayWord("FIVE_");
    displayWord("PAST");
    displayHour(hour);
  } else if (minute >= 10 && minute < 15) {
    // TEN PAST HOUR
    displayWord("TEN_");
    displayWord("PAST");
    displayHour(hour);
  } else if (minute >= 15 && minute < 23) {
    // A QUARTER PAST HOUR
    displayWord("A QUARTER");
    displayWord("PAST");
    displayHour(hour);
  } else if (minute >= 23 && minute < 43) {
    // HALF PAST HOUR
    displayWord("HALF");
    displayWord("PAST");
    displayHour(hour);
  } else if (minute >= 43 && minute < 50) {
    // A QUARTER TO HOUR+1
    displayWord("A QUARTER");
    displayWord("TO");
    displayHour((hour + 1) % 12);
    if ((hour + 1) % 12 == 0) displayHour(12); // Handle hour wrap-around
  } else if (minute >= 50 && minute < 55) {
    // TEN TO HOUR+1
    displayWord("TEN");
    displayWord("TO");
    displayHour((hour + 1) % 12);
    if ((hour + 1) % 12 == 0) displayHour(12); // Handle hour wrap-around
  } else if (minute >= 55 && minute < 60) {
    // FIVE TO HOUR+1
    displayWord("FIVE");
    displayWord("TO");
    displayHour((hour + 1) % 12);
    if ((hour + 1) % 12 == 0) displayHour(12); // Handle hour wrap-around
  }
}

void clearDisplay() {
  PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));
  PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
  PORTB &= ~((1 << PB0) | (1 << PB1));
}

void displayWord(const char* word) {
  for (int col = 0; col < numColumns; col++) {
    for (int row = 0; row < numRows; row++) {
      if (strcmp(words[col][row], word) == 0) {
        digitalWrite(columnPins[col], HIGH);
        digitalWrite(rowPins[row], HIGH);
        delay(3);
        digitalWrite(columnPins[col], LOW);
        digitalWrite(rowPins[row], LOW);
      }
    }
  }
}

void displayHour(int hour) {
  const char* hourWord = "";
  switch (hour) {
    case 1: hourWord = "ONE"; break;
    case 2: hourWord = "TWO"; break;
    case 3: hourWord = "THREE"; break;
    case 4: hourWord = "FOUR"; break;
    case 5: hourWord = "FIVE"; break;
    case 6: hourWord = "SIX"; break;
    case 7: hourWord = "SEVEN"; break;
    case 8: hourWord = "EIGHT"; break;
    case 9: hourWord = "NINE"; break;
    case 10: hourWord = "TEN"; break;
    case 11: hourWord = "ELEVEN"; break;
    case 12: hourWord = "TWELVE"; break;
  }
  displayWord(hourWord);
}
