
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
    
  public:
    WifiDTO(const char*, const char*); 
    
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

char* WifiDTO::toJson(char* buffer) {  
  strcpy(buffer, "{ ssid:\""); 
  strcpy(buffer, this->_ssid); 
  strcpy(buffer, "\" password:\""); 
  strcpy(buffer, this->_password); 
  strcpy(buffer, "\" }"); 

  return buffer;
}

#endif
