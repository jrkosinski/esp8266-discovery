
#ifndef __UDP_H__
#define __UDP_H__

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "debug.h" 

#define UDP_PACKET_SIZE 255
#define UDP_SEARCH_PATTERN "*3*" //TODO: implement

class UdpServer 
{
  private: 
    uint32_t _port; 
    WiFiUDP _udp; 
    byte _buffer[UDP_PACKET_SIZE]; 
    
  public: 
    UdpServer(uint32_t port);

    void begin(); 
    void end();
    void listen();
    void handleProbe(IPAddress remoteIP, unsigned int remotePort, uint8_t *data, size_t len); 
};


UdpServer::UdpServer(uint32_t port){
  this->_port = port;
}

void UdpServer::begin(){
  this->_udp.begin(this->_port); 
}

void UdpServer::end(){
  //TODO: implement
}

void UdpServer::listen(){
  int cb = this->_udp.parsePacket();
  if (cb) {
    IPAddress remoteIP = this->_udp.remoteIP();
    unsigned int remotePort = this->_udp.remotePort();
    uint8_t data[cb];
    this->_udp.read(data, cb);
    this->handleProbe(remoteIP, remotePort, data, cb);
  }
}

void UdpServer::handleProbe(IPAddress remoteIP, unsigned int remotePort, uint8_t *data, size_t len) 
{
  data[len] = 0;
  String content = String((char *) data);

  if (content.indexOf(UDP_SEARCH_PATTERN) == 0) 
  {
    //send response 
    WiFiUDP udpClient;
    udpClient.beginPacket(remoteIP, remotePort);
    udpClient.write(WiFi.localIP().toString().c_str());
    udpClient.endPacket();
  }
}

#endif
