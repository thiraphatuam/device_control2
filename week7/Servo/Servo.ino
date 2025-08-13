#include <ESP32Servo.h>

Servo myServo;

String inputString = "";   // เก็บข้อมูลจาก Serial Monitor
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);       // ต่อ Servo ที่ขา D9
  myServo.write(0);        // เริ่มต้นที่ 0 องศา
  inputString.reserve(200);
}

void loop() {
  // เมื่อรับข้อมูลมาครบ
  if (stringComplete) {
    inputString.trim();  // ลบช่องว่าง / \n / \r

    if (inputString.equalsIgnoreCase("reset")) {
      myServo.write(0);
      Serial.println("Reset to 0 degrees");
    } else {
      // แยกค่ามุมด้วย comma
      int angle;
      int index = 0;
      String angleStr;
      while ((index = inputString.indexOf(',')) >= 0) {
        angleStr = inputString.substring(0, index);
        angle = angleStr.toInt();
        moveToAngle(angle);
        inputString = inputString.substring(index + 1);
      }

      // มุมสุดท้าย (หลัง comma สุดท้าย)
      if (inputString.length() > 0) {
        angle = inputString.toInt();
        moveToAngle(angle);
      }

      Serial.println("Donet");
    }

    // รีเซ็ตค่าข้อมูลหลังประมวลผลเสร็จ
    inputString = "";
    stringComplete = false;
  }
}

// ฟังก์ชันหมุนเซอร์โวไปยังมุมที่กำหนด
void moveToAngle(int angle) {
  myServo.write(angle);
  delay(1000);  // รอ 1 วินาที
}

// อ่านข้อมูลจาก Serial Monitor
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;

    // ตรวจสอบว่าเจอ '\n' หรือ '\r' แล้ว
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    }
  }
}