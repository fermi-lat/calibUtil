##   $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/calibUtil/src/maint/fillmeta_v1.sql,v 1.3 2002/07/09 18:24:53 jrb Exp $
## Put some fake data into metadata table

use calib;

insert into metadata_v1 
 set instrument="BTEM", calib_type="TKR_Bad_Chan", data_fmt="XML",
 vstart="2000-10-31", vend="2000-11-23",fmt_version="v0r0",
 completion="OK",creator="metafill.sql",uid="jrb",
 data_ident="$CALIBUTILXMLPATH/test/phantom1.xml",
 notes="total fantasy";

insert into metadata_v1 
 set instrument="BTEM", calib_type="TKR_Bad_Chan", data_fmt="XML",
 vstart="2000-10-31", vend="2000-11-23",fmt_version="v0r0",
 completion="inc",creator="metafill.sql",uid="jrb", proc_level="DEV",
 data_ident="$CALIBUTILXMLPATH/test/phantom2.xml",
 notes="total fantasy";

insert into metadata_v1 
 set instrument="BFEM", calib_type="TKR_Bad_Chan", data_fmt="XML",
 vstart="2000-10-31", vend="2000-11-23",fmt_version="v0r0",
 completion="OK",creator="metafill.sql",uid="jrb", proc_level="DEV",
 data_ident="$CALIBUTILXMLPATH/test/phantom3.xml",
 notes="total fantasy";

insert into metadata_v1 
 set instrument="BTEM", calib_type="CAL_Light_Att", data_fmt="XML",
 vstart="2000-10-31", vend="2000-11-23",fmt_version="v0r0",
 completion="OK",creator="metafill.sql",uid="jrb", proc_level="PROD",
 data_ident="$CALIBUTILXMLPATH/test/phantom4.xml",
 notes="total fantasy";

insert into metadata_v1 
 set instrument="BTEM", calib_type="TKR_Bad_Chan", data_fmt="XML",
 vstart="2001-10-31", vend="2001-11-23",fmt_version="v0r0",
 completion="OK",creator="metafill.sql",uid="jrb", proc_level="PROD",
 data_ident="$CALIBUTILXMLPATH/test/phantom5.xml",
 notes="total fantasy";


   
