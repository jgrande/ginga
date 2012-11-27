#!/usr/bin/env python2
import sys
import os
from optparse import OptionParser

def setParam(option, opt, value, parser):
  setattr(parser.values, option.dest, value)

COMPILE=""
def setTool(option, opt, value, parser):
  global COMPILE
  COMPILE="TOOL"
  setParam(option, opt, value, parser)

def setLib(option, opt, value, parser):
  global COMPILE
  COMPILE="LIB"
  setParam(option, opt, value, parser)
    
def setToolGinga(option, opt, value, parser):
    option.dest="TOOL"
    setTool(option, opt, "ginga", parser)

MAKE_SENTENCE_COMPILE="make"

def setMode(option, opt, value, parser):
  if parser.values.MODE:
    print "\nWARNING :: Can only sets one Debug Mode. Argument was ignored: %s\n" % opt
  else:
    option.dest="MODE"
    valMode="-DVERBOSITY="
    if opt == "-d" or opt == "--debug":
      valMode+="1 -DCMAKE_VERBOSE_MAKEFILE=ON"
    elif opt == "-v" or opt == "--verbose":
      valMode+="2"
      global MAKE_SENTENCE_COMPILE
      MAKE_SENTENCE_COMPILE+=" VERBOSE=1"
    else:
      valMode+="0"
    setParam(option, opt, valMode, parser)

def checkBuildType(parser):
  if(parser.values.BUILD_TYPE == "Debug") or (parser.values.BUILD_TYPE == "Release") or (parser.values.BUILD_TYPE == "RelWithDebInfo") or (parser.values.BUILD_TYPE == "MinSizeRel"):
    return True
  else:
    print "ERROR :: You must set a valid build type (Release, Debug, RelWithDebInfo, MinSizeRel)."
    return False

def checkParams(parser):
  if bool(parser.values.TOOL) ^ bool(parser.values.LIB):
    if parser.values.MODE: 
      return checkBuildType(parser)
    else:
      parser.values.MODE="-DVERBOSITY=0"
      return checkBuildType(parser)
  else:
    print "ERROR :: You must set lib OR tool param to compile."
    return False

#-- main()

def runCmd( command ):
	print command
	result = os.system(command)
	if not result == 0:
		sys.exit(1)

def setOptions(parser):

  parser.add_option("-t", "--tool", dest="TOOL", action="callback", callback=setTool, type="string", help="Specify the TOOL to compile.", metavar="TOOL")
  parser.add_option("-l", "--lib", dest="LIB", action="callback", callback=setLib, type="string", help="Specify the LIB to compile.", metavar="LIB")
  #parser.add_option("--ginga", action="callback", callback=setToolGinga, help="Set TOOL = GINGA to compile.")

  parser.add_option("-o","--options", dest="OPTIONS_ONLY", action="store_true", default=False, help="Get the options defined in the LIB/TOOL. Also is needed to set -l or -t param.", metavar="OPTIONS_ONLY")
  
  parser.add_option("-p", "--platform", dest="PLATFORM", action="callback", callback=setParam, type="string", help="Set the PLATFORM to compile.", default="LINUX", metavar="PLATFORM")

  parser.add_option("-k", "--pack", dest="PACKAGE", action="store_true", help="Pack the project?", default=False, metavar="PACKAGE")

  parser.add_option("-i", "--ide", dest="IDE", action="callback", callback=setParam, type="string", help="Define the IDE with compile the TOOL.", default="", metavar="IDE")

  parser.add_option("-b", "--build-type", dest="BUILD_TYPE", action="callback", callback=setParam, type="string", default="Release", help="Set the build type for make based generators.")
  
  # params to diferents debug modes
  parser.add_option("-d", "--debug", dest="MODE", action="callback", callback=setMode, default="", help="Put cmake in debug mode.(Debug in CMAKE)")
  parser.add_option("-v", "--verbose", dest="MODE", action="callback", callback=setMode, default="", help="Put cmake in verbose mode.(Debug in MAKE)")

def setupCmakeParams(parser):
  DEPOT = os.path.dirname(os.path.dirname(os.path.abspath( __file__ )))
  
  if os.getenv("DEPOT") == None:
    os.putenv("DEPOT",DEPOT)
  else:
    DEPOT = os.getenv("DEPOT")

  PLATFORM=parser.values.PLATFORM
  
  PLATFORM_FILE="%s/config/Platform_%s.cmake" % (DEPOT, PLATFORM)
  MODE=parser.values.MODE
  
  if(parser.values.OPTIONS_ONLY):
    OPTIONS_ONLY=1
  else:
    OPTIONS_ONLY=0
    
  if(parser.values.PACKAGE):
    GENERATE_PACKAGE=1
  else:
    GENERATE_PACKAGE=0
  
  CMAKE_BUILD_TYPE="-DCMAKE_BUILD_TYPE=\""+parser.values.BUILD_TYPE+"\""
  
  GENERATE_PROJECT=parser.values.IDE

  if COMPILE == "TOOL":
    IS_TOOL="-DIS_TOOL=1"
    COMPILE_PROJECT=parser.values.TOOL
  else:
    IS_TOOL="-DIS_TOOL=0"
    COMPILE_PROJECT=parser.values.LIB    

  return (MODE, IS_TOOL, OPTIONS_ONLY, PLATFORM_FILE, COMPILE_PROJECT, GENERATE_PACKAGE, GENERATE_PROJECT, DEPOT, PLATFORM, CMAKE_BUILD_TYPE)

parser = OptionParser()
setOptions(parser)

parser.parse_args()

#print parser.values
if checkParams(parser):
  (MODE, IS_TOOL, OPTIONS_ONLY, PLATFORM_FILE, COMPILE_PROJECT, GENERATE_PACKAGE, GENERATE_PROJECT, DEPOT, PLATFORM, CMAKE_BUILD_TYPE)=setupCmakeParams(parser)
  # Configure the projects
  runCmd ("cmake %s %s %s -DCMAKE_TOOLCHAIN_FILE=\"%s\" -DCOMPILE_PROJECT=%s -DOPTIONS_ONLY=%d -DPACK=%d -DGENERATE_PROJECTS=%s %s/build" % (MODE, IS_TOOL, CMAKE_BUILD_TYPE, PLATFORM_FILE, COMPILE_PROJECT, OPTIONS_ONLY, GENERATE_PACKAGE, GENERATE_PROJECT, DEPOT))
  if(not OPTIONS_ONLY):
    # and build them
    if (PLATFORM == "VS"):
      runCmd ("msbuild build.sln" )
    else:
      runCmd (MAKE_SENTENCE_COMPILE + " %s" % COMPILE_PROJECT)

else:
  parser.print_help()
  