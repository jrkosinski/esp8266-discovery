#include <Arduino.h> 

#include "debug.h" 
#include "wifi.h"
#include "wifiAP.h"
#include "storage.h" 
#include "webserver.h"
#include "udp.h"

#define MODE_NORMAL       1
#define MODE_SETUP        0
#define UDP_PORT          8021
#define SERIAL_BAUD_RATE  9600

WifiConnection* wifi;           // wifi connection
WifiAP* ap;                     // wifi access point
Database* database;             // EEPROM db
WebServer* webServer;           // web server
SetDataCallback* setCallback;   // callback when new data's been received from client 
UdpServer* udp;                 // UDP server listener (for probing requests) 

bool dbConfigured = false; 
byte progMode = MODE_NORMAL;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE); 
  
  database = new Database(); 
  database->open(); 
  
  webServer = new WebServer(database, setCallback);
  dbConfigured = database->isConfigured();
  ap = new WifiAP(); 
  udp = new UdpServer(UDP_PORT);
  
  bool wifiConnected = false;
  
  if (dbConfigured){
    //we already have wifi config; start wifi normally
    wifi = new WifiConnection(database->getWifiSsid(), database->getWifiPasswd()); 

    //try to connect to wifi with existing info
    wifi->begin();
    wifiConnected = wifi->tryConnect();
  }

  //not connected yet; start AP (enter setup mode)
  if (!wifiConnected) {
    enterSetupMode();
  }
  else {
    enterNormalMode();
  }
}

void loop() {
  if (progMode == MODE_NORMAL){
    udp->listen();
  } 
  else {
    ap->listen();
  }
    
  webServer->listen();
}

void enterSetupMode()
{
  progMode = MODE_SETUP;
  ap->begin(); 
  webServer->start();
}

void enterNormalMode()
{
  progMode = MODE_NORMAL;
    webServer->start();
    udp->begin(); 
}

bool SetDataCallback::dataSet(){
  if (wifi->tryConnect()){
    enterNormalMode(); 
    return true;
  }
  return false;
}

