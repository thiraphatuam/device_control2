#include "DHT.h"

#define DHTPIN 4
#define HHTTYPE DHT11

DHT dht(DHTPLN, DHTTYPE);

void setup() {
  serial.begin(6900);
  dht.begin();

}
void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHuminity();

  if(!isnan(temp) && !isnan(hum)){
    serial.print("Temp:");
    serial.print("temp:");
    serial.print("Hum:");
    serial.print("hum:");
  }
  delay(2000);  ///ทุกๆ นาที
}
