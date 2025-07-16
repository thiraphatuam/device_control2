
void setup() {
  Serial.begin(9600);
  Serial.println("----- ไฟสัญญาณจราจร -----");
}

void loop() {
  for (int i = 1; i <= 3; i++) {
    showTraffic(i);
    delay(3000); // ระยะเวลาไฟเขียว
  }
}

// แสดงสถานะไฟของถนนทั้ง 3 เส้น
void showTraffic(int greenRoad) {
  for (int i = 1; i <= 3; i++) {
    Serial.print("Road ");
    Serial.print(i);
    if (i == greenRoad) {
      Serial.println(" is Green");
    } else {
      Serial.println(" is Red");
    }
  }
  Serial.println(); // เพิ่มบรรทัดว่างเพื่ออ่านง่าย
}