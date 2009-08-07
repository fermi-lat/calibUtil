# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/calibUtil/calibUtilLib.py,v 1.1 2008/07/09 21:13:44 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['calibUtil'])
    env.Tool('facilitiesLib')
    env.Tool('xmlBaseLib')
    env.Tool('rdbModelLib')
    env.Tool('addLibrary', library = env['xercesLibs'])
def exists(env):
    return 1;
