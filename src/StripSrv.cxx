// $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/StripSrv.cxx,v 1.15 2003/12/02 23:37:13 jrb Exp $
/// Module provides methods for clients to get strip services.

#include "xml/XmlParser.h"
#include "xml/Dom.h"
#include <xercesc/dom/DOM_Element.hpp>
#include <xercesc/dom/DOM_NodeList.hpp>
#include <xercesc/dom/DOM_TreeWalker.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <memory>

#include "calibUtil/GenericSrv.h"
#include "calibUtil/StripSrv.h"
#include "calibUtil/ChannelStatusDef.h"

namespace calibUtil {
  

  StripSrv::StripSrv(eBadType badType, const GenericSrv& gen)
    : m_badType(badType), m_state(BUILDING) {
    m_genSrv = new GenericSrv(gen);
  }

  // Initialize the data structures by parsing the XML file
  StripSrv::StripSrv(std::string xmlFileName) : m_badType(UNKNOWN_BADTYPE),
                                                m_state(FROM_PERS), 
                                                m_genSrv(0)            
  {
    using xml::Dom;

    xml::XmlParser* parser = new xml::XmlParser();
    DOM_Document doc = parser->parse(xmlFileName.c_str());

    if (doc == DOM_Document()) {
      std::cerr << "Error parsing document" << xmlFileName << std::endl;
      return;
    }

    DOM_Element docElt = doc.getDocumentElement();
    m_genSrv = new GenericSrv(docElt);

    std::vector<DOM_Element> towers;

    Dom::getDescendantsByTagName(docElt, "tower", towers);
    unsigned nTower = towers.size();

    m_towers.reserve(nTower);

    std::string bString = Dom::getAttribute(docElt,"badType");
    if (!bString.compare("hot")) m_badType = HOT;
    else if (!bString.compare("dead")) m_badType = DEAD;
    else m_badType = UNKNOWN_BADTYPE;


    for (unsigned int iTower = 0; iTower < nTower; iTower++) {
      Tower tower;
      tower.m_uniplanes.clear();
      try {
        tower.m_row = Dom::getIntAttribute(towers[iTower], "row");
        tower.m_col = Dom::getIntAttribute(towers[iTower], "col");
      }
      catch (xml::DomException ex) {
        std::cerr << "From calibUtil::StripSrv::StripSrv" << std::endl
                  << ex.getMsg() << std::endl;
        throw ex;
      }

      tower.m_howBad = 0;
      tower.m_allBad = 0;

      std::string attValue = Dom::getAttribute(towers[iTower], "nOnbdCalib");
      if (attValue.compare("true") == 0) {
        tower.m_howBad |= vCALIBUTIL_nOnbdCalib;
      }
      attValue = Dom::getAttribute(towers[iTower], "nOnbdTrig");
      if (attValue.compare("true") == 0) {
        tower.m_howBad |= vCALIBUTIL_nOnbdTrig;
      }
      attValue = Dom::getAttribute(towers[iTower], "nOnbdData");
      if (attValue.compare("true") == 0) {
        tower.m_howBad |= vCALIBUTIL_nOnbdData;
      }
      if (tower.m_howBad) {
        tower.m_allBad = 1;
        goto NEXT;
      }    // otherwise have to process individual uniplane elements

      {
        DOM_Element uniElt = Dom::getFirstChildElement(towers[iTower]);

        while (uniElt != DOM_Element()) {
          Uniplane uni;
          uni.m_howBad = 0;
          fillUni(uniElt, &uni);
          // if bad status, complain and return

          tower.m_uniplanes.push_back(uni);
          uniElt = Dom::getSiblingElement(uniElt);
        }
      }
    NEXT:
      m_towers.push_back(tower);
      //      towerElt = Dom::getSiblingElement(towerElt);
    }
  }

  /// destructor used to deallocate memory
  StripSrv::~StripSrv(){
    delete m_genSrv;
  }
  
  /// returns the status (Hot or Dead) of the strips
  StripSrv::eBadType  StripSrv::getBadType() const {
    return m_badType;
  }
  
  /// Lists all towers with bad strips 
  void StripSrv::getBadTowers(std::vector<StripSrv::towerRC>& towerRCs) const
  {
    std::vector<Tower>::const_iterator it = m_towers.begin();
    while(it != m_towers.end() ) {

      towerRC trc;
      towerRCs.reserve(m_towers.size());
      trc.row = it->m_row;
      trc.col = it->m_col;
      towerRCs.push_back(trc);
      it++;
    }
  }

 /// methods giving access to generic data

  /// Get instrument name
  std::string StripSrv::getInst() const {
    return m_genSrv->getInst();
  }
  
  /// Get timestamp
  std::string StripSrv::getTimestamp() const {
    return m_genSrv->getTimestamp();
  }
  
  /// Get calibration type
  std::string StripSrv::getCalType() const {
    return m_genSrv->getCalType();
  }
  
  /// Get format Version
  std::string StripSrv::getFmtVer() const {
    return m_genSrv->getFmtVer();
  } 
  
  
  /// call back method for client to access large data
  eVisitorRet StripSrv::traverseInfo(ClientObject *client) const {

    /* NOTE:  could also check for empty badLists and only
       call back client if nonempty.
    */
    std::vector<Tower>::const_iterator iTower = m_towers.begin();
    
    eVisitorRet ret = DONE;
    while (iTower != m_towers.end() ) {
      if (iTower->m_allBad) {
        ret = client->badTower(iTower->m_row, iTower->m_col, iTower->m_howBad);
        if (ret != CONT) return ret;
      }
      //   If tower not all bad, loop over planes within towers
      else {
        std::vector<Uniplane>::const_iterator iUni = 
          (iTower->m_uniplanes).begin();
        while (iUni != (iTower->m_uniplanes).end() ) {
          ret = client->badPlane(iTower->m_row, iTower->m_col,
                                 iUni->m_tray, iUni->m_top,
                                 iUni->m_howBad, iUni->m_allBad,
                                 (iUni->m_strips));
          if (ret != CONT) return ret;
          iUni++;
        }
      }
      ++iTower;
    }
    // If got to here, traversed the entire data structure without
    // a murmur from client
    return DONE;
  }

  // Private utilities

  void StripSrv::fillUni(const DOM_Element& uniElt, Uniplane *uni) {
    using xml::Dom;

    std::string attValue;

    attValue = Dom::getAttribute(uniElt, "allBad");
    uni->m_allBad = (attValue.compare("true") == 0);

    attValue = Dom::getAttribute(uniElt, "nOnbdCalib");
    if (attValue.compare("true") == 0) {
      uni->m_howBad |= vCALIBUTIL_nOnbdCalib;
    }
    attValue = Dom::getAttribute(uniElt, "nOnbdTrig");
    if (attValue.compare("true") == 0) {
      uni->m_howBad |= vCALIBUTIL_nOnbdTrig;
      }
    attValue = Dom::getAttribute(uniElt, "nOnbdData");
    if (attValue.compare("true") == 0) {
      uni->m_howBad |= vCALIBUTIL_nOnbdData;
    }
    
    attValue = Dom::getAttribute(uniElt, "tray");
    uni->m_tray = atoi(attValue.c_str());
    
    attValue = Dom::getAttribute(uniElt, "which");
    if (attValue.compare("top") == 0) uni->m_top = true;
    else if (attValue.compare("bot") == 0) uni->m_top = false;
    // if anything else happens, xml file is bad
    
    if (!uni->m_allBad) {   // process strip lists, spans
      fillStrips(uniElt, uni->m_strips);
    }
  }


  void StripSrv::fillStrips(const DOM_Element& badElt, StripCol& list) {
    using xml::Dom;

    DOM_Element childElt = Dom::getFirstChildElement(badElt);

    while (childElt != DOM_Element() ) {
      // must be list or span
      if (Dom::checkTagName(childElt, "stripList")) {
        std::string xmlList = Dom::getAttribute(childElt, "strips");
        strToNum(xmlList, list);
      }
      else  if (Dom::checkTagName(childElt, "stripSpan")) {
        unsigned short first, last;

        try {
          first = Dom::getIntAttribute(childElt, "first");
          last = Dom::getIntAttribute(childElt, "last");
        }
        catch (xml::DomException ex) {
          std::cerr << "From calibUtil::StripSrv::fillStrips" << std::endl
                    << ex.getMsg() << std::endl;
          throw ex;
        }
      
        if (last >= first) {
          // Might as well reserve memory all at once
          list.reserve(list.size() + last + 1 - first);  
          for (unsigned short int i = first; i <= last; i++) {
            list.push_back(i);
          }
        }
      }
      childElt = Dom::getSiblingElement(childElt);
    }
  }

  void StripSrv::strToNum(std::string s, std::vector<unsigned short int> &v){

    std::string::iterator it = s.begin();
    
    // Maybe add something to be sure all we've got are digits
    // and blanks??
    
    // Skip over leading blanks, if any
    while((it != s.end()) && (*it == ' ')) it++;

    // save contiguous digits in tempStr
    while ((it != s.end()) && (*it >= '0') && (*it <= '9'))    {
      std::string tempStr;    
      tempStr += *it;
      it++;  
        
      while((it != s.end()) && (*it >= '0') && (*it <= '9')){
        tempStr += *it;
        it++;
      }

      // No more contiguous digits; skip over blanks
      while((it != s.end()) && (*it == ' ')) it++;
      
      // Save the converted integer
      v.push_back(atoi(tempStr.c_str()));
    }

  }

  StripSrv::Tower* StripSrv::findTower(towerRC& towerId) {
    std::vector<Tower>::iterator it = m_towers.begin();
    while(it != m_towers.end() ) {
      if ((it->m_row == towerId.row) && (it->m_col == towerId.col)) {
        return (&(*it));
      }
      ++it;
    }
    return 0;
  }

  const StripSrv::Tower* StripSrv::findTower(const towerRC& towerId) const {
    std::vector<Tower>::const_iterator it = m_towers.begin();
    while(it != m_towers.end() ) {
      if ((it->m_row == towerId.row) && (it->m_col == towerId.col)) {
        return (&(*it));
      }
      ++it;
    }
    return 0;
  }
  
  eVisitorRet StripSrv::writeXml(std::ostream* ) {
    return DONE;
  }


}// end of namespace calibUtil
