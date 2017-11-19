
#ifndef __WIFI_DTO_H__
#define __WIFI_DTO_H__

#include "debug.h" 

/****************************************
 * WifiDTO
 * --------
 * Encapsulates wifi data (ssid and password), and sometimes local IP. 
 * To be returned to client. 
 */
class WifiDTO
{
  private: 
    const char* _ssid;
    const char* _password;
    const char* _localIP = NULL;
    
  public:
    WifiDTO(const char*, const char*); 
    WifiDTO(const char*, const char*, IPAddress); 
    
    char* toJson(char* buffer);  
};
/****************************************/


// ************************************************************************************
// constructor 
//  
WifiDTO::WifiDTO(const char* ssid, const char* passwd)
{
  this->_ssid = ssid;
  this->_password = passwd;
}

// ************************************************************************************
// constructor 
//  
WifiDTO::WifiDTO(const char* ssid, const char* passwd, IPAddress localIP) : WifiDTO(ssid, passwd)
{
  this->_localIP = localIP.toString().c_str();
}

// ************************************************************************************
// converts current instance data to a JSON string 
// 
// args
//  buffer: buffer to which to write JSON
// 
// returns: pointer to buffer containing JSON string
// 
char* WifiDTO::toJson(char* buffer) {  
  sprintf(buffer, "{ \"ssid\":\"%s\", \"password\":\"******\", \"ip\":\"%s\" }", 
    this->_ssid, 
    this->_password, 
    this->_localIP != NULL ? this->_localIP : ""
  ); 

  return buffer;
}

#endif
