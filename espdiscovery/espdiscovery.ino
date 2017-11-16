#include <Arduino.h> 

#include "debug.h" 
#include "wifi.h"
#include "wifiAP.h"
#include "storage.h" 
#include "webserver.h"

#define MODE_NORMAL 1
#define MODE_SETUP  0

WifiConnection* wifi;           // wifi connection
WifiAP* ap;                     // wifi access point
Database* database;             // EEPROM db
WebServer* webServer;           // web server

bool dbConfigured = false; 
byte progMode = MODE_NORMAL;

void setup() {
  database = new Database(); 
  dbConfigured = database->isConfigured();
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
  }
}

void loop() {
  if (progMode == MODE_NORMAL){
    
  }
  else {
    
  }
}

void enterSetupMode()
{
  progMode = MODE_SETUP;
  ap = new WifiAP(); 
  ap->start(); 
}

