// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/test/MyObject.h,v 1.1 2002/06/28 18:20:11 jrb Exp $
/// file for sample client

#ifndef CALIBUTIL_MYOBJECT_H
#define CALIBUTIL_MYOBJECT_H

#include "calibUtil/ClientObject.h"

  class MyObject : public calibUtil::ClientObject {
  public: 
    
    /// Performs client specified function on the data
    unsigned int readData(calibUtil::StripSrv::towerRC towerId, 
                          unsigned int trayNum, 
                          calibUtil::StripSrv::eUnilayer uni, 
                          std::vector<unsigned int> v){
      
      // Any function on the stripList v can be written here
      cout << "IN READ DATA" << endl;
      
    }

  };
  

#endif
  
