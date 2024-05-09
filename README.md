# IoT_mini_project_bundle
Arduino ESP32, MQTT를 활용한 IoT 미니 프로젝트 모음입니다. 

## IoT_smart_mood_lamp
스마트 무드등 미니 프로젝트입니다.<br>
ON/OFF 기능, 밝기 조절 기능, 사용자 원격 작동 기능, 온습도 측정 기능 <br>

[![Video Label](http://img.youtube.com/vi/PPARpDz4DLA/0.jpg)](https://youtu.be/PPARpDz4DLA)
<h4>requirement</h4>
ESP32, Arduino IDE, need to install library(DHT_Unified_Sensor) <br>

<h4>pin MAP</h4>
<img src = https://github.com/woodong11/IoT_mini_project_bundle/assets/91379630/a336265b-c246-4391-a261-6edc4a5f63f4>


LED<br>
+: GPIO 17, -: 220옴 저항 → GND<br>
버튼<br>
GPIO 18, 10k옴 저항 → 3,3V, GND<br>
가변저항<br>
왼쪽 : 3.3V, 가운데 : ADC0, 오른쪽 : GND<br>
DHT11S<br>
GPIO 13, V : 3.3V, G : GND<br>

