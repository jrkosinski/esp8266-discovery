
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
 * WebServer
 * ----------
 *  
 */
class WebServer
{
  private: 
    ESP8266WebServer* _server;
    Database* _database;
    
  public:
    WebServer(Database* database); 
    
    void start(); 
    void listen();

  private: 
    void handleGetData(); 
    void handleSetData(); 
};
/****************************************/


// ************************************************************************************
// constructor 
//  
WebServer::WebServer(Database* database)
{
  this->_server = new ESP8266WebServer(80); 
  this->_database = database;
}

void WebServer::start() {  
  this->_server->on("/getData", []() {
    //handleGetData();
  });
  this->_server->on("/getData", []() {
    //handleSetData();
  });
  this->_server->begin();
}

void WebServer::listen() {  
}

void WebServer::handleGetData() {
  char buffer[512]; 
  WifiDTO dto(this->_database->getWifiSsid(), this->_database->getWifiPasswd());
  this->_server->send(200, "text/json", dto.toJson(buffer));
}

void WebServer::handleSetData() {
  String ssid = this->_server->arg("ssid");
  String passwd = this->_server->arg("password");

  this->_database->setWifiData(ssid.c_str(), passwd.c_str()); 
  
  handleGetData();
}

#endif
