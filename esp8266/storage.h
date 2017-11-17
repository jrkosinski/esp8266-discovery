
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <EEPROM.h>

#define SETUP_GUID "##a136462c-16d3-4638-82e4-f8a4b08d137b##" 
#define EEPROM_SIZE 1024
#define GUID_INDEX 0
#define WIFI_SSID_INDEX 1
#define WIFI_PASSWD_INDEX 2

const char* test_ssid = "mina" ; 
const char* test_passwd = "HappyTime"; 

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
    ~Database();

    char* getWifiSsid();
    char* getWifiPasswd(); 
    void setWifiData(const char* ssid, const char* passwd);
    bool isConfigured(); 
    void begin();
    void end();

  private: 
    void read(); 
    char* getRecord(int index);
    void setRecord(int index, const char* value, bool isLast = false); 
    void write(); 
    void printContents();
};
/****************************************/


// ************************************************************************************
// default constructor 
// 
Database::Database(){
}
Database::~Database(){
  this->end();
}

// ************************************************************************************
// 
//TODO: this should be combined so we dont have to read twice in a row
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
  this->setRecord(GUID_INDEX, SETUP_GUID, false); 
  this->setRecord(WIFI_SSID_INDEX, ssid, false);
  this->setRecord(WIFI_PASSWD_INDEX, passwd, true); 
  this->write();
}

// ************************************************************************************
//  
bool Database::isConfigured() {
  this->read();
  char* guid = this->getRecord(GUID_INDEX);
  if (guid != NULL){
    return (strcmp(guid, SETUP_GUID) == 0);
  }
  
  return false;
}

// ************************************************************************************
//  
void Database::begin() {
  EEPROM.begin(EEPROM_SIZE);
}

// ************************************************************************************
//  
void Database::end() {
  EEPROM.end();
}

// ************************************************************************************
//  
void Database::read(){
  for(int n=0; n<EEPROM_SIZE; n++) {
    this->_dataBuffer[n] = EEPROM.read(n); 
  }
}

// ************************************************************************************
//  
void Database::write(){
  int nullCount =0; 
  for(int n=0; n<EEPROM_SIZE; n++){
    EEPROM.write(n, this->_dataBuffer[n]); 
    
    if (this->_dataBuffer[n] == 0)
      nullCount++; 
    else 
      nullCount = 0; 

    if (nullCount >= 3)
      break;      
  }
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
      n++; 
    }

    //if we're at the index, return ptr
    if (curIndex == index){
      return (char*)(this->_dataBuffer+n);
    }

    //if past the index already, return null
    if (curIndex > index)
      return NULL;
  }

  return NULL;
}

// ************************************************************************************
//  
void Database::setRecord(int index, const char* value, bool isLast)
{
  char* recordPtr = this->getRecord(index); 
  if (recordPtr == NULL){
    recordPtr = this->_dataBuffer;
  }
    
  int len = strlen(value);
  strcpy(recordPtr, value);
  recordPtr[len] = 0; 

  if (isLast){
    recordPtr[len+1] = 0;
    recordPtr[len+2] = 0;
  }
}

// ************************************************************************************
//  
void Database::printContents()
{
  for(int n=0; n<EEPROM_SIZE; n++)
  {
    char c = this->_dataBuffer[n];
    if (c == 0)
      DEBUG_PRINTLN(c); 
    else {
      DEBUG_PRINT(c); 
      DEBUG_PRINT(","); 
    }

    if (c == 0 && this->_dataBuffer[n+1] == 0 && this->_dataBuffer[n+2] == 0)
      break;
  }
}

#endif 
