#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>

// Firebase configuration
#define FIREBASE_HOST "cycle-parking-system-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "_YOUR_FIREBASE_API_KEY_HERE_"
// Initialize Firebase
FirebaseData firebaseData;
FirebaseESP32 firebase;

// Pins for Servos and LEDs
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
#define Servo_1 27 // Pin for Slot 0 LED
#define Servo_2 33 // Pin for Slot 1 LED
#define Servo_3 4 // Pin for Slot 1 LED
#define Servo_4 16 // Pin for Slot 1 LED

#define LED_1 14
#define LED_2 25
#define LED_3 17
#define LED_4 2

// Other pins
#define buzzer 19 
#define button1 12
#define button2 26
#define button3 32
#define button4 15

// Structure for authorized users
struct AuthorizedUser {
  String uid;
  String name;
  String regNumber;
};

// List of authorized users
AuthorizedUser authorizedUsers[] = {
 {"AA65FF30", "ALDRIN", "URK22EC1019"},
 {"7535ABAC", "ABY ALEX", "URK22EC1018"},
 {"2D889A67", "BENNY", "URK22EC1017"},
 {"DD65FF30", "SAMSON", "URK22EC1016"},
 {"0DC65E66", "THIMOTHY", "URK22EC4012"}
  // Add more authorized users as needed
};

// Slot status and user mapping
bool slot_state[4] = {false, false, false, false}; // Initial slot state for 2 slots
String uid_slot[4] = {"nil0", "nil1", "nil2", "nil3"};
bool slotFull = false;

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the I2C LCD display with its address

void setup() {
  // Initialize hardware components
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);   // Initialize the LCD display
  lcd.backlight();
  
  servo1.attach(Servo_1);
  servo2.attach(Servo_2);
  servo3.attach(Servo_3);
  servo4.attach(Servo_4);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  // Connect to WiFi
  WiFi.begin("Virus#404", "password1");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  
  // Initialize Firebase and update slot status
  firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Update the slot status in the Firebase database
  firebase.setBool(firebaseData, "/CycleParking/slot1", false);
  firebase.setBool(firebaseData, "/CycleParking/slot2", false);
  firebase.setBool(firebaseData, "/CycleParking/slot3", false);
  firebase.setBool(firebaseData, "/CycleParking/slot4", false);
  
  // Initialize LCD display
  lcd.setCursor(1, 0);
  lcd.print("<Device Ready>");
  lcd.setCursor(4, 1);
  lcd.print("WELCOME!");  
  delay(1000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("#Scan Your ID#");
  Serial.println("Ready to read RFID tags...");
}  

// Check if UID is authorized
bool isAuthorizedUID(String uid) {
  for (int i = 0; i < sizeof(authorizedUsers) / sizeof(authorizedUsers[0]); i++) {
    if (uid == authorizedUsers[i].uid) {
      return true; // UID is authorized
    }
  }
  return false; // UID is not authorized
}

// Play a sound using the buzzer
void sound(){
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

// Book a parking slot
int BookSlot(int slot) {
  switch (slot) {
    int state;
    case 0:
      state = 0;
      servo1.write(0);
      digitalWrite(LED_1, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button1) == LOW){
          delay(1000);
          state = 1; 
          break;
        }
        delay(500);
      }
      servo1.write(120);
      digitalWrite(LED_1, LOW);
      sound();
      return state;
      break;

    case 1:
      state = 0;
      servo2.write(0);
      digitalWrite(LED_2, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button2) == LOW){
          delay(1000);
          state = 1;          
          break;
        }
        delay(500);
      }
      servo2.write(120);
      digitalWrite(LED_2, LOW);      
      sound();
      return state;
      break;

    case 2:
      state = 0;
      servo3.write(0);
      digitalWrite(LED_3, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button3) == LOW){
          delay(1000);
          state = 1; 
          break;
        }
        delay(500);
      }
      servo3.write(120);
      digitalWrite(LED_3, LOW);
      sound();
      return state;
      break;

    case 3:
      state = 0;
      servo4.write(0);
      digitalWrite(LED_4, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button4) == LOW){
          delay(1000);
          state = 1;          
          break;
        }
        delay(500);
      }
      servo4.write(120);
      digitalWrite(LED_4, LOW);      
      sound();
      return state;
      break;

    default:
      break;
  }
 }

// Withdraw from a parking slot
int WithdrawSlot(int slot) {
  switch (slot) {
    int state;    
    case 0:
      state = 1;
      servo1.write(0);
      digitalWrite(LED_1, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button1) == HIGH){
          delay(1000);
          state = 0;
          break;
        }
        delay(500);
      }
      servo1.write(120);
      digitalWrite(LED_1, LOW);
      sound();
      return state;
      break;

    case 1:
      state = 1;
      servo2.write(0);
      digitalWrite(LED_2, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button2) == HIGH){
          delay(1000);
          state = 0;
          break;
        }
        delay(500);
      }
      servo2.write(120);
      digitalWrite(LED_2, LOW);
      sound();
      return state;
      break;

    case 2:
      state = 1;
      servo3.write(0);
      digitalWrite(LED_3, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button3) == HIGH){
          delay(1000);
          state = 0;
          break;
        }
        delay(500);
      }
      servo3.write(120);
      digitalWrite(LED_3, LOW);
      sound();
      return state;
      break;

    case 3:
      state = 1;
      servo4.write(0);
      digitalWrite(LED_4, HIGH);
      for(int i=0; i<10; i++){
        if(digitalRead(button4) == HIGH){
          delay(1000);
          state = 0;
          break;
        }
        delay(500);
      }
      servo4.write(120);
      digitalWrite(LED_4, LOW);
      sound();
      return state;
      break;

    default:
      break;
  }
}

// Display welcome message on LCD
void scanID() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("#Scan Your ID#");
}

// Find index of authorized user by UID
int P(String uid) {
  for (int i = 0; i < sizeof(authorizedUsers) / sizeof(authorizedUsers[0]); i++) {
    if (uid == authorizedUsers[i].uid) {
      return i; // UID is authorized
    }
  }
}

void loop() {
  
String Data = "";
bool dataInput = false;

if(WiFi.status() != WL_CONNECTED){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[!Server'Error!]");

  WiFi.begin("Virus#404", "password1");
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }  
  Serial.println();
  Serial.println("WiFi connected");

  firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  scanID();
}

//Slot Booking Through App
if (Firebase.getString(firebaseData, "/CycleParking/input")) {
  if (firebaseData.dataType() == "string") {
    String temp = firebaseData.stringData();
    temp.trim();  // Remove leading and trailing whitespaces
    
    if (temp.length() > 7) {  // Check if the string length is greater than 8
      Data = temp.substring(2, temp.length() - 2);
      dataInput = true;
    }
  }
}

//Check if All Slots are Full
if (!(Serial.available() > 0) && slotFull == true) {
    scanID();
    lcd.setCursor(0, 1);
    lcd.print("            ");
    delay(500);
    lcd.setCursor(2, 1);
    lcd.print("[SlotsFuLL!]");
    delay(1000);  
}
// Handle RFID scanning and slot management
if ((Serial.available() > 0) || (dataInput)){
    String uid = "";
    if(!dataInput){
    uid = Serial.readString();
    uid.trim();
    lcd.clear();
    lcd.setCursor(1, 0);  
    lcd.print("...ScanninG...");
    delay(500);
    }
    else{
    uid = Data;
    lcd.clear();
    lcd.setCursor(1, 0);  
    lcd.print("UID: " + uid);
    delay(500);
    }

    uid.toUpperCase();
    Serial.print("UID: ");
    Serial.println(uid);

    if (!isAuthorizedUID(uid)) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("!Unknown UseR!");
      lcd.setCursor(2, 1);
      lcd.print("AccessDenieD");
      delay(2000);

      scanID();
      
      Serial.println("Unauthorized access!\n");
      return;
    }
        
    for (int i = 0; i < 4; i++) {

      if (slot_state[i] == true && uid_slot[i] == uid) {
        slot_state[i] = false;
        uid_slot[i] = "nil";
        uid_slot[i].concat(String(i));

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(authorizedUsers[P(uid)].name);
        lcd.setCursor(0, 1);
        lcd.print(authorizedUsers[P(uid)].regNumber);
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(authorizedUsers[P(uid)].name);
        lcd.setCursor(0, 1);
        lcd.print("Slot: ");
        lcd.print(i+1);
        delay(1000);
        
        if(WithdrawSlot(i) == 0){
        slotFull = false;
        
        // Update the slot status in the Firebase database
        firebase.setBool(firebaseData, "/CycleParking/slot" + String(i+1), slot_state[i]);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("*Cycle UnParkeD*");
        lcd.setCursor(2,1);
        lcd.print("[ Slot: ");
        lcd.print(i+1);
        lcd.print(" ]");
        delay(2000);
        }
        else{
        slot_state[i] = true;
        uid_slot[i] = uid;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Unparking FaileD");
        lcd.setCursor(3,1);
        lcd.print("Try AgaiN!");
        delay(2000);}
        
        scanID();
        break;
      }
      if (!(slot_state[0] && slot_state[1] && slot_state[2] && slot_state[3])) {
       if (slot_state[i] == false && uid != uid_slot[0] && uid != uid_slot[1] && uid != uid_slot[2] && uid != uid_slot[3]) {
          uid_slot[i] = uid;
          slot_state[i] = true;

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(authorizedUsers[P(uid)].name);
          lcd.setCursor(0, 1);
          lcd.print(authorizedUsers[P(uid)].regNumber);
          delay(2000);

          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Alloted SloT");
          lcd.setCursor(4, 1);
          lcd.print("Slot:  ");
          lcd.print(i+1);
          delay(1000);
              
          if(BookSlot(i) == 1){
             
            // Update the slot status in the Firebase database
            firebase.setBool(firebaseData, "/CycleParking/slot" + String(i+1), slot_state[i]);

            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("*Cycle ParkeD*");
            lcd.setCursor(3,1);
            lcd.print("[Slot:  ");
            lcd.print(i+1);
            lcd.print("]");
            delay(2000);
            scanID();
            if(slot_state[0] && slot_state[1] && slot_state[2] && slot_state[3]){
            scanID();
            slotFull = true;          
           }
           else{
            scanID();
            slotFull = false;
            }
          }
          else{
            slot_state[i] = false;
            uid_slot[i] = "nil";
            uid_slot[i].concat(String(i));

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("*Parking FaileD*");
            lcd.setCursor(3,1);
            lcd.print("Try AgaiN!");
            delay(2000);
            scanID();
            break;
          }        
        }
      }
      else if (slot_state[0] && slot_state[1] && slot_state[2] && slot_state[3] && i == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Slots");
        lcd.setCursor(0, 1);
        lcd.print("Available!");
        delay(2000);
      }
    }
  }
}
