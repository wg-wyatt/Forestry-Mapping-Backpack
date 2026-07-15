#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>

// --- PINS ---
#define PPS_PIN   2   
#define GPS_RX    4   
#define GPS_TX    5   
#define ENC_CS    9   
#define MTR_SPD   6   
#define MTR_DIR   8   
#define MTR_EN    10  

// --- SETTINGS ---
const int bitResolution = 17; 
const int targetMotorSpeed = 51; // Constant speed when running

// --- VARIABLES ---
TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);

volatile unsigned long lastPPSMillis = 0;
unsigned long lastEncoderMillis = 0;
bool motorRunning = true; // Track state for Stop/Go

void ppsHandler() {
    lastPPSMillis = millis();
     Serial.println("PPS Detected");
}

void setup() {
    Serial.begin(115200);
    gpsSerial.begin(9600);
    
    pinMode(PPS_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PPS_PIN), ppsHandler, FALLING);

    // SPI Setup for AksIM-2
    pinMode(ENC_CS, OUTPUT);
    digitalWrite(ENC_CS, HIGH);
    SPI.begin();

    // Motor Setup
    pinMode(MTR_SPD, OUTPUT);
    pinMode(MTR_DIR, OUTPUT);
    pinMode(MTR_EN, OUTPUT);
    
    // Initial Start
    digitalWrite(MTR_EN, HIGH);
    analogWrite(MTR_SPD, targetMotorSpeed);
    
    Serial.println(F("System Ready. Type 'stop' to pause, 'go' to resume."));
}

uint32_t readEncoder() {
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ENC_CS, LOW);
    
    uint32_t b1 = SPI.transfer(0x00);
    uint32_t b2 = SPI.transfer(0x00);
    uint32_t b3 = SPI.transfer(0x00);
    
    digitalWrite(ENC_CS, HIGH);
    SPI.endTransaction();

    return (b1 << 16) | (b2 << 8) | b3;
}

void loop() {
    // 1. GPS Processing
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    // 2. Stop/Go Logic
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim(); // Remove whitespace
        
        if (cmd.equalsIgnoreCase("stop")) {
            motorRunning = false;
            digitalWrite(MTR_EN, LOW);
            Serial.println(F(">>> MOTOR STOPPED"));
        } 
        else if (cmd.equalsIgnoreCase("go")) {
            motorRunning = true;
            digitalWrite(MTR_EN, HIGH);
            analogWrite(MTR_SPD, targetMotorSpeed);
            Serial.println(F(">>> MOTOR RESUMED"));
        }
    }

    // 3. 100Hz Logging Loop
    // 3. 100Hz Logging Loop
    if (millis() - lastEncoderMillis >= 10) {
        lastEncoderMillis = millis();
        
        // ... (Your encoder reading logic) ...

        unsigned long offset = millis() - lastPPSMillis;
        
        Serial.print(F(" | UTC:"));
        
        // Bypass the validity check to see what the SBG is actually sending
        // Check gps.time.age() to make sure we are getting data at all
        if (gps.time.age() < 2000) { 
            printfTime(gps.time.hour(), gps.time.minute(), gps.time.second(), offset);
        } else {
            Serial.println(F("NO SERIAL DATA"));
        }
    }
}

void printfTime(int h, int m, int s, unsigned long ms) {
    if (ms > 999) ms = 999;
    char buf[20];
    sprintf(buf, "%02d:%02d:%02d.%03lu", h, m, s, ms);
    Serial.println(buf);
}