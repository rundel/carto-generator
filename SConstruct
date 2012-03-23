import glob
import os
import pipes
import subprocess
import shlex

import sys

# colorize output
colors = {
    'cyan'      : '\033[96m',
    'purple'    : '\033[95m',
    'blue'      : '\033[94m',
    'green'     : '\033[92m',
    'yellow'    : '\033[93m',
    'red'       : '\033[91m',
    'end'       : '\033[0m'
}

if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

# construct environment
env = Environment(
  #CXXCOMSTR='%scxx: $SOURCE -> $TARGET%s' % (colors['green'], colors['end']),
  #CCCOMSTR='%scc: $SOURCE -> $TARGET%s' % (colors['green'], colors['end']),
  #SHCXXCOMSTR='%scxx: $SOURCE -> $TARGET%s' % (colors['green'], colors['end']),
  #SHCCCOMSTR='%scc: $SOURCE -> $TARGET%s' % (colors['green'], colors['end']),
  #LINKCOMSTR='%sld: $TARGET%s' % (colors['yellow'], colors['end']),
  #SHLINKCOMSTR='%sld: $TARGET%s' % (colors['yellow'], colors['end']),

  #tools=["default"],
  ENV = {'PATH' : os.environ['PATH']}
)

# check environ
if 'CXX' in os.environ:
    env.Replace(CXX=os.environ['CXX'])
    print("%sconfigure: using CXX: %s%s" % (colors['blue'], os.environ['CXX'], colors['end']))

if 'CXXFLAGS' in os.environ:
    env.Append(CXXFLAGS=os.environ['CXXFLAGS'])
    print("%sconfigure: using CXXFLAGS: %s%s" % (colors['blue'], os.environ['CXXFLAGS'], colors['end']))

if 'LDFLAGS' in os.environ:
    env.Append(LINKFLAGS=os.environ['LDFLAGS'])
    print("%sconfigure: using LDFLAGS: %s%s" % (colors['blue'], os.environ['LDFLAGS'], colors['end']))

def _mapnik_config(*args):
    (output, _) = subprocess.Popen(('mapnik-config',) + args, stdout=subprocess.PIPE).communicate()
    return shlex.split(output.strip())

# configure
mapnik_cflags = _mapnik_config('--cflags')
mapnik_ldflags = _mapnik_config('--libs', '--ldflags', '--dep-libs')
(plugin_path,) = _mapnik_config('--input-plugins')

# hacky fix for boost library suffixes
boost_libs = [x for x in _mapnik_config('--dep-libs') if x.find("-lboost_") != -1 ]
boost_suff = ""
if boost_libs[0].rfind("-") > 0:
	boost_suff = "-"+boost_libs[0].split("-")[-1]

env.Append(CPPPATH=[ 'include', 'agg/include' ])
env.Append(CXXFLAGS=mapnik_cflags + [ '-DMAPNIKDIR="\\"{0}\\""'.format(pipes.quote(plugin_path)) ])# + [ '-Wall', '-pedantic', '-Wfatal-errors', '-Werror', '-Wno-unused-but-set-variable', '-Wno-format' ])
env.Append(LINKFLAGS=mapnik_ldflags + [ '-lboost_program_options'+boost_suff ])

objects = env.Object(source=[ fn for fn in glob.glob('src/*.cpp') + glob.glob('src/**/*.cpp') if fn != 'src/xml2carto.cpp' ])

env.Program(target='xml2carto',
            source=objects + [ 'src/xml2carto.cpp' ])
