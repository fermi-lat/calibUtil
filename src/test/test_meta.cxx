// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/test/test_meta.cxx,v 1.1 2002/07/05 22:52:58 jrb Exp $
/** @file test_meta.cxx
    Sample program to exercise calibration metadata database services
*/

#include <string>
#include <iostream>
#include "calibUtil/Metadata.h"

int main(int argc, char* argv[]) {

  // Very simplest thing to test first is getReadInfo.

  std::string  fmtVersion;
  calibUtil::Metadata::eDataFmt dataFmt;
  std::string dataIdent;
  unsigned    ser = 2;

  calibUtil::Metadata  meta;
  calibUtil::Metadata::eRet ret = 
    meta.getReadInfo(ser, dataFmt, fmtVersion, dataIdent);

  if (ret == calibUtil::Metadata::RETOk) {
    std::cout << "Success reading info for record #" << ser << std::endl;

    std::cout << "Data format = " << dataFmt << std::endl;
    std::cout << "Format version = " << fmtVersion << std::endl;
    std::cout << "Data ident = " << dataIdent << std::endl;
  }

  else {
    std::cout << "Failed reading info for record #" << ser;
    std::cout << " with code " << ret;
  }

  return(ret);

}









