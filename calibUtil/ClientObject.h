// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/calibUtil/ClientObject.h,v 1.3 2002/07/09 23:07:29 jrb Exp $
 
#ifndef CALIBUTIL_CLIENTOBJECT_H
#define CALIBUTIL_CLIENTOBJECT_H

#include "calibUtil/StripSrv.h"

namespace calibUtil {

  class ClientObject {
  public: 
    
    /// Performs client specified function on data
    virtual StripSrv::eRet readData(StripSrv::towerRC towerId, 
                                    unsigned int trayNum, 
                                    StripSrv::eUnilayer uni, 
                                    StripSrv::eBadness  howBad,
                                    const StripSrv::StripCol* const strips) = 0;

  };

}// end of namespace calibUtil

#endif


