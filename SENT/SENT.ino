#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>                                                                                                                                           
//1. Change the following info
#define FIREBASE_HOST "https://finalxsmax32promaxandroid-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "E5yCtJXtthBcxBpeIsjFtgdsAYoLGaXRXvPSgY6y"      

#define WIFI_SSID "Galaxy A90"                                            
#define WIFI_PASSWORD "13082004"     // Khai báo chân A0 để đọc dữ liệu từ cảm biến
#define ledr D4
#define ledy D2
DHT dht(DHTPIN, DHTTYPE);                                                     

FirebaseData dulieuH;  //giao tiếp với cloud cần tạo qua bien tu dat
FirebaseData dulieuT;  //giao tiếp với cloud cần tạo qua bien tu dat
FirebaseData mangData;  //giao tiếp với cloud cần tạo qua bien tu dat
void setup() {
  Serial.begin(115200);
  pinMode(ledr, OUTPUT);
  pinMode(ledy, OUTPUT);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // wifi bắt đầu chạy                                
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                          
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                            
  dht.begin();
}                                                       
void loop() {  
                                     
  if (isnan(h) || isnan(t)) {                                        
    Serial.println(F("lỗi"));                                               
  delay(500);
  if (t > 33) {
    digitalWrite(D2, 1);
    digitalWrite(ledr,1);
    digitalWrite(ledy,0);
  }
  else {
    digitalWrite(D2 ,0);
    digitalWrite(ledr, 0);
    digitalWrite(ledy, 1);
  }
  Firebase.setString(dulieuH, "/DHT11/Humidity", h);
  Firebase.setString(dulieuT, "/DHT11/Temperature", t);                          
}