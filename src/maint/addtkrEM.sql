##   $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/maint/fillmeta_v2r1.sql,v 1.3 2003/02/06 23:28:56 jrb Exp $
## Put some EM data into metadata table

use calib;

insert into metadata_v2r1
 set instrument="EM", calib_type="TKR_DeadChan", data_fmt="XML",
 vstart="2000-10-31", vend="2004-11-23",fmt_version="v2r0",
 completion="OK",creator="addTkrEM.sql",uid="jrb", proc_level="PROD",
 data_ident="$(CALIBUTILROOT)/xml/Tkr/DeadStripsOutput.xml",
 notes="Leon's EM dead channels file";

insert into metadata_v2r1
 set instrument="EM", calib_type="TKR_HotChan", data_fmt="XML",
 vstart="2000-10-31", vend="2004-1-10 17:00",fmt_version="v2r0",
 completion="OK",creator="addTkrEM.sql",uid="jrb", proc_level="PROD",
 data_ident="$(CALIBUTILROOT)/xml/Tkr/HotStripsOutput.xml",
 notes="Leon's EM hot channels file";



   