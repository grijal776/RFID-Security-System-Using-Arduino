#include <SPI.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <MFRC522.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo myservo;

// Define the RFID tag IDs (replace with your own)
#define TAG_ID_1 0x7C5E7322
#define TAG_ID_2 0xF98D71B2

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
int pos = 0;

void setup() {
  myservo.attach(8);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  lcd.print("Show your Key");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.println("Card detected:");
      unsigned long ID = 0;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        ID <<= 8;
        ID |= mfrc522.uid.uidByte[i];
      }
      Serial.println(ID, HEX);

      if (ID == TAG_ID_1) { // Check if it matches the first tag
        lcd.clear();
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Welcome Girija");
        for (pos = 0; pos <= 180; pos += 1) {
          myservo.write(pos);
          delay(5);
        }
        delay(5000);
        lcd.clear();
        lcd.print("Door Closing");
        for (pos = 180; pos >= 0; pos -= 1) {
          myservo.write(pos);
          delay(5);
        }
      } else if (ID == TAG_ID_2) { // Check if it matches the second tag
        lcd.clear();
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Welcome AMBU");
        for (pos = 0; pos <= 180; pos += 1) {
          myservo.write(pos);
          delay(5);
        }
        delay(5000);
        lcd.clear();
        lcd.print("Door Closing");
        for (pos = 180; pos >= 0; pos -= 1) {
          myservo.write(pos);
          delay(5);
        }
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        delay(2000); // Display "Access Denied" for 2 seconds
      }
      lcd.clear();
      lcd.print("Show your Key"); // Display "Show your Key" after any action
    }
  }
}
