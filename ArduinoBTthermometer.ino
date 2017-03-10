#include <SoftwareSerial.h>
#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 2

//分时复用参数
const int blanking = 2000;
unsigned long lastTime = 0;
SoftwareSerial bt(8, 9);  //RX,TX

void setup(){
  Serial.begin(9600);
  bt.begin(38400);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}

void loop(){
  refreshData();
}

void refreshData(){           //执行一轮数据采样并发送
  if (millis() - lastTime < blanking)
    return;                             //时候未到
  lastTime = millis();
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }
  
  bt.write(DHT11.humidity/10 + 48);
  bt.write(DHT11.humidity%10 + 48);
  bt.write('h');
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  bt.write(DHT11.temperature/10 + 48);
  bt.write(DHT11.temperature%10 + 48);
  bt.write('t');
  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);
}
