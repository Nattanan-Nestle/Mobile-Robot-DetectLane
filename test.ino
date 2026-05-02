#include <Arduino.h>

// ตั้งค่า Pin มอเตอร์ A (หน้าซ้าย)
#define INF1 18
#define INF2 19
#define ENFA 21

// ตั้งค่า Pin มอเตอร์ B (หน้าขวา)
#define INF3 5
#define INF4 17
#define ENFB 16

// ตั้งค่า Pin มอเตอร์ A (หลังซ้าย)
#define INB1 27
#define INB2 26
#define ENBA 12

// ตั้งค่า Pin มอเตอร์ B (หลังขวา)
#define INB3 25
#define INB4 33
#define ENBB 32

void forward(int speed = 200) {
    ledcWrite(ENFA, speed);
    ledcWrite(ENFB, speed);
    ledcWrite(ENBA, speed);
    ledcWrite(ENBB, speed);
    digitalWrite(INF1, HIGH); digitalWrite(INF2, LOW);
    digitalWrite(INF3, HIGH); digitalWrite(INF4, LOW);
    digitalWrite(INB1, HIGH); digitalWrite(INB2, LOW);
    digitalWrite(INB3, HIGH); digitalWrite(INB4, LOW);
    Serial.println("OK:forward");
}

void backward(int speed = 200) {
    ledcWrite(ENFA, speed);
    ledcWrite(ENFB, speed);
    ledcWrite(ENBA, speed);
    ledcWrite(ENBB, speed);
    digitalWrite(INF1, LOW); digitalWrite(INF2, HIGH);
    digitalWrite(INF3, LOW); digitalWrite(INF4, HIGH);
    digitalWrite(INB1, LOW); digitalWrite(INB2, HIGH);
    digitalWrite(INB3, LOW); digitalWrite(INB4, HIGH);

    Serial.println("OK:backward");
}

void turnLeft(int speed = 150) {
    ledcWrite(ENFA, speed);
    ledcWrite(ENFB, speed);
    ledcWrite(ENBA, speed);
    ledcWrite(ENBB, speed);
    digitalWrite(INF1, LOW);  digitalWrite(INF2, HIGH);
    digitalWrite(INF3, HIGH); digitalWrite(INF4, LOW);
    digitalWrite(INB1, HIGH);  digitalWrite(INB2, LOW);
    digitalWrite(INB3, LOW); digitalWrite(INB4, HIGH);
    Serial.println("OK:left");
}

void turnRight(int speed = 150) {
    ledcWrite(ENFA, speed);
    ledcWrite(ENFB, speed);
    ledcWrite(ENBA, speed);
    ledcWrite(ENBB, speed);
    digitalWrite(INF1, HIGH); digitalWrite(INF2, LOW);
    digitalWrite(INF3, LOW);  digitalWrite(INF4, HIGH);
    digitalWrite(INB1, LOW); digitalWrite(INB2, HIGH);
    digitalWrite(INB3, HIGH);  digitalWrite(INB4, LOW);
    Serial.println("OK:right");
}

void stopMotor() {
    ledcWrite(ENFA, 0);
    ledcWrite(ENFB, 0);
    ledcWrite(ENBA, 0);
    ledcWrite(ENBB, 0);
    digitalWrite(INF1, LOW); digitalWrite(INF2, LOW);
    digitalWrite(INF3, LOW); digitalWrite(INF4, LOW);
    digitalWrite(INB1, LOW); digitalWrite(INB2, LOW);
    digitalWrite(INB3, LOW); digitalWrite(INB4, LOW);
    Serial.println("OK:stop");
}

void setup() {
    Serial.begin(115200);

    // ตั้งค่า Pin มอเตอร์
    pinMode(INF1, OUTPUT); pinMode(INF2, OUTPUT);
    pinMode(INF3, OUTPUT); pinMode(INF4, OUTPUT);
    pinMode(INB1, OUTPUT); pinMode(INB2, OUTPUT);
    pinMode(INB3, OUTPUT); pinMode(INB4, OUTPUT);

    // ตั้งค่า PWM แบบใหม่ (API 3.x)
    ledcAttach(ENFA, 1000, 8);  // Pin, Freq, Resolution
    ledcAttach(ENFB, 1000, 8);
    ledcAttach(ENBA, 1000, 8);  // Pin, Freq, Resolution
    ledcAttach(ENBB, 1000, 8);

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