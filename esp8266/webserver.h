
#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <DNSServer.h>

#include "debug.h" 
#include "wifiDTO.h" 
#include "storage.h" 


/****************************************
 * SetDataCallback
 * ----------------
 * Callback to be called when new data has been written.
 */
class SetDataCallback
{ 
  public:
    SetDataCallback() { }
    bool dataSet(); 
};

bool getReceived = false;
bool setReceived = false; 
bool pingReceived = false; 

/****************************************
 * WebServer
 * ----------
 * Listens on port 80 for HTTP requests. 
 */
class WebServer
{
  private: 
    ESP8266WebServer* _server;
    Database* _database;
    SetDataCallback* _setCallback;
    
  public:
    WebServer(Database* database, SetDataCallback* setCallback); 
    
    void start(); 
    void listen();

  private: 
    void handleGet(); 
    void handleSet(); 
    void handlePing();
};
/****************************************/


// ************************************************************************************
// constructor 
//  
// args
//  database: pointer to database instance 
//  setCallback: callback to be called after new data written 
// 
WebServer::WebServer(Database* database, SetDataCallback* setCallback)
{
  this->_server = new ESP8266WebServer(80); 
  this->_database = database;
  this->_setCallback = setCallback;
}

// ************************************************************************************
// starts listening for requests 
// 
void WebServer::start() {  
  DEBUG_PRINTLN("starting web server"); 
  
  this->_server->on("/get", []() {
    DEBUG_PRINTLN("received get");
    getReceived = true;
  });
  this->_server->on("/set", []() {
    DEBUG_PRINTLN("received set");
    setReceived = true;
  });
  this->_server->on("/ping", []() {
    DEBUG_PRINTLN("received ping");
    pingReceived = true;
  });
  this->_server->begin();
}

// ************************************************************************************
// to be called from loop() to handle incoming requests (if any) 
// 
void WebServer::listen() {  
  this->_server->handleClient();

  if (getReceived){
    getReceived  = false;
    this->handleGet();
  }
  if (setReceived){
    setReceived  = false;
    this->handleSet(); 
  }
  if (pingReceived) {
    pingReceived  = false;
    this->handlePing(); 
  }
}

//TODO: handle these callbacks better 
// ************************************************************************************
// handles the /get request 
// 
void WebServer::handleGet() {
  char buffer[512]; 
  WifiDTO dto(this->_database->getWifiSsid(), this->_database->getWifiPasswd(), WiFi.localIP());
  this->_server->send(200, "text/json", dto.toJson(buffer));
}

// ************************************************************************************
// handles the /ping request 
//  
void WebServer::handlePing() {
  DEBUG_PRINTLN("handling ping");
  this->_server->send(200, "text/json", "{}");
}

// ************************************************************************************
// handles the /set request 
//
void WebServer::handleSet() {
  String ssid = this->_server->arg("ssid");
  String passwd = this->_server->arg("password");

  this->_database->setWifiData(ssid.c_str(), passwd.c_str()); 
  
  if (this->_setCallback->dataSet()){
    WifiDTO dto(this->_database->getWifiSsid(), this->_database->getWifiPasswd(), WiFi.localIP());
  }
}

#endif
