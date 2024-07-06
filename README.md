# ⚙ 🙋🏻‍♂️RFID & GSM Enabled Attendance System 📜    
  <img src="https://github.com/vivekcrox/arduino_rfid_based_attendance_system/assets/133307528/aa9d49c0-1a8b-4fb8-bcb2-68bc8a115cdf" height="300">
  
  <img src="https://github.com/vivekcrox/arduino_rfid_based_attendance_system/assets/133307528/f14d927e-1356-457d-bbdc-db3986d84370" height="300">

## 🛠 Overview

The system revolves around RFID tags carried by users (students, employees, etc.). These
tags contain unique identifiers that are read by a dedicated RFID reader module connected to
the Arduino microcontroller. Alternatively, a keypad can be incorporated to allow for manual
ID entry (optional). The retrieved ID is then verified against a database stored on the
Arduino's memory or an external storage device (SD card).

Upon successful verification, the system performs the following actions:

• Records the attendance with date and time.

• Displays a confirmation message on a connected LCD screen (if available).

• Illuminates a green LED (if available) for visual confirmation.

• Optionally, sends an SMS notification to designated recipients (e.g.,
parents/guardians) regarding the user's attendance status.

In case of unsuccessful verification (e.g., unknown ID), the system can display an error
message on the LCD (if available) and illuminate a red LED (if available) for notification.


## 🛠 Hardware Requirements

- Arduino uno
- Power Adapter
- gsm module
- rfid reader
- rfid card
- keypad
- LCD display
- wires
- dc to dc converter
- sim module.

## 👩🏻‍💻 Software Requirement

- Arduino IDE
- C++ language
