# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/calibUtil/calibUtilLib.py,v 1.2 2009/08/07 22:04:43 jrb Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['calibUtil'])
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'calibUtil') 
    env.Tool('facilitiesLib')
    env.Tool('xmlBaseLib')
    env.Tool('rdbModelLib')
    env.Tool('addLibrary', library = env['xercesLibs'])
def exists(env):
    return 1;
