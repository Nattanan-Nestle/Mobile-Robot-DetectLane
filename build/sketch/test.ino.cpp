#line 1 "D:\\งาน ปตท\\Code Arduino\\test\\test.ino"
#include <Arduino.h>

// ตั้งค่า Pin มอเตอร์ A (ซ้าย)
#define IN1 15
#define IN2 13
#define ENA 32

// ตั้งค่า Pin มอเตอร์ B (ขวา)
#define IN3 17
#define IN4 16
#define ENB 5

// PWM Settings
#define FREQ     1000
#define CHANNEL_A 0
#define CHANNEL_B 1
#define RESOLUTION 8  // 8-bit = 0-255

void forward(int speed = 200) {
    ledcWrite(CHANNEL_A, speed);
    ledcWrite(CHANNEL_B, speed);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    Serial.println("OK:forward");
}

void backward(int speed = 200) {
    ledcWrite(CHANNEL_A, speed);
    ledcWrite(CHANNEL_B, speed);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    Serial.println("OK:backward");
}

void turnLeft(int speed = 150) {
    ledcWrite(CHANNEL_A, speed);
    ledcWrite(CHANNEL_B, speed);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    Serial.println("OK:left");
}

void turnRight(int speed = 150) {
    ledcWrite(CHANNEL_A, speed);
    ledcWrite(CHANNEL_B, speed);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
    Serial.println("OK:right");
}

void stopMotor() {
    ledcWrite(CHANNEL_A, 0);
    ledcWrite(CHANNEL_B, 0);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    Serial.println("OK:stop");
}

void setup() {
    Serial.begin(115200);

    // ตั้งค่า Pin มอเตอร์
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

    // ตั้งค่า PWM
    ledcSetup(CHANNEL_A, FREQ, RESOLUTION);
    ledcSetup(CHANNEL_B, FREQ, RESOLUTION);
    ledcAttachPin(ENA, CHANNEL_A);
    ledcAttachPin(ENB, CHANNEL_B);

    stopMotor();
    Serial.println("ESP32 พร้อมแล้ว รอคำสั่ง...");
}

void loop() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        Serial.print("รับคำสั่ง: ");
        Serial.println(cmd);

        if (cmd == "forward")       forward();
        else if (cmd == "backward") backward();
        else if (cmd == "left")     turnLeft();
        else if (cmd == "right")    turnRight();
        else if (cmd == "stop")     stopMotor();
        else Serial.println("ERROR:unknown");
    }
}

