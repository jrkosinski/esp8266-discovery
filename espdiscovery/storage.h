
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <EEPROM.h>

#define SETUP_GUID "##a136462c-16d3-4638-82e4-f8a4b08d137b##" 
#define EEPROM_SIZE 4096
#define GUID_INDEX 0
#define WIFI_SSID_INDEX 1
#define WIFI_PASSWD_INDEX 2

/****************************************
 * Database
 * ---------
 *  
 */
class Database 
{
  private: 
    char _dataBuffer[EEPROM_SIZE]; 
    
  public: 
    Database();

    char* getWifiSsid();
    char* getWifiPasswd(); 
    void setWifiData(const char* ssid, const char* passwd);
    bool isConfigured(); 

  private: 
    void open();
    void close();
    void read(); 
    char* getRecord(int index);
    void setRecord(int index, const char* value, bool isLast = false); 
    void write(); 
};
/****************************************/


// ************************************************************************************
// default constructor 
// 
Database::Database(){
}

// ************************************************************************************
//  
char* Database::getWifiSsid(){
  if (this->isConfigured())
    return this->getRecord(WIFI_SSID_INDEX);

  return NULL;
}

// ************************************************************************************
//  
char* Database::getWifiPasswd(){
  if (this->isConfigured())
    return this->getRecord(WIFI_PASSWD_INDEX);

  return NULL;
}

// ************************************************************************************
//  
void Database::setWifiData(const char* ssid, const char* passwd){
  this->read();
  this->setRecord(GUID_INDEX, SETUP_GUID); 
  this->setRecord(WIFI_SSID_INDEX, ssid);
  this->setRecord(WIFI_PASSWD_INDEX, passwd, true); 
  this->write();
}

// ************************************************************************************
//  
bool Database::isConfigured() {
  this->read();
  char* guid = this->getRecord(GUID_INDEX);
  return (strcmp(guid, SETUP_GUID) == 0);
}

// ************************************************************************************
//  
void Database::open() {
  EEPROM.begin(EEPROM_SIZE);
}

// ************************************************************************************
//  
void Database::close() {
  EEPROM.end();
}

// ************************************************************************************
//  
void Database::read(){
  this->open();
  
  for(int n=0; n<EEPROM_SIZE; n++) {
    this->_dataBuffer[n] = EEPROM.read(n); 
  }
  
  this->close();
}

// ************************************************************************************
//  
void Database::write(){
  this->open();
  int len = strlen(this->_dataBuffer);
  for(int n=0; n<len; n++){
    
  }
  this->close();
}

// ************************************************************************************
//  
char* Database::getRecord(int index)
{
  int curIndex = 0; 
  
  //go to requested index 
  for(int n=0; n<EEPROM_SIZE; n++)
  {
    //0 is the delimiter between records 
    if (this->_dataBuffer[n] == 0){
      curIndex++; 

      //000 is the end-of-file 
      if (this->_dataBuffer[n+1] == 0 && this->_dataBuffer[n+2] == 0)
        return 0;
    }

    //if we're at the index, return ptr
    if (curIndex == index){
      return (char*)(this->_dataBuffer+n);
    }

    //if past the index already, return null
    if (curIndex > index)
      return 0;
  }

  return false;
}

// ************************************************************************************
//  
void Database::setRecord(int index, const char* value, bool isLast)
{
  char* recordPtr = this->getRecord(index); 
  int len = strlen(value);
  strcpy(recordPtr, value);
  recordPtr[len] = 0; 

  if (isLast){
    recordPtr[len+1] = 0;
    recordPtr[len+2] = 0;
  }
}

#endif 
