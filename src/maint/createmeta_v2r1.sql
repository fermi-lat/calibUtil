# $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/maint/createmeta_v2r1.sql,v 1.1 2002/11/18 23:02:43 jrb Exp $
# File for creating metadata table for calibration
# This (or any other) script may be run from within mysql 
#     mysql>  source createmeta.sql
# or directly from shell prompt (known as "batch mode"), e.g.
#     $ mysql -p < createmeta.sql


use calib;


## start out with alternate name so as not to disturb current working
## version                    
#  Field meanings:
#   ser_no           serial number.  One series is used for all
#                    calibration types. (automatic assignment)
#   instrument       flight, EM, etc.
#   calib_type       What kind of data, e.g. TKR bad strips
#   flavor           Denotes special kind of calibration; defaults to "vanilla"
#   data_fmt         Anticipate supporting XML and ROOT (just XML to start)
#   data_size        Optional field; interpretation to depend on calib_type
#   vstart,vend      Validity interval for data
#   enter_time       When this record was entered in dbs (automatic assignment)
#   locale           Where calibration input was acquired; defaults to "orbit"
#   fmt_version      Versioning field placeholder so that code has option
#                    of, e.g., reading in old data.
#   proc_level       How seriously are we to take this data?
#   prod_start       Time the calibration achieved proc_level = 'PROD'
#   prod_end         Time the calib. ceased being called 'PROD', e.g.
#   completion       Did it?     
#   creator          What program created the data?
#   uid              What person created/entered the data?
#   data_ident       Filename or other identifier for persistent data
# $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/src/maint/createmeta_v2r1.sql,v 1.1 2002/11/18 23:02:43 jrb Exp $
#       input_desc       Comments about input to this calibration procedure
#       notes            A spot for miscellaneous comments
create table metadata_v2r1
  (ser_no mediumint not null auto_increment primary key, 
   instrument  varchar(16) not null,
   calib_type  varchar(20) not null,
   flavor      varchar(30) not null default 'vanilla',
   data_fmt    varchar(10) not null,
   data_size   int(11),
   vstart      datetime,
   vend        datetime,
   enter_time  timestamp,
   locale      varchar(30) not null default 'orbit',
   fmt_version varchar(12),
   completion ENUM('OK','INC', 'ABORT'),
   proc_level ENUM('PROD', 'TEST', 'DEV', 'SUPSED') not null default 'TEST',
   prod_start  datetime,
   prod_end    datetime,
   creator     varchar(255),
   uid         varchar(12) not null,
   data_ident     varchar(255) not null,  
   input_desc  varchar(255),
   notes varchar(255),
   index typical_search (completion, instrument, calib_type, flavor, proc_level)  )
  comment = "calibration metadata table version v2r1";

#    Following won't be implemented until and unless it's necessary
#   read_status      In case we want to, e.g., lock out readers while a 
#                    row is being created or updated.
###   Probably don't need a 'busy bit' per row
###    read_status ENUM('BUSY', 'OK', 'BAD') not null default 'BUSY', 
