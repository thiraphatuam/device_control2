#define LED_BUILTIN 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  digitalWrite(LED_BUILTIN, 1);
  Serial.print("สวัสดี ธีรภัทร์ อ่วมกระโทก");
  Serial.print("light ...\n");
  delay(1000);

  digitalWrite(LED_BUILTIN, 0);
  Serial.print("สวัสดี ธีรภัทร์ อ่วมกระโทก");
  Serial.print("not light ...\n");
  delay(1000);
}