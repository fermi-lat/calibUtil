// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/calibUtil/ClientObject.h,v 1.2 2002/06/27 22:10:52 madhup Exp $
 
#ifndef CALIBUTIL_CLIENTOBJECT_H
#define CALIBUTIL_CLIENTOBJECT_H

#include "calibUtil/StripSrv.h"

namespace calibUtil {

  class ClientObject {
  public: 
    
    /// Performs client specified function on data
    virtual unsigned int readData(StripSrv::towerRC towerId, 
                                  unsigned int trayNum, 
                                  StripSrv::eUnilayer uni, 
                                  std::vector<unsigned int> v) = 0;

  };

}// end of namespace calibUtil

#endif


