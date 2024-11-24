#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define fan1 D1
#define fan2 D2
#define lamp1 D3
#define lamp2 D4
#define lamp3 D5
#define spray D6
#define flame D8


#define WIFI_SSID "I'm in!"
#define WIFI_PASSWORD "connected"
#define API_KEY "AIzaSyDf2iP8oudhjY2fVBXh5n5QiO6vYxvxdBo"
#define DATABASE_URL "firesensor-25af9-default-rtdb.firebaseio.com/" 


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
bool Spray = false;
bool Fan1 = false;
bool Fan2 = false;
bool Lamp1 = false;
bool Lamp2 = false;
bool Lamp3 = false;



void setup() {
  // put your setup code here, to run once:
   

  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(lamp3, OUTPUT);
  pinMode(spray, OUTPUT);
  pinMode(flame, INPUT);
  Serial.begin(9600);
  digitalWrite(fan1, LOW);
  digitalWrite(fan2, LOW);
  digitalWrite(lamp1, LOW);
  digitalWrite(lamp2, LOW);
  digitalWrite(lamp3, LOW);
  digitalWrite(spray, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
   while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
   Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // put your main code here, to run repeatedly:

  int value = digitalRead(flame);



  if (Firebase.ready() && signupOK && (millis() -  sendDataPrevMillis > 1000 || sendDataPrevMillis == 0 )) {
    sendDataPrevMillis = millis();


    if (Firebase.RTDB.getBool(&fbdo, "Controls/lamp1")){
      if (fbdo.dataType() == "boolean"){
         Lamp1 = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Lamp1 + "(" + fbdo.dataType() + ")");
        digitalWrite(lamp1, Lamp1);
        
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.getBool(&fbdo, "Controls/lamp2")){
      if (fbdo.dataType() == "boolean"){
         Lamp2 = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Lamp2 + "(" + fbdo.dataType() + ")");
        digitalWrite(lamp2, Lamp2);
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }

     if (Firebase.RTDB.getBool(&fbdo, "Controls/lamp3")){
      if (fbdo.dataType() == "boolean"){
         Lamp3 = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Lamp3 + "(" + fbdo.dataType() + ")");
        digitalWrite(lamp3, Lamp3);
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }

     if (Firebase.RTDB.getBool(&fbdo, "Controls/fan1")){
      if (fbdo.dataType() == "boolean"){
         Fan1 = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Fan1 + "(" + fbdo.dataType() + ")");
        digitalWrite(fan1, Fan1);
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }

     if (Firebase.RTDB.getBool(&fbdo, "Controls/fan2")){
      if (fbdo.dataType() == "boolean"){
         Fan2 = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Fan2 + "(" + fbdo.dataType() + ")");
        digitalWrite(fan2, Fan2);
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }

     if (Firebase.RTDB.getBool(&fbdo, "Controls/spray")){
      if (fbdo.dataType() == "boolean"){
         Spray = fbdo.boolData();
        Serial.println("Seccess: " + fbdo.dataPath() + ": " + Spray + "(" + fbdo.dataType() + ")");
        digitalWrite(spray, Spray);
      }
    }
    else {
      Serial.println("FAILED: " + fbdo.errorReason());
    }
    
  
   if (Firebase.RTDB.setFloat(&fbdo, "SENSORS/1/flame", value   )){
      
         Serial.print("Flame Value: ");
       Serial.println(value);
      
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }



    Serial.print("");
    Serial.println("_______________________________________");

  }

}
