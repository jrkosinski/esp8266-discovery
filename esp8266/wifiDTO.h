
#ifndef __WIFI_DTO_H__
#define __WIFI_DTO_H__

#include "debug.h" 

/****************************************
 * WifiDTO
 * --------
 *  
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
//  
char* WifiDTO::toJson(char* buffer) {  
  strcpy(buffer, "{ ssid:\""); 
  strcpy(buffer+strlen(buffer), this->_ssid); 
  strcpy(buffer+strlen(buffer), "\" password:\""); 
  strcpy(buffer+strlen(buffer), this->_password); 

  if (this->_localIP != NULL){
    strcpy(buffer+strlen(buffer), "\" localIP:\""); 
    strcpy(buffer+strlen(buffer), this->_localIP);
  }
  
  strcpy(buffer+strlen(buffer), "\" }"); 

  return buffer;
}

#endif
