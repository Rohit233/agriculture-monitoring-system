#include <ArduinoJson.h>

#include <DHT_U.h>
#include <DHT.h>


#include <SoftwareSerial.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
int mValue=0;
int rainWater;
String value;
char t='w';
SoftwareSerial nodemcu(2,3); 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
nodemcu.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
dht.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root=jsonBuffer.createObject();
   Serial.print("Humidity: ");
   Serial.print(dht.readHumidity());
   Serial.print("%");
   Serial.println("temperature: ");
   Serial.print(dht.readTemperature());
    rainWater=analogRead(A1);
    Serial.print(rainWater);
   // moisture

  

     if(nodemcu.available()==0){
       mValue=analogRead(A0);
   mValue=map(mValue,721,10,0,100);
   value=value+mValue+",";
   Serial.println("");
   Serial.print("moisure:");
   Serial.print(mValue);
   Serial.print("% ");
   Serial.println("");
   Serial.print(value+"  "+analogRead(A0));
           //nodemcu.write(mValue); 
           //delay(1000);
         //  if(rainWater<400){
        //   nodemcu.write(1);
        //   }
       //    else{
       //     nodemcu.write(0);
      //      }
        nodemcu.write(1);
       root["moisture"]=mValue;
       root["rainWater"]=rainWater;
       root.printTo(nodemcu);

            
           delay(10000); 
           value="";    
      }

   
}
