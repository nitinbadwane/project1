/*------Esp8266-----*/

//FirebaseESP32.h must be included before ESP8266WiFi.h
//#include "FirebaseESP32.h"  // Install Firebase ESP32 library
//#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
//#include <WiFi.h> // for esp32
#include <SoftwareSerial.h>
SoftwareSerial s(D7,D8); // RX & TX

////////////3 code is used for upload code through OTA means WIFI/////////////
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h> 
///////////////////////
 
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <ArduinoJson.h> // https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries (use the correct version)
#include <StreamString.h>
#include <StringSplitter.h>
#include "Arduino.h"
#include "PCF8574.h"

//#define FIREBASE_HOST "smart-home-automation-cecfd.firebaseio.com" 
//#define FIREBASE_AUTH "TCbiEuaQttVHu5BgxWdE7TsZKhiIcAz0T1Nmmbe2"
#define WIFI_SSID "ASUS_X00TD"     //ASUS_X00TD  //jio dongle SSID//JioFi3_5C4B43
#define WIFI_PASSWORD "Nitin4444"  //Nitin4444  pass//mzf98rk1xm


//code for sinric server
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

void Serialvalue(char a);
void received_data();
static char data1;

// Set i2c address
PCF8574 i2c1(0x21);
PCF8574 i2c2(0x22);


/////////////// Button1////////////

 int switchState1 = 0; // actual read value from pin1
static  int oldSwitchState1 = 0; // last read value from pin1
 int lightsOn1 = 0; // is the switch on = 1 or of off =0
 
/////////////// Button2/////////////
 int switchState2 = 0; // actual read value from pin2
 static int oldSwitchState2 = 0; // last read value from pin2
 int lightsOn2 = 0; // is the switch on = 1 or of off =0

/////////////// Button3/////////////
 int switchState3 = 0; // actual read value from pin3
static int oldSwitchState3 = 0; // last read value from pin3
 int lightsOn3 = 0; // is the switch on = 1 or of off =0

/////////////// Button4/////////////
 int switchState4 = 0; // actual read value from pin4
static int oldSwitchState4 = 0; // last read value from pin4
 int lightsOn4 = 0; // is the switch on = 1 or of off =0

/////////////// Button5/////////////
 int switchState5 = 0; // actual read value from pin5
static int oldSwitchState5 = 0; // last read value from pin5
 int lightsOn5 = 0; // is the switch on = 1 or of off =0

/////////////// Button6/////////////
 int switchState6 = 0; // actual read value from pin6
static int oldSwitchState6 = 0; // last read value from pin6
 int lightsOn6 = 0; // is the switch on = 1 or of off =0

/////////////// Button7/////////////
 int switchState7 = 0; // actual read value from pin7
static int oldSwitchState7 = 0; // last read value from pin7
 int lightsOn7 = 0; // is the switch on = 1 or of off =0
 
/////////////// Button8/////////////
 int switchState8 = 0; // actual read value from pin8
static int oldSwitchState8 = 0; // last read value from pin8
 int lightsOn8 = 0; // is the switch on = 1 or of off =0

void allbutton()
{

   /////////////// Button1///////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
    switchState1 = i2c1.digitalRead(P0); // read the pushButton State
   if (switchState1 != oldSwitchState1) { //catch change
         delay(200);
     oldSwitchState1 = switchState1;
      if (switchState1 == HIGH)
     {
          // toggle
          lightsOn1 = !lightsOn1;// Toggle Button On Off 
            
      }
    
   if(lightsOn1)
   {
       
       //digitalWrite(LED_BUILTIN , LOW); // set the LED on
       i2c2.digitalWrite(0,LOW);
       data1 = 'A';
       Serialvalue(data1);
       setPowerStateOnServer("5fb9bc96aedf812fa2c11f7d","ON");
        
    } 
  else
   {   
       //digitalWrite(LED_BUILTIN,  HIGH); // set the LED off
       i2c2.digitalWrite(0,HIGH);
       data1 = 'a';
       Serialvalue(data1);
       setPowerStateOnServer("5fb9bc96aedf812fa2c11f7d","OFF");
       // delay(45);
        
    }

  }
    
    /////////////// Button2/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState2 = i2c1.digitalRead(P1); // read the pushButton State
   if (switchState2 != oldSwitchState2) // catch change
   {
       delay(200);
     oldSwitchState2 = switchState2;
      if (switchState2 == HIGH)
     {
          // toggle
          lightsOn2 = !lightsOn2;// Toggle Button On Off 
      }
 
   if(lightsOn2)
    {
        //digitalWrite(LED_BUILTIN , HIGH); // set the LED on
        i2c2.digitalWrite(1 , LOW);
        data1 = 'B';
        Serialvalue(data1);
    } 
  else
   { 
       // digitalWrite(LED_BUILTIN,  LOW); // set the LED off
        i2c2.digitalWrite(1 , HIGH);
        data1 = 'b';
        Serialvalue(data1);
   }

 }
   /////////////// Button3/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState3 = i2c1.digitalRead(P2); // read the pushButton State
   if (switchState3 != oldSwitchState3) // catch change
   {
        delay(200);
     oldSwitchState3 = switchState3;
      if (switchState1 == HIGH)
     {
          // toggle
          lightsOn3 = !lightsOn3;// Toggle Button On Off 
      }

   if(lightsOn3)
   {
      //  digitalWrite(LED_BUILTIN , HIGH); // set the LED on
          i2c2.digitalWrite(2 , HIGH);
   } 
  else
   { 
       //  digitalWrite(LED_BUILTIN,  LOW); // set the LED off
           i2c2.digitalWrite(2  , LOW);
   }
  
 }
    /////////////// Button4/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState4 = i2c1.digitalRead(P3); // read the pushButton State
   if (switchState4 != oldSwitchState4) // catch change
   {
        delay(200);
     oldSwitchState4 = switchState4;
      if (switchState4 == HIGH)
     {
          // toggle
          lightsOn4 = !lightsOn4;// Toggle Button On Off 
      }
        
   if(lightsOn4)
   {
        // digitalWrite(LED_BUILTIN , HIGH); // set the LED on
           i2c2.digitalWrite(3 , HIGH);
   } 
  else
   { 
        // digitalWrite(LED_BUILTIN,  LOW); // set the LED off
         i2c2.digitalWrite(3 , LOW);
   }
        
 }
    /////////////// Button5/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState5 = i2c1.digitalRead(P4); // read the pushButton State
   if (switchState5 != oldSwitchState5) // catch change
   {
        delay(200);
     oldSwitchState5 = switchState5;
      if (switchState5 == HIGH)
     {
          // toggle
          lightsOn5 = !lightsOn5;// Toggle Button On Off 
      }
 
   if(lightsOn5)
   {
       // digitalWrite(LED_BUILTIN , HIGH); // set the LED on
          i2c2.digitalWrite(4 , HIGH);
   } 
  else
   { 
       //  digitalWrite(LED_BUILTIN,  LOW); // set the LED off
          i2c2.digitalWrite(4  , LOW);
   }

 }
   /////////////// Button6/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState6 = i2c1.digitalRead(P5); // read the pushButton State
   if (switchState6 != oldSwitchState6) // catch change
   {
        delay(200);
     oldSwitchState6 = switchState6;
      if (switchState6 == HIGH)
     {
          // toggle
          lightsOn6 = !lightsOn6;// Toggle Button On Off 
      }
        
   if(lightsOn6)
   {
        // digitalWrite(LED_BUILTIN , HIGH); // set the LED on
          i2c2.digitalWrite(5 , HIGH);
   } 
  else
   { 
        // digitalWrite(LED_BUILTIN,  LOW); // set the LED off
          i2c2.digitalWrite(6 , LOW);
   }
        
 }
   /////////////// Button7/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState7 = i2c1.digitalRead(P6); // read the pushButton State
   if (switchState7 != oldSwitchState7) // catch change
   {
        delay(200);
     oldSwitchState7 = switchState7;
      if (switchState7 == HIGH)
     {
          // toggle
          lightsOn7 = !lightsOn7;// Toggle Button On Off 
      }
  
   if(lightsOn7)
   {
        // digitalWrite(LED_BUILTIN , HIGH); // set the LED on
         i2c2.digitalWrite(7 , HIGH);
   } 
  else
   { 
        // digitalWrite(LED_BUILTIN,  LOW); // set the LED off
         i2c2.digitalWrite(7 , LOW);
   }

}
   /////////////// Button8/////////////
    
   //int p0 = i2c1.digitalRead(P0);// Read Pin P0
  
    switchState8 = i2c1.digitalRead(P7); // read the pushButton State
   if (switchState8 != oldSwitchState8) // catch change
    {
        delay(200);
     oldSwitchState8 = switchState8;
      if (switchState8 == HIGH)
     {
          // toggle
          lightsOn8 = !lightsOn8;// Toggle Button On Off 
      }
  
   if(lightsOn8)
    {
          //digitalWrite(LED_BUILTIN , HIGH); // set the LED on
          i2c2.digitalWrite(6  , HIGH);
    } 
  else
   { 
          //digitalWrite(LED_BUILTIN,  LOW); // set the LED off
          i2c2.digitalWrite(6 , LOW);
    } 
        
  }
    
}

//sinric auth kay
#define MyApiKey "e8d564d5-61b3-42b5-b5b8-1e88e8a53ca3" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard

#define HEARTBEAT_INTERVAL 300000 // 1 Minutes

//#define v1 "{"on":true}"

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == "5fb9bc96aedf812fa2c11f7d") // Device ID of 1 device
  {  
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(CFLLight,LOW);
     data1 = 'A';
     Serialvalue(data1);
     i2c2.digitalWrite(0,LOW);// LED1 ON
  } 
  else if (deviceId == "5fb9c422aedf812fa2c12032") // Device ID of 2 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(CFlnightbulb,LOW);
     data1 = 'B';
     Serialvalue(data1);
     i2c2.digitalWrite(1,LOW);// LED2 ON
  }
    else if (deviceId == "5fb9bc75aedf812fa2c11f79") // Device ID of 3 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(TV,LOW);
     data1 = 'C';
     Serialvalue(data1);
     i2c2.digitalWrite(2,LOW);// LED3 ON
  }
   else if (deviceId == "5fbc9322aedf812fa2c16118") // Device ID of 4 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(CeilingFan,LOW);
     data1 = 'D';
     Serialvalue(data1);
     i2c2.digitalWrite(3,LOW);// LED4 ON
  }
   else if (deviceId == "5fbb560daedf812fa2c14568") // Device ID of 5 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    // i2c1.digitalWrite(CFLLight1,LOW);
     data1 = 'E';
     Serialvalue(data1);
     i2c2.digitalWrite(4,LOW);// LED5 ON
  }
   else if (deviceId == "5fbb5667aedf812fa2c1456e") // Device ID of 6 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(CFlnightbulb1,LOW);
      data1 = 'F';
     Serialvalue(data1);
     i2c2.digitalWrite(5,LOW);// LED6 ON
  }
   else if (deviceId == "5fb9ebdaaedf812fa2c1237e") // Device ID of 7 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(UtilityScoketforCharger,LOW);
      data1 = 'G';
     Serialvalue(data1);
     i2c2.digitalWrite(6,LOW);// LED7 ON
  }
   else if (deviceId == "5fbc93a0aedf812fa2c1612e") // Device ID of 8 device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    //i2c1.digitalWrite(CeilingFan1,LOW);
      data1 = 'H';
     Serialvalue(data1);
     i2c2.digitalWrite(7,LOW);// LED8 ON
  }
  
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);    
  }     
    
}

// off devices
void turnOff(String deviceId) {
   if (deviceId == "5fb9bc96aedf812fa2c11f7d") // Device ID of 1 device
   {  
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(CFLLight,HIGH);
     data1 = 'a';
     Serialvalue(data1);
     i2c2.digitalWrite(0,HIGH);// LED1 ON
   }
   else if (deviceId == "5fb9c422aedf812fa2c12032") // Device ID of 2 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(CFlnightbulb,HIGH);
        data1 = 'b';
     Serialvalue(data1);
     i2c2.digitalWrite(1,HIGH);// LED2 ON
  }
  else if (deviceId == "5fb9bc75aedf812fa2c11f79") // Device ID of 3 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(TV,HIGH);
       data1 = 'c';
     Serialvalue(data1);
     i2c2.digitalWrite(2,HIGH);// LED3 ON
  }
  else if (deviceId == "5fbc9322aedf812fa2c16118") // Device ID of 4 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(CeilingFan,HIGH);
       data1 = 'd';
     Serialvalue(data1);
     i2c2.digitalWrite(3,HIGH);// LED4 ON
  }
  else if (deviceId == "5fbb560daedf812fa2c14568") // Device ID of 5 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(CFLLight1,HIGH);
       data1 = 'e';
     Serialvalue(data1);
     i2c2.digitalWrite(4,HIGH);// LED5 ON
  }
  else if (deviceId == "5fbb5667aedf812fa2c1456e") // Device ID of 6 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(CFlnightbulb1,HIGH);
       data1 = 'f';
     Serialvalue(data1);
      i2c2.digitalWrite(5,HIGH);// LED6 ON
  }
  else if (deviceId == "5fb9ebdaaedf812fa2c1237e") // Device ID of 7 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     //i2c1.digitalWrite(UtilityScoketforCharger,HIGH);
       data1 = 'g';
     Serialvalue(data1);
      i2c2.digitalWrite(6,HIGH);// LED7 ON
  }
  else if (deviceId == "5fbc93a0aedf812fa2c1612e") // Device ID of 8 device
   { 
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
    //i2c1.digitalWrite(CeilingFan1,HIGH);
       data1 = 'h';
      Serialvalue(data1);
       i2c2.digitalWrite(7,HIGH);// LED8 ON
  }
    
  else {
              Serial.print("Turn off for unknown device id: ");
              Serial.println(deviceId);    
     }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");        
            
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
       
#if ARDUINOJSON_VERSION_MAJOR == 5
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
        DynamicJsonDocument json(1024);
        deserializeJson(json, (char*) payload);      
#endif        
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);
            } 
            else
            {
                turnOff(deviceId);
            }
        }
       else if(action == "action.devices.commands.OnOff")
       {   // Switch or Light
            String value = json ["value"];
            value.remove(0,6); // {"on":true} this string convert to "true"
            value.remove(value.length()-1,value.length());
            Serial.println(value);
            if(value == "true")
            {
                turnOn(deviceId);
            } 
            else
            {
                turnOff(deviceId);
            }
        }
         
        else if (action == "SetTargetTemperature") {
            String deviceId = json ["deviceId"];     
            String action = json ["action"];
            String value = json ["value"];
        }
        else if (action == "test") {
            Serial.println("[WSc] received test command from sinric.com");
        }
        
        else if(action == "AdjustBrightness") {
             // adjustBrightness
             String value = json ["value"];
             Serial.println(value);
            // alexa, dim lights  ==>{"deviceId":"xxx","action":"AdjustBrightness","value":-25}
        }       
        else if(action == "SetBrightness") {
             String value = json ["value"];
             Serial.println(value);
           //alexa, set the lights to 50% ==> {"deviceId":"xx","action":"SetBrightness","value":50}
        }
        else if(action == "SetColor") {
             String value = json ["value"];
             Serial.println(value);
           //alexa, set the lights to red ==> {"deviceId":"xx","action":"SetColor","value":{"hue":0,"saturation":1,"brightness":1}}
        }
        else if(action == "IncreaseColorTemperature") {
           //alexa, set the lights softer ==> {"deviceId":"xxx","action":"IncreaseColorTemperature"}
        }
        else if(action == "IncreaseColorTemperature") {
           //alexa, set the lights softer ==> {"deviceId":"xxx","action":"IncreaseColorTemperature"}
        }
        else if(action == "SetColorTemperature") {
             String value = json ["value"];
             Serial.println(value);
           //alexa, set the lights softer ==> {"deviceId":"xxx","action":"SetColorTemperature","value":2200}
        }

        
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
    
}

//[WSc] get text: {"deviceId":"5fb9c422aedf812fa2c12032","action":"action.devices.commands.OnOff","value":{"on":false}} get request from GOOGLE HOME
//[WSc] get text: {"deviceId":"5fb9bc96aedf812fa2c11f7d","action":"setPowerState","value":"ON"} get request from ALEXA


void setup()//////////Setup///////////
{
    
  WiFi.mode(WIFI_STA);
  Serial.begin(9600);
  s.begin(9600);
    
  for( int i=0;i<=7;i++)
    {
        i2c1.pinMode(i, INPUT);
        i2c2.pinMode(i,OUTPUT);
    }
    

   //i2c lets begin
    i2c1.begin();
    i2c2.begin();
 
  WiFiMulti.addAP(WIFI_SSID , WIFI_PASSWORD);
   
   pinMode(LED_BUILTIN,OUTPUT);
   digitalWrite(LED_BUILTIN,HIGH);
    for(int i=0;i<7;i++)
        {
           i2c2.digitalWrite(i,HIGH);
        }
 //Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
       delay(200);
      allbutton();
     }
    
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

// Code for sinric server
  webSocket.begin("iot.sinric.com", 80, "/");

  
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000); 
  
  
////////////This code is used for upload code through OTA means WIFI///////////////////////////

 // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
///////////////////////////////////////////////////////////////////////////////////////////
    
}

//////////////////////////Feedback status show/////////////////////////////

// If you are going to use a push button to on/off the switch manually, use this function to update the status on the server
// so it will reflect on Alexa app.
// eg: setPowerStateOnServer("deviceid", "ON")

// Call ONLY If status changed. DO NOT CALL THIS IN loop() and overload the server. 

void setPowerStateOnServer(String deviceId, String value) {
#if ARDUINOJSON_VERSION_MAJOR == 5
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  DynamicJsonDocument root(1024);
#endif        

  root["deviceId"] = deviceId;
  root["action"] = "setPowerState";
  root["value"] = value;
  StreamString databuf;
#if ARDUINOJSON_VERSION_MAJOR == 5
  root.printTo(databuf);
#endif
#if ARDUINOJSON_VERSION_MAJOR == 6        
  serializeJson(root, databuf);
#endif  
  webSocket.sendTXT(databuf);
}


void loop()
{
  
////////////This code is used for upload code through OTA means WIFI///////////
   ArduinoOTA.handle();
/////////////////////////
   //delay(200);
   allbutton();
   received_data();
   //Serialvalue('A');
   webSocket.loop();
  
   if(isConnected) {
      uint64_t now = millis();
      
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
       } 
    } 
 }
//////////////Software Serial communication////////////// 

//////////////Send data to esp32////////////////////////
void Serialvalue(char a)
 {
    s.write("s");
    if(s.available()>0)
    {
        s.write(a);
        Serial.println(a);
       //root.printTo(s);
    }
                                                                                                                                                                             
 }
//////////////Received data from esp32////////////////////////
void received_data()
{
  //-------------Received data from  esp32------------------//
    s.write("s");
   if (s.available()>0)
   {  
     char data1 = s.read();
     Serial.println(data1);
    //bluehandle(data);
      switch(data1) // Switch read data from bluetooth..
      {
    
         case 'A':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(0,LOW);
                      setPowerStateOnServer("5fb9bc96aedf812fa2c11f7d","ON");// Device ID of 1 device
                      break;
              
         case 'a':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(0,HIGH);
                      setPowerStateOnServer("5fb9bc96aedf812fa2c11f7d","OFF");
                      break;  
                      
         case 'B':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(1,LOW);
                      setPowerStateOnServer("5fb9c422aedf812fa2c12032","ON");// Device ID of 2 device
                      break;
              
         case 'b':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(1,HIGH);
                      setPowerStateOnServer("5fb9c422aedf812fa2c12032","OFF");
                      break;  

         case 'C':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(2,LOW);
                      setPowerStateOnServer("5fb9bc75aedf812fa2c11f79","ON");// Device ID of 3 device
                      break;
              
         case 'c':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(2,HIGH);
                      setPowerStateOnServer("5fb9bc75aedf812fa2c11f79","OFF");
                      break;    
                       
         case 'D':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(3,LOW);
                      setPowerStateOnServer("5fbc9322aedf812fa2c16118","ON");// Device ID of 4 device
                      break;
              
         case 'd':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(3,HIGH);
                      setPowerStateOnServer("5fbc9322aedf812fa2c16118","OFF");
                      break;

         case 'E':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(4,LOW);
                      setPowerStateOnServer("5fbb560daedf812fa2c14568","ON");// Device ID of 5 device
                      break;
              
         case 'e':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(4,HIGH);
                      setPowerStateOnServer("5fbb560daedf812fa2c14568","OFF");
                      break;                                                  

         case 'F':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(5,LOW);
                      setPowerStateOnServer("5fbb5667aedf812fa2c1456e","ON");// Device ID of 6 device
                      break;
              
         case 'f':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(5,HIGH);
                      setPowerStateOnServer("5fbb5667aedf812fa2c1456e","OFF");
                      break;     

         case 'G':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(6,LOW);
                      setPowerStateOnServer("5fb9ebdaaedf812fa2c1237e","ON");// Device ID of 7 device
                      break;
              
         case 'g':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(6,HIGH);
                      setPowerStateOnServer("5fb9ebdaaedf812fa2c1237e","OFF");
                      break;   

         case 'H':  //digitalWrite(CFLLight,LOW);
                      i2c2.digitalWrite(7,LOW);
                      setPowerStateOnServer("5fbc93a0aedf812fa2c1612e","ON");// Device ID of 8 device
                      break;
                      
         case 'h':   //digitalWrite(CFLLight,HIGH);
                      i2c2.digitalWrite(7,HIGH);
                      setPowerStateOnServer("5fbc93a0aedf812fa2c1612e","OFF");
                      break;
                                                                                                                         
         
      }    
   }
}
