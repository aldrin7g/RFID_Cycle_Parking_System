# RFID-Based Cycle Parking System

The RFID-Based Cycle Parking System is a smart solution for efficient cycle parking management using RFID technology. This repository contains the source code for the project, including both the Arduino code for RFID tag reading and the NodeMCU ESP32 code for slot management and communication with a dedicated app developed using MIT App Inventor. The system offers seamless bicycle parking, retrieval, and monitoring through RFID tags and a user-friendly mobile app.

## Table of Contents

- [Project Overview](#project-overview)
- [How the System Works](#how-the-system-works)
- [Arduino Code Explanation](#arduino-code-explanation)
- [NodeMCU ESP32 Code Explanation](#nodemcu-esp32-code-explanation)
- [MIT App Inventor App and Firebase Integration](#mit-app-inventor-app-and-firebase-integration)
- [Future Plans](#future-plans)
- [How to Use](#how-to-use)
- [Dependencies](#dependencies)
- [Contributors](#contributors)
- [License](#license)

## Project Overview

The RFID-Based Cycle Parking System aims to streamline the process of parking, securing, and retrieving bicycles in a designated parking area. The system leverages RFID technology to identify users, allocate parking slots, and communicate with a dedicated mobile app. It comprises two main components: an Arduino board equipped with an RFID RC522 reader for tag scanning and a NodeMCU ESP32 board responsible for slot management, communication with Firebase, and interaction with the MIT App Inventor app.

## How the System Works

1. **RFID Tag Scanning**: Users scan their RFID tags using the RFID RC522 reader at the bicycle parking stand. The Arduino board reads the unique identification (UID) of the RFID tag and sends it to the NodeMCU ESP32 board over UART communication.

2. **Slot Allocation**: Upon receiving the UID from the Arduino, the NodeMCU ESP32 processes the information. If the user is authorized and parking slots are available, the system allocates an available slot for the user. This is done by controlling servos that secure the bicycle in place within the designated slot.

3. **Automatic Locking**: After the user parks their bicycle, a switch activated by the bicycle wheel triggers the automatic locking mechanism. The slot's locking mechanism engages, securing the bicycle in the allocated spot.

4. **Unlocking and Retrieval**: To retrieve their bicycle, the user scans their RFID tag again. The NodeMCU ESP32 verifies the user's identity and releases the locking mechanism of the allocated slot. The slot automatically unlocks and can be opened for the user to take their bicycle.

5. **Dedicated App**: A dedicated app developed using MIT App Inventor is provided to users for an alternative method of slot allocation and monitoring. The app is integrated with a Firebase database and allows users to view slot availability, book slots, and receive notifications.

## Arduino Code Explanation

The Arduino code initializes the RFID RC522 reader, sets up the serial communication, and continuously checks for new RFID tags. When a new tag is detected, the UID is read and sent to the NodeMCU ESP32 for further processing.

## NodeMCU ESP32 Code Explanation

The NodeMCU ESP32 code handles various tasks, including slot booking and withdrawal, communication with Firebase, controlling servos and LEDs, and interfacing with the I2C LCD. It manages the slot status and updates the Firebase database accordingly. The code also checks for scenarios where all parking slots are occupied, displaying appropriate messages on the LCD. Additionally, the code establishes Wi-Fi connectivity, sets up UART communication with the Arduino, and integrates with Firebase for remote monitoring.

## MIT App Inventor App and Firebase Integration

The MIT App Inventor app provides users with an intuitive interface to monitor slot availability and book parking slots. The app connects to the Firebase Realtime Database, retrieving slot status information and displaying it to users. Users can also book slots through the app. The app also has the potential for further enhancement, such as real-time updates and more interactive features.

## Future Plans

The project's future plans include optimizing the hardware setup by using techniques like shift register ICs or multiplexers to manage more inputs and outputs efficiently. Additionally, considerations are made for improving security and data retention by incorporating a mechanical locking mechanism and interfacing with an SD card. The project also aims to make the app more versatile, allowing for remote database updates and potentially creating a compact, portable version that can be mounted on bicycles themselves.

## How to Use

1. Upload the Arduino code to the Arduino board with the RFID RC522 reader.
2. Upload the NodeMCU ESP32 code to the NodeMCU ESP32 board.
3. Connect the Arduino board's UART pins (TX and RX) to the NodeMCU ESP32's UART pins (RX and TX) for communication.
4. Set up the necessary hardware components, including servos, LEDs, buttons, buzzer, and I2C LCD.
5. Connect the NodeMCU ESP32 board to Wi-Fi and Firebase according to the configuration in the code.
6. As users present their RFID tags to the reader, the system will handle slot booking and withdrawal based on availability.
7. The I2C LCD will display relevant instructions and status updates.
8. Alternatively, users can use the MIT App Inventor app to monitor slot availability and to book slots.

## Dependencies

- Arduino: `SPI`, `MFRC522`
- NodeMCU ESP32: `Wire`, `LiquidCrystal_I2C`, `ESP32Servo`, `WiFi`, `FirebaseESP32`, `ArduinoJson`

## Contributors

- ALDRN G (https://github.com/aldrin7g)

## License

Feel free to use and modify the code according to your needs.
