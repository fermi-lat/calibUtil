// $Header: $
/// file for sample client

#ifndef CALIBUTIL_MYOBJECT_H
#define CALIBUTIL_MYOBJECT_H

#include "calibUtil/ClientObject.h"

namespace calibUtil {

  class MyObject : public ClientObject{
  public: 
    
    /// Performs client specified function on the data
    unsigned int readData(towerRC towerId, unsigned int trayNum, 
                          uniL uniLayer, std::vector<unsigned int> v){
      
      // Any function on the stripList v can be written here
      cout << "IN READ DATA" << endl;
      
    }

  };
  
}// end of namespace calibUtil

#endif
  
