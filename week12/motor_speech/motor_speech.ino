#include <ESP32Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);   // ต่อ Servo ที่ขา 9
  myservo.write(0);    // เริ่มต้นที่ 0°
  delay(500);
  Serial.println("Arduino พร้อมรับคำสั่งมุม 0-180");
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();   // อ่านมุมจาก Python
    if (angle == 0 || angle == 45 || angle == 90 || angle == 135 || angle == 180) {
      myservo.write(angle);          // หมุน Servo ไปที่มุม
      Serial.print("✅ หมุนไปที่: ");
      Serial.println(angle);
    } else {
      Serial.println("⚠️ มุมไม่ถูกต้อง (เลือก 0,45,90,135,180 เท่านั้น)");
    }
  }
}
