# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/calibUtil/SConscript,v 1.15 2012/08/20 18:14:36 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: calibUtil-01-14-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='calibUtil', toBuild='shared')
calibUtil = libEnv.SharedLibrary('calibUtil',
                                 listFiles(['src/*.cxx', 'src/*.c']))

progEnv.Tool('calibUtilLib')
test_strips = progEnv.Program('test_strips', ['src/test/test_strips.cxx'])
test_meta = progEnv.Program('test_meta',[ 'src/test/test_meta.cxx'])
calibCoverage = progEnv.Program('calibCoverage',
                                ['src/dbIntegrity/calibCoverage.cxx',
                                 'src/dbIntegrity/Coverage.cxx'])

progEnv.Tool('registerTargets', package = 'calibUtil',
             libraryCxts = [[calibUtil, libEnv]],
             testAppCxts = [[test_strips, progEnv], [test_meta, progEnv]],
             binaryCxts = [[calibCoverage, progEnv]],
             includes = listFiles(['calibUtil/*.h']))




