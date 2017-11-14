#include <Arduino.h> 

#include "debug.h" 
#include "wifi.h"
#include "wifiAP.h"
#include "storage.h" 
#include "webserver.h"

WifiConnection* wifi;           // wifi connection
WifiAP* ap;                     // wifi access point
Database* database;             
bool dbConfigured = false;      

void setup() {
  database = new Database(); 
  dbConfigured = database->isConfigured();
  
  if (dbConfigured){
    //we already have wifi config; start wifi normally
    wifi = new WifiConnection(database->getWifiSsid(), database->getWifiPasswd()); 
    wifi->begin(); 
    wifi->connect();
  }
  else {
    ap = new WifiAP(); 
    ap->start(); 
  }
}

void loop() {
  if (!dbConfigured) {
    
  }
  else {
    
  }
}

