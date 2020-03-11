#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <FirebaseError.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseHttpClient.h>
#include <FirebaseArduino.h>
#include <Firebase.h>


#define FIREBASE_HOST "agriculture-6078b.firebaseio.com"
#define FIREBASE_AUTH "OGhs4buORjQMoGb8mZ3CRu9iX4S5vFvh5mwqHN0e"
#define WIFI_SSID "realme 5"
#define WIFI_PASSWORD "rohit@233$$$"

String name;
String sMoisture;
int moisture = 0;
int dataM;
char r;

SoftwareSerial s1(D7,D8);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 s1.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    Serial.println();
    Serial.print("Connected:");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
  name = String("Rohit");
  Firebase.setString("name", name);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
 //  dataM = Serial.read();
  //  delay(1000);
  //  r=Serial.read();
    //sMoisture = sMoisture + dataM;
   // Serial.print(dataM);
   // Serial.println("");
  //  Serial.print(r);
 //   Serial.println("");
    //if (dataM) {
     // String temp = getValue(sMoisture, ',', 0);
      moisture = sMoisture.toInt();
      Firebase.setString("soilmoisture", String(dataM));

      sMoisture = "";
      moisture = 0;
  //  }

   StaticJsonBuffer<1000> jsonBuffer;
   JsonObject& root=jsonBuffer.parseObject(Serial);
   if(root == JsonObject::invalid())
   return;
  int m=root["moisture"];
  Serial.print(m);
   Serial.println("");
   int rain=root["rainWater"];
   Serial.print(rain);
   Serial.println("");
  
    delay(10000);
  }


}
