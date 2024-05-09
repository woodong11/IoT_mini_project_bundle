
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "sntp.h"
#define DHTPIN 13                 // DHT 센서
#define DHTTYPE    DHT11          // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// setting
int led1 = 17;
int btn1 = 18;
int pot = A0;              
 // ADC저항을 ADC0에 달았다.

int led_flag = 0;
const int freq = 5000;      //주파수 : 1초에 몇번 led를 ON/OFF 할지 결정, 보통 LED 는 5000Hz로 세팅
const int ledChannel = 0;
const int resolution = 8;   //해상도 : 얼마나 정밀하게 제어할 것인지 8 은 8 bit 해상도, 0~16bit 까지 지원, 8로 설정하면, 2^8 = 256 duty rate 로 제어하겠다는 의미

void setup() {

  // 온도센서 디테일 출력 
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("-------------INFORMATION------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  
  // 습도 센서 디테일
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  pinMode(btn1, INPUT);
  pinMode(pot, INPUT);

  delayMS = sensor.min_delay / 1000;          // 딜레이 정하기
  Serial.begin(9600);                         //Serial.begin(baud rate) : 해당 속도로 통신하겠다. 다른 기기와 할 때는 보통 속도를 맞춰야 한다.
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(led1, ledChannel);
}




void loop() {

    

  // 가변저항 값 dutyrate로 변환
  int value = analogRead(A0);                     //analogRead(pinNum): 해당 핀의 아날로그 신호 값을 읽는 API
  int m_value = map(value, 0, 1030, 0, 255);      //map(val, init_minimum, init_maximum, later_minimum, later_maximum) : 기존 값의 범위를 다른 범위로 변경하는 API, 수학 연산을 토대로 손 쉽게 범위 변경이 가능하다.
  Serial.println(F("------------------------------------"));
  Serial.print("Original ADC : "); Serial.print(value);
  Serial.print(" | Led map Value : "); Serial.println(m_value);

  // 버튼을 눌렀을때 토글되도록 한다 -> flag 토글
  if( digitalRead(btn1)==LOW ){
    led_flag ++;
    led_flag %= 2; 
  }

  // UART - 사용자 입력 시에도 키고 끈다
  if( Serial.available() ){
    char a = Serial.read();
    if( a=='1' ){
      led_flag = 1;
      Serial.println("아가씨 또 핸드폰하는거에요?");
    }
    else if( a=='2'){
      led_flag = 0;
      Serial.println("야레야레");
    }
  }

  // flag상태에 따라 led 키고 끄기
  if (led_flag == 1)
    ledcWrite(ledChannel, m_value);    //아두이노의 PWM 용 API 로 analogWrite() 는 esp32 에서 동작하지 않는다.
  else
    ledcWrite(ledChannel, 0);


  // 온습도 정보 출력
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }



  delay(100);
}
