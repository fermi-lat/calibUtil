##   $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/maint/fillmeta_v2r1.sql,v 1.3 2003/02/06 23:28:56 jrb Exp $
## Put some fake Cal pedestal data into metadata table

use calib;

insert into metadata_v2r1
 set instrument="LAT", calib_type="CAL_Ped", data_fmt="XML",
 vstart="2000-10-31", vend="2003-1-10 10:00",fmt_version="v2r0",
 completion="OK",creator="addCalPeds.sql",uid="jrb", proc_level="PROD",
 data_ident="$(CALIBUTILROOT)/xml/test/testCalPed_v2.xml",
 notes="Made-up pedestals for made-up mini-LAT";

insert into metadata_v2r1
 set instrument="LAT", calib_type="CAL_Ped", data_fmt="XML",
 vstart="2003-1-10 02:00", vend="2004-1-10 17:00",fmt_version="v2r0",
 completion="OK",creator="addCalPeds.sql",uid="jrb", proc_level="PROD",
 data_ident="$(CALIBUTILROOT)/xml/test/testCalPed_v2n2.xml",
 notes="More made-up pedestals for made-up mini-LAT";



   