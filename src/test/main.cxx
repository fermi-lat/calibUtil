// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/test/main.cxx,v 1.1 2002/06/27 08:47:46 madhup Exp $
/// Test client program for strip services.  

#include "calibUtil/MyObject.h"

#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {

  std::string name(argv[1]);
  
  calibUtil::StripSrv ssObj(name);

  std::vector<calibUtil::towerRC> tv1 = ssObj.getBadTowers();   
  cout << "ROW IS" << tv1[0].row;
  cout << "COL IS" << tv1[0].col;

  calibUtil::towerRC trc;
  trc.row = 3;
  trc.col = 2; 

  cout << "bad is" <<  ssObj.countBad(trc,2,calibUtil::TOP) << endl;

  std::vector<unsigned int> stripList 
    = ssObj.getBad(trc,0,calibUtil::TOP);
  cout << "strip number is" << stripList[0];

  cout<< "BAD TYPE IS" << ssObj.getBadType() << std::endl;

  cout << "instrument name is" << ssObj.getCalType() << endl;

  calibUtil::MyObject cli;
  ssObj.traverseInfo(&cli);

  return(0);

} /* end of main */









