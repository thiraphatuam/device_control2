#include <ESP32Servo.h>

Servo myservo;
char user_input;

void setup() {
  Serial.begin(9600);
  myservo.attach(5);
  Serial.println("Enter angle: 0, 45, or 90");
}

void loop() {
  if (Serial.available() > 0) {
    user_input = Serial.read();

    if (user_input == '0') {
      Serial.println("Servo Motor => 0");
      myservo.write(0);
    } 
    else if (user_input == '1') { // ใช้ '1' แทนเพื่อสั่ง 45 องศา
      Serial.println("Servo Motor => 45");
      myservo.write(45);
    } 
    else if (user_input == '2') { // ตัวอย่างเพิ่ม 90 องศา
      Serial.println("Servo Motor => 120");
      myservo.write(120);
    }else if (user_input == '3') { // ตัวอย่างเพิ่ม 90 องศา
      Serial.println("Servo Motor => 150");
      myservo.write(150);
    }else if (user_input == '4') { // ตัวอย่างเพิ่ม 90 องศา
      Serial.println("Servo Motor => 180");
      myservo.write(180);
    }
    delay(1000);
  }
}
