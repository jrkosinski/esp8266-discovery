
#ifndef __UPNP_H__
#define __UPNP_H__

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "debug.h" 

#define UDP_PACKET_SIZE 255; 

class UpnpServer 
{
  private: 
    uint32_t _port; 
    WiFiUDP _udp; 
    byte _buffer[UDP_PACKET_SIZE]; 
    
  public: 
    UpnpServer(uint32_t port);

    void begin(); 
    void end();
    void listen();
};


UpnpServer::UpnpServer(uint32_t port){
  this->_port = port;
}

void UpnpServer::begin(){
  this->_udp.begin(this->_port); 
}

void UpnpServer::end(){
  //TODO: implement
}

void UpnpServer::listen(){
  int cb = this->_udp.parsePacket();
  if (cb) {
    this->_udp.read(this->_buffer, UDP_PACKET_SIZE);
    String data = ""; 
    for(int i = 0; i < UDP_PACKET_SIZE; i++) {
      data += (char)this->_buffer[i];
    }
  }
}

#endif
