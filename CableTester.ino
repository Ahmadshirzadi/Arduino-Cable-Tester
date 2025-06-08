#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // آدرس LCD

const int wires = 10;
int startPin = 4; // شروع از پین D4
int ledGreen = 2, ledRed = 3;
int buttonPin = 7; // پین شستی

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // شستی با مقاومت Pull-Up داخلی
  
  for(int i=0; i<wires; i++) {
    pinMode(startPin + i, INPUT_PULLUP);
  }
  
  lcd.clear();
  lcd.print("Press Button to");
  lcd.setCursor(0,1);
  lcd.print("Start Test...");
}

void loop() {
  if(digitalRead(buttonPin) == LOW) { // اگر شستی فشار داده شد
    delay(50); // حذف نویز
    if(digitalRead(buttonPin) == LOW) { // تأیید فشار شستی
      runTest();
    }
  }
}

void runTest() {
  bool allOK = true;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Testing...");
  
  for(int i=0; i<wires; i++) {
    lcd.setCursor(0, (i/5)+1);
    lcd.print("W");
    lcd.print(i+1);
    lcd.print(":");
    
    if(digitalRead(startPin + i) == LOW) {
      lcd.print("OK ");
    } else {
      lcd.print("BAD");
      allOK = false;
    }
  }
  
  digitalWrite(ledGreen, allOK);
  digitalWrite(ledRed, !allOK);
  
  // نمایش نتیجه نهایی
  lcd.setCursor(0,3);
  if(allOK) {
    lcd.print("ALL WIRES OK!");
  } else {
    lcd.print("CHECK WIRES!");
  }
  
  delay(3000);
  lcd.clear();
  lcd.print("Press Button to");
  lcd.setCursor(0,1);
  lcd.print("Test Again...");
}
