/**
 * @file main.cpp
 * @brief Motor Drive & IMU Synchronization System
 * 
 * @author Stefan Vin
 * @generated_with Gemini
 * @date 2026-07-23
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>

// --- SCHEMATIC PIN DEFINITIONS ---
#define IMU_SYNC_PIN 2   // D2 - IMU_SYNC_IN (PPS / Time Sync Input)
#define MOT_FAULT_PIN 3  // D3 - MOT_FAULT (Input from Motor Controller)
#define IMU_RX_PIN    5  // D5 - NANO_UART_RX (From MAX3232 R1OUT)
#define IMU_TX_PIN    4  // D4 - NANO_UART_TX (To MAX3232 T1IN)
#define MOT_PWM_PIN   6  // D6 - MOT_PWM (Speed Control)
#define MOT_ENBL_PIN  7  // D7 - MOT_ENBL (Driver Enable)
#define MOT_DIR_PIN   8  // D8 - MOT_ROT_DIR (Rotation Direction)
#define ENC_CS_PIN    9  // D9 - ENC_NCS (AksIM-2 SPI Chip Select)
#define MOT_RUN_PIN   10 // D10 - MOT_RUN (Run/Stop Line)

// Hardware SPI Pins on Arduino Nano:
// D11 = MOSI, D12 = MISO, D13 = SCK

// --- SETTINGS ---
const int targetMotorSpeed = 51; // Constant PWM speed (0-255)

// --- OBJECTS & VARIABLES ---
TinyGPSPlus gps;
SoftwareSerial imuSerial(IMU_RX_PIN, IMU_TX_PIN); // RX = Pin 5, TX = Pin 4

volatile unsigned long lastPPSMillis = 0;
volatile bool ppsTriggered = false;

unsigned long lastEncoderMillis = 0;
bool motorRunning = true;

// ISR for PPS Interrupt on D2
void ppsHandler() {
    lastPPSMillis = millis();
    ppsTriggered = true;
}

void setup() {
    // Standard Hardware Serial for Debugging / Commands
    Serial.begin(115200);
    
    // Software Serial for IMU Communication (via MAX3232)
    imuSerial.begin(9600);
    
    // PPS Interrupt Setup
    pinMode(IMU_SYNC_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(IMU_SYNC_PIN), ppsHandler, FALLING);

    // Encoder SPI Setup
    pinMode(ENC_CS_PIN, OUTPUT);
    digitalWrite(ENC_CS_PIN, HIGH);
    SPI.begin();

    // Motor Controller Pins Setup
    pinMode(MOT_PWM_PIN, OUTPUT);
    pinMode(MOT_ENBL_PIN, OUTPUT);
    pinMode(MOT_DIR_PIN, OUTPUT);
    pinMode(MOT_RUN_PIN, OUTPUT);
    pinMode(MOT_FAULT_PIN, INPUT);

    // Initial Motor State Setup
    digitalWrite(MOT_DIR_PIN, LOW);   // Set default direction
    digitalWrite(MOT_ENBL_PIN, HIGH); // Enable controller bridge
    digitalWrite(MOT_RUN_PIN, HIGH);  // Set Run active
    analogWrite(MOT_PWM_PIN, targetMotorSpeed);
    
    Serial.println(F("System Initialized. Commands: 'stop', 'go'."));
}

uint32_t readEncoder() {
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ENC_CS_PIN, LOW);
    
    uint32_t b1 = SPI.transfer(0x00);
    uint32_t b2 = SPI.transfer(0x00);
    uint32_t b3 = SPI.transfer(0x00);
    
    digitalWrite(ENC_CS_PIN, HIGH);
    SPI.endTransaction();

    return (b1 << 16) | (b2 << 8) | b3;
}

void printfTime(int h, int m, int s, unsigned long ms) {
    if (ms > 999) ms = 999;
    char buf[25];
    sprintf(buf, "%02d:%02d:%02d.%03lu", h, m, s, ms);
    Serial.println(buf);
}

void loop() {
    // 1. Process Serial Data from IMU
    while (imuSerial.available() > 0) {
        gps.encode(imuSerial.read());
    }

    // 2. Handle PPS Event Flag Safely
    if (ppsTriggered) {
        ppsTriggered = false;
        Serial.println(F("[SYNC] PPS Edge Detected"));
    }

    // 3. Serial Command Processing
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        
        if (cmd.equalsIgnoreCase("stop")) {
            motorRunning = false;
            digitalWrite(MOT_RUN_PIN, LOW);   // Disable output drive
            analogWrite(MOT_PWM_PIN, 0);
            Serial.println(F(">>> MOTOR STOPPED"));
        } 
        else if (cmd.equalsIgnoreCase("go")) {
            motorRunning = true;
            digitalWrite(MOT_RUN_PIN, HIGH);  // Resume output drive
            analogWrite(MOT_PWM_PIN, targetMotorSpeed);
            Serial.println(F(">>> MOTOR RESUMED"));
        }
    }

    // 4. Check for Motor Controller Faults
    if (digitalRead(MOT_FAULT_PIN) == HIGH) {
        // Adjust polarity based on Faulhaber SC2804S fault pin logic (active HIGH/LOW)
        // Serial.println(F("WARNING: Motor Controller Fault Pin Triggered!"));
    }

    // 5. 100Hz Logging Loop (10ms interval)
    if (millis() - lastEncoderMillis >= 10) {
        lastEncoderMillis = millis();
        
        uint32_t rawEncoder = readEncoder();
        unsigned long offset = millis() - lastPPSMillis;
        
        Serial.print(F("ENC: "));
        Serial.print(rawEncoder);
        Serial.print(F(" | UTC: "));
        
        if (gps.time.age() < 2000 && gps.time.isValid()) { 
            printfTime(gps.time.hour(), gps.time.minute(), gps.time.second(), offset);
        } else {
            Serial.println(F("NO TIMING DATA"));
        }
    }
}