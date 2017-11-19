
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
 * WifiAP
 * ------
 * opens up a wifi access point, and listens on it for requests. 
 */
class WifiAP
{
  private: 
    DNSServer _dns;
    
  public:
    WifiAP(); 
    
    void begin(); 
    void end(); //TODO: implement
    void listen();
};
/****************************************/


// ************************************************************************************
// constructor 
// 
WifiAP::WifiAP()
{
}

// ************************************************************************************
// initializes this instance; prepares it for use 
// 
void WifiAP::begin() {  
   
  static char ssid[12];
  sprintf(ssid, "IoThing %02d", ESP.getChipId() % 100);
  DEBUG_PRINTLN("Starting AP"); 
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid);
  delay(100);
  DEBUG_PRINTLN(ip.toString().c_str()); 

  //set all DNS to redirect to here
  _dns.setErrorReplyCode(DNSReplyCode::NoError);
  _dns.start(53, "*", ip);
}

// ************************************************************************************
// to be called from loop() to handle incoming requests (if any) 
// 
void WifiAP::listen(){
  this->_dns.processNextRequest();
}

#endif
