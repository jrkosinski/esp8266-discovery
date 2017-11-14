
#ifndef __WIFI_AP_H__
#define __WIFI_AP_H__

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include "debug.h" 


const IPAddress ip(192, 168, 4, 1);  
const IPAddress netmask(255, 255, 255, 0);

/****************************************
 * WebServer
 * ----------
 *  
 */
class WebServer
{
  private: 
    ESP8266WebServer* _server;
    
  public:
    WebServer(); 
    
    void start(); 
    void listen();

  private: 
    void handleRequest(); 
};
/****************************************/


// ************************************************************************************
// constructor 
//  
WebServer::WebServer()
{
  this->_server = new ESP8266WebServer(80); 
}

void WebServer::start() {  
  this->_server.on("/", this->handleRequest); 
  this->_server.begin();
}

void WebServer::handleRequest() {
  
}

#endif
