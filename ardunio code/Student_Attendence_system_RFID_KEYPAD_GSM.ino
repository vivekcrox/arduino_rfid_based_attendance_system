#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns and 2 rows
String phoneNumber = "+918287683669";

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create instance

byte cardUID[] = { 0xF7, 0xEE, 0x44, 0x63 }; // Specified card UID to validate against

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A1, 3, 4, 5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, A0}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin();                      // Initialize the LCD
  lcd.backlight();                  // Turn on backlight
  Serial.begin(9600);               // Initialize serial communications
  SPI.begin();                      // Init SPI bus
  mfrc522.PCD_Init();               // Init MFRC522
  lcd.setCursor(0,0);
  lcd.print("Student Attend.");  // Display message on LCD
  lcd.setCursor(0,1);
  lcd.print("      System      ");
  delay(2000);
  lcd.clear();                      // Clear the LCD before starting
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Scanning Card..."); // Indicate that the system is scanning a card
  
  if (!mfrc522.PICC_IsNewCardPresent()) { // If new card is not present
    delay(100); // Wait a short moment before checking again
    return; // Skip the current iteration and proceed to the next one
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) { // If the card's serial number cannot be read
    delay(100); // Wait a short moment before checking again
    return; // Skip the current iteration and proceed to the next one
  }
  
  lcd.clear(); // Clear the LCD before displaying the UID
  lcd.setCursor(0, 0);
  //lcd.print("Card UID:");
  Serial.print("Card UID:");
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); // Print without space
    // lcd.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); // Print without space
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.println();
  delay(1000); // Display card UID for a moment before showing valid/invalid
  
  //lcd.setCursor(0, 1);
  bool validCard = true;
  
  for (byte i = 0; i < sizeof(cardUID); i++) {
    if (mfrc522.uid.uidByte[i] != cardUID[i]) 
    {
      validCard = false;
      break;
    }
  }
  
  if (validCard) 
  {
    lcd.print("Welcome Ritik      "); // Display message on LCD
    // Add your actions when a valid card is detected here
    char password[5];
    lcd.setCursor(0, 1);
    lcd.print("EN PASSWO:");
   // lcd.setCursor(8, 1);
    for (int i = 0; i < 4; i++) 
    {
      char key = keypad.getKey();
      if (key != NO_KEY) 
      { 
        password[i] = key;
        Serial.print(key); // Print to serial monitor
        lcd.print(key); // Print to LCD
      } 
      else 
      {
        i--; // Decrement i to wait for the next key press
        delay(50); // Delay to prevent multiple key presses
      }
      delay(50); // Delay for user input
    }
    password[4] = '\0'; // Null terminate the string
    if (strcmp(password, "4569") == 0) 
    {
      lcd.clear();
      lcd.print("Success!"); // Display success message
      delay(2000);
      
      String message = "Attedence has been successfully marked for your ward Ritik";
      sendSMS(phoneNumber, message);
      delay(2000);
    } 
    else 
    {
      lcd.clear();
      lcd.print("Invalid Password"); // Display invalid password message
      delay(2000);
    }
    lcd.clear();
  } 
  
  else 
  {
    lcd.print("Invalid Card   ");    // Display message on LCD
    delay(2000); // Delay after displaying invalid message
    lcd.clear();
  }
}


void sendSMS(String number, String message) 
{
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  Serial.print(message);
  delay(100);
  Serial.write(0x1A);
  delay(1000);
}
