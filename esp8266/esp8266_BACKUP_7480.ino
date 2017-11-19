#include <Arduino.h> 

#include "debug.h" 
#include "blink.h" 
#include "wifi.h"
#include "wifiAP.h"
#include "storage.h" 
#include "webserver.h"
#include "udp.h"

//normal mode and setup mode
#define MODE_NORMAL       1
#define MODE_SETUP        0

//listen on UDP port for discovery requests
#define UDP_PORT          8021

//if set incorrectly, serial output will not be visible 
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
// runs once, on power up of the chip. 
// 
void setup() {
  Serial.begin(SERIAL_BAUD_RATE); 

<<<<<<< HEAD
  //initialize EEPROM database
=======
  LED::begin();
  LED::blink(10); 
  
>>>>>>> e825306974e0def2b9e03af7dea6082ce3db5bbc
  database = new Database(); 
  database->begin(); 

  //is DB set up (has data ever been written to it?) 
  dbConfigured = database->isConfigured();

  //TODO: remove this 
  if (!dbConfigured){
    database->setWifiData("mina", "HappyTime");
    dbConfigured = database->isConfigured();
  }

  //what's in the database?
  if (dbConfigured) {
    DEBUG_PRINTLN("wifi data:");
    DEBUG_PRINTLN(database->getWifiSsid());
    DEBUG_PRINTLN(database->getWifiPasswd());
  }

  //instantiate web server
  webServer = new WebServer(database, setCallback);

  //instantiate AP wifi
  ap = new WifiAP(); 

  //instantiate UDP listener
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
    //otherwise, enter normal mode 
    enterNormalMode();
  }
}

// ************************************************************************************
// repeats continually.  
// 
void loop() {
  //in normal mode, we need to handle UDP discovery requests
  if (progMode == MODE_NORMAL){
    if (udp)
      udp->listen();
  } 
  //in setup mode, we need to listen on AP 
  else {
    if (ap)
      ap->listen();
  }

  //in both modes, we need to listen on web server port
  if (webServer)
    webServer->listen();
}

// ************************************************************************************
// initialize setup mode, in which requests can come in on the wifi AP. 
// 
void enterSetupMode()
{
  DEBUG_PRINTLN("entering setup mode...");
  progMode = MODE_SETUP;
  ap->begin(); 
  webServer->start();
}

// ************************************************************************************
// initialize normal mode, in which requests can come in via web request or UDP. 
// 
void enterNormalMode()
{
  DEBUG_PRINTLN("entering normal mode...");
  progMode = MODE_NORMAL;
  webServer->start();
  udp->begin(); 
}

// ************************************************************************************
// callback called after new wifi data has been written to the database. 
// 
// returns: true on successful connection 
// 
bool SetDataCallback::dataSet(){
  if (wifi->tryConnect()){
    enterNormalMode(); 
    return true;
  }
  return false;
}

