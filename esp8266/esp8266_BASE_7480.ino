#include <Arduino.h> 

#include "debug.h" 
#include "blink.h" 
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

// ************************************************************************************
void setup() {
  Serial.begin(SERIAL_BAUD_RATE); 

  LED::begin();
  LED::blink(3); 
  
  database = new Database(); 
  database->begin(); 
  
  dbConfigured = database->isConfigured();

  if (!dbConfigured){
    database->setWifiData("mina", "HappyTime");
    dbConfigured = database->isConfigured();
  }

  DEBUG_PRINTLN("wifi data:");
  DEBUG_PRINTLN(database->getWifiSsid());
  DEBUG_PRINTLN(database->getWifiPasswd());

  webServer = new WebServer(database, setCallback);
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

// ************************************************************************************
void loop() {
  if (progMode == MODE_NORMAL){
    if (udp)
      udp->listen();
  } 
  else {
    if (ap)
      ap->listen();
  }

  if (webServer)
    webServer->listen();
}

// ************************************************************************************
void enterSetupMode()
{
  DEBUG_PRINTLN("entering setup mode...");
  progMode = MODE_SETUP;
  ap->begin(); 
  webServer->start();
}

// ************************************************************************************
void enterNormalMode()
{
  DEBUG_PRINTLN("entering normal mode...");
  progMode = MODE_NORMAL;
  webServer->start();
  udp->begin(); 
}

// ************************************************************************************
bool SetDataCallback::dataSet(){
  if (wifi->tryConnect()){
    enterNormalMode(); 
    return true;
  }
  return false;
}

