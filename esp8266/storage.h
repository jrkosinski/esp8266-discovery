
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
 * EEPROM database interface. 
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
// gets the saved wifi SSID 
// 
// returns: point to the saved (string) value, or null if not found. 
//  
//TODO: this should be combined so we dont have to read twice in a row
char* Database::getWifiSsid(){
  if (this->isConfigured())
    return this->getRecord(WIFI_SSID_INDEX);

  return NULL;
}

// ************************************************************************************
// gets the saved wifi password 
// 
// returns: point to the saved (string) value, or null if not found. 
//  
char* Database::getWifiPasswd(){
  if (this->isConfigured())
    return this->getRecord(WIFI_PASSWD_INDEX);

  return NULL;
}

// ************************************************************************************
// sets wifi SSID and password and writes it to the database. 
// 
// args 
//  ssid: the wifi SSID to save 
//  passwd: the wifi passwd to save
//
void Database::setWifiData(const char* ssid, const char* passwd){
  this->read();
  this->setRecord(GUID_INDEX, SETUP_GUID, false); 
  this->setRecord(WIFI_SSID_INDEX, ssid, false);
  this->setRecord(WIFI_PASSWD_INDEX, passwd, true); 
  this->write();
}

// ************************************************************************************
// returns true if the database has ever been written to; false otherwise. 
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
// initializes this instance 
// 
void Database::begin() {
  EEPROM.begin(EEPROM_SIZE);
}

// ************************************************************************************
// closes/deinitializes this instance 
// 
void Database::end() {
  EEPROM.end();
}

// ************************************************************************************
// read entire contents of EEPROM into memory. 
// 
void Database::read(){
  for(int n=0; n<EEPROM_SIZE; n++) {
    this->_dataBuffer[n] = EEPROM.read(n); 
  }
}

// ************************************************************************************
// read entire contents of in-memory buffer into EEPROM. 
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
// gets a pointer to the value (char*) of the given record (specified by index)
//
// args
//  index: index of record to retrieve.
//
// returns: pointer to the value of the record, or null if not found. 
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
// overwrites the value of the specified record with the given value, but only in 
// the in-memory buffer (doesn't automatically write it to the database as well) 
//
// args
//  index: index of record to set.
//  value: the string value to write. 
//  isLast: true if the given record index is the last one in the database.
//
// returns: pointer to the value of the record, or null if not found. 
//  
void Database::setRecord(int index, const char* value, bool isLast)
{
  //get record 
  char* recordPtr = this->getRecord(index); 
  if (recordPtr == NULL){
    recordPtr = this->_dataBuffer;
  }

  //copy new data 
  int len = strlen(value);
  strcpy(recordPtr, value);
  recordPtr[len] = 0; 

  //last record delimiter
  if (isLast){
    recordPtr[len+1] = 0;
    recordPtr[len+2] = 0;
  }
}

// ************************************************************************************
// for debugging; prints entire contents of database to serial. 
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
