
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
 *  
 */
class WifiAP
{
  private: 
    DNSServer _dns;
    
  public:
    WifiAP(); 
    
    void start(); 
};
/****************************************/


// ************************************************************************************
// constructor 
//  
WifiAP::WifiAP()
{
}

void WifiAP::start() {  
  
  static char ssid[12];
  sprintf(ssid, "IoThing %02d", ESP.getChipId() % 100);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid);
  delay(100);

  //set all DNS to redirect to here
  _dns.setErrorReplyCode(DNSReplyCode::NoError);
  _dns.start(53, "*", ip);
}

#endif
