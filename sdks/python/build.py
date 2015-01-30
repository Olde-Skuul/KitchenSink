#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Build project files
#

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import os
import glob
import shutil
import sys
import platform
import argparse
import subprocess
import burger

#
# Call a user supplied python script for custom build rules
#

def invokepython(fullpathname):

	# Get the working directory
	workingDir = os.path.dirname(fullpathname)

	# extract the class name from the filename
	basename = os.path.basename(fullpathname)
	splitname = os.path.splitext(basename)

	# Add this folder to python so it can find the new file
	sys.path.append(workingDir)

	# Import the new code
	externalcode = __import__(splitname[0])

	# Force a load (Clear the cache)
	reload(externalcode)

	# Compile, and then execute the custom code
	error = externalcode.main(workingDir)

	# Restore the pathnames
	sys.path.pop()

	# Return the error, if any
	return error

#
# Build a rezfile
# Return 0 if no error, non-zero on error
#

def buildrezscript(fullpathname,verbose):
	# Create the build command
	if verbose==True:
		cmd = 'makerez -v "' + fullpathname + '"'
		print cmd
	else:
		cmd = 'makerez "' + fullpathname + '"'
	return subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)

#
# Build slicer data
# Return 0 if no error, non-zero on error
#

def buildslicerscript(fullpathname,verbose):
	# Create the build command
	cmd = 'slicer "' + fullpathname + '"'
	if verbose==True:
		print cmd
	return subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)

#
# Build Doxygen docs
# Return 0 if no error, non-zero on error
#

def builddoxygen(fullpathname,verbose):

	# Is Doxygen installed?

	doxygenpath = burger.whereisdoxygen()
	if doxygenpath==None:
		return 0

	# Make the output folder for errors (If needed)

	tempdir = os.path.join(os.path.dirname(fullpathname),'temp')
	burger.createfolderifneeded(tempdir)
	bindir = os.path.join(os.path.dirname(fullpathname),'bin')
	burger.createfolderifneeded(bindir)
	# Location of the log file
	errorsfile = os.path.join(bindir,'doxygenerrors.txt')

	# Create the build command
	if burger.getmachosttype()!=False:
		# The mac version requires the file to have Linux line feeds!!!
		tempdox = fullpathname + '.tempfile'
		cmd = 'addlf -l "' + fullpathname +'" "' + tempdox + '"'
		if verbose==True:
			print cmd
		subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
		cmd = '"' + os.path.join(doxygenpath) + '" "' + tempdox + '" 2> "' + errorsfile + '"'
		if verbose==True:
			print cmd
		error = subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
		os.remove(tempdox)
		
	else:
		cmd = '"' + os.path.join(doxygenpath) + '" "' + fullpathname + '" 2> "' + errorsfile + '"'
		if verbose==True:
			print cmd
		error = subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
	
	# If the error log has nothing, delete it
	if os.stat(errorsfile).st_size==0:
		os.remove(errorsfile)
		
	return error
#
# Build Watcom MakeFile
# Return 0 if no error, non-zero on error
#

def buildwatcommakefile(results,fullpathname,verbose,fatal):
	# Is Watcom installed?
	watcompath = os.getenv('WATCOM')
	if watcompath==None:
		print fullpathname + ' requires Watcom to be installed to build!'
		results.append((0,fullpathname))
		return 0

	# List of platforms to build
	platformlist = [
		'dos4gw',
		'dosx32',
		'win32'	]
		
	# List of configurations to build
	
	targetlist = [
		'Debug',
		'Internal',
		'Release']
	
	# Create the build commands
	
	erroroccurred = 0
	oldpath = os.environ['PATH']
	os.environ['PATH'] = os.path.join(watcompath,'binnt') + ';' + os.path.join(watcompath,'binw') + ';' + oldpath

	if fullpathname.endswith('.wmk'):
		cmd = '"' + os.path.join(watcompath,'binnt','wmake') + '" -e -h -f "' + fullpathname + '" all'
		if verbose==True:
			print cmd
		error = subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
		results.append((error,fullpathname,'all'))
		if error!=0:
			erroroccurred = 1
			if fatal==True:
				os.environ['PATH'] = oldpath
				return error
				
	else:
		for platform in platformlist:
			for target in targetlist:

				cmd = '"' + os.path.join(watcompath,'binnt','wmake') + '" -e -h -f "' + fullpathname + '" Target=' + target + ' Platform=' + platform
				if verbose==True:
					print cmd
				error = subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
				results.append((error,fullpathname,platform + '|' + target))
				if error!=0:
					erroroccurred = 1
					if fatal==True:
						os.environ['PATH'] = oldpath
						return error
	
	os.environ['PATH'] = oldpath
	return erroroccurred

#
# Given a .sln file for Visual Studio 8, 9 or 10
# locate and extract all of the build targets
# available and return the list
# It will also determine which version of Visual
# Studio this solution file requires
#

def parseslnfile(fullpathname):

	# Start with an empty list
	
	visualstudio = 0
	targetlist = []
	
	fp = open(fullpathname)
	for line in fp:
	
		# Get the version number
		
		if 'Microsoft Visual Studio Solution File' in line:
		
			# The number is in the last part of the line
			lineparts = line.rsplit()
			versionstring = lineparts[len(lineparts)-1]
			# Use the version string to determine which visual studio to launch
			if versionstring=='8.00':
				visualstudio = 7
			elif versionstring=='9.00':
				visualstudio = 8
			elif versionstring=='10.00':
				visualstudio = 9
			elif versionstring=='11.00':
				visualstudio = 10
			
		# Look for this section. Immediately after it
		# has the targets
		if 'GlobalSection(SolutionConfigurationPlatforms)' in line:
			for line in fp:
				# Once the end of the section is reached, end
				if 'EndGlobalSection' in line:
					break
				# They are seperated by spaces
				lineparts = line.rsplit('=')
				# The first entry is the data needed
				targetlist.append(lineparts[0].strip())

	# Clean up and exit with the results
	fp.close()
	if visualstudio==0:
		print 'The visual studio solution file ' + fullpathname + ' is corrupt or an unknown version!'
	return (targetlist,visualstudio)

#
# Build a visual studio .sln file
# Return 0 if no error or error ignored, non-zero if a fatal error
#

def buildvisualstudio(results,fullpathname,verbose,fatal):

	# Get the list of build targets
	(targetlist,visualstudio) = parseslnfile(fullpathname)
	
	# Was the file corrupted?
	if visualstudio==0:
		results.append((10,fullpathname))
		# The error message about corruption was already printed
		return 10

	vstudioenv=None
	if visualstudio==7:
		# Is Visual studio 7 installed?
		vstudioenv = 'VS71COMNTOOLS'
	elif visualstudio==8:
		# Is Visual studio 8 installed?
		vstudioenv = 'VS80COMNTOOLS'
	elif visualstudio==9:
		# Is Visual studio 9 installed?
		vstudioenv = 'VS90COMNTOOLS'
	elif visualstudio==10:
		# Is Visual studio 10 installed?
		vstudioenv = 'VS100COMNTOOLS'
	elif visualstudio==11:
		# Is Visual studio 11 installed?
		vstudioenv = 'VS110COMNTOOLS'
	else:
		print fullpathname + ' requires Visual Studio version ' + str(visualstudio) + ' which is unsupported!'
		results.append((0,fullpathname))
		return 0
	
	# Is Visual studio installed?
	vstudiopath = os.getenv(vstudioenv)
	if vstudiopath==None:
		print fullpathname + ' requires Visual Studio version ' + str(visualstudio) + ' to be installed to build!'
		results.append((0,fullpathname))
		return 0
		
	# Locate the launcher
	
	vstudiopath = os.path.abspath(vstudiopath + '\..\ide\devenv')
	# Build each and every target
	xboxfail = False
	xbox360fail = False
	ps3fail = False
	ps4fail = False
	shieldfail = False
	androidfail = False
	erroroccurred = 0
	for target in targetlist:
	
		# Certain targets require an installed SDK
		# verify that the SDK is installed before trying to build
		
		targettypes = target.rsplit('|')
		
		# PS3
		if targettypes[1]=='PS3':
			if os.getenv('SCE_PS3_ROOT')==None:
				ps3fail = True
				continue
		
		# PS4
		if targettypes[1]=='ORBIS':
			if os.getenv('SCE_ORBIS_SDK_DIR')==None:
				ps4fail = True
				continue
		
		# Xbox 360
		if targettypes[1]=='Xbox 360':
			if os.getenv('XEDK')==None:
				xbox360fail = True
				continue
		
		# Xbox Classic
		if targettypes[1]=='Xbox':
			if os.getenv('XDK')==None:
				xboxfail = True
				continue

		# Android
		if targettypes[1]=='Android':
			if os.getenv('ANDROID_NDK')==None:
				androidfail = True
				continue
				
		# nVidia Shield
		if targettypes[1]=='Tegra-Android':
			if os.getenv('NV')==None:
				shieldfail = True
				continue
				
		# Create the build command
		cmd = '"' + vstudiopath + '" "' + fullpathname + '" /Build "' + target + '"'
		if verbose==True:
			print cmd
		sys.stdout.flush()
		error = subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)
		results.append((error,fullpathname,target))
		if error != 0:
			erroroccurred = 1
			if fatal==True:
				return error

	if xboxfail==True:
		print 'Xbox classic project detected but XDK was not installed'
		
	if xbox360fail==True:
		print 'Xbox 360 project detected but XEDK was not installed'
	
	if ps3fail==True:
		print 'PS3 project detected but SCE_PS3_ROOT was not found'

	if ps4fail==True:
		print 'PS4 project detected but SCE_ORBIS_SDK_DIR was not found'

	if shieldfail==True:
		print 'nVidia Shield project detected but NV was not found'

	if androidfail==True:
		print 'Android project detected but ANDROID_NDK was not found'

	return erroroccurred

#
# Build a Metrowerks Codewarrior file on MacOS
# Return 0 if no error, 1 if an error, 2 if
# Code Warrior was not found
#

def buildcodewarriormac(fileName,verbose,ignoreerrors):
	fileNamelower = fileName.lower()
	# Codewarrior version was not detected for Mac OSX
	if 'wii' in fileNamelower:
		return 0
	if 'nds' in fileNamelower:
		return 0
	if 'gcn' in fileNamelower:
		return 0

	if 'c10' in fileNamelower:
		cwfile = '/Applications/Metrowerks CodeWarrior 10.0/Metrowerks CodeWarrior/CodeWarrior IDE 10'
	elif 'cw9' in fileNamelower:
		cwfile = '/Applications/Metrowerks CodeWarrior 9.0/Metrowerks CodeWarrior/CodeWarrior IDE 9.6'
	else:
		print 'Codewarrior version was not detected'
		return 0

	mytempdir = os.path.join(os.path.dirname(fileName),'temp')
	errorFile = os.path.basename(fileName)
	errorList = os.path.splitext(errorFile)
	errorFile = os.path.join(mytempdir,errorList[0] + '.err')

	# Make the output folder for errors (If needed)

	burger.createfolderifneeded(mytempdir)

	# Create the build command

	cmd = 'cmdide -proj -bcwef "' + errorFile + '" -y "' + cwfile + '" -z Everything "' + fileName + '"'
	if verbose==True:
		print cmd
	sys.stdout.flush()
	error = subprocess.call(cmd,cwd=os.path.dirname(fileName),shell=True)
	return error

#
# Build a Metrowerks Codewarrior file on MacOS
# Return 0 if no error, 1 if an error, 2 if
# Code Warrior was not found
#

def buildcodewarriorwindows(fileName,verbose,ignoreerrors):

	fileNamelower = fileName.lower()
	# Don't use Codewarrior for Mac
	if 'mac' in fileNamelower:
		return 0
		
	# These targets build on Windows hosts
	if 'wii' in fileNamelower:
		print 'Can\'t build ' + fileName + ' yet!'
		return 0
	elif 'nds' in fileNamelower:
		print 'Can\'t build ' + fileName + ' yet!'
		return 0
	elif 'gcn' in fileNamelower:
		print 'Can\'t build ' + fileName + ' yet!'
		return 0
	elif 'w32' in fileNamelower or 'win' in fileNamelower:
		cwfile = os.getenv('CWFolder')
		if cwfile==None:
			print 'Can\'t build ' + fileName + '! CWFolder not set to Codewarrior 9.4 for Windows!'
			return 0
		# Note: CmdIDE is preferred, however, Codewarrior 9.4 has a bug
		# that it will die horribly if the pathname to it
		# has a space, so ide is used instead.
		cwfile = os.path.join(cwfile,'Bin','ide')
	else:
		print 'Codewarrior version was not detected for ' + fileName
		return 0

	mytempdir = os.path.join(os.path.dirname(fileName),'temp')
	errorFile = os.path.basename(fileName)
	errorList = os.path.splitext(errorFile)
	errorFile = os.path.join(mytempdir,errorList[0] + '.err')

	# Make the output folder for errors (If needed)

	burger.createfolderifneeded(mytempdir)

	# Create the build command
	# /s New instance
	# /t Project name
	# /b Build
	# /c close the project after completion
	# /q Close Codewarrior on completion
	
	cmd = '"' + cwfile + '" "' + fileName + '" /t Everything /s /c /q /b'
	if verbose==True:
		print cmd
	sys.stdout.flush()
	error = subprocess.call(cmd,cwd=os.path.dirname(fileName),shell=True)
	return error

#
# Given a .xcodeproj directory for XCode for MacOSX
# locate and extract all of the build targets
# available and return the list
#

def parsexcodeprojdir(fileName):

	# Start with an empty list
	
	targetlist = []
	fp = open(os.path.join(fileName,'project.pbxproj'))
	projectfile = fp.read().splitlines()
	fp.close()
	configurationfound = False
	for line in projectfile:
		# Look for this section. Immediately after it
		# has the targets
		if configurationfound==False:
			if 'buildConfigurations' in line:
				configurationfound=True
		else:
			# Once the end of the section is reached, end
			if ');' in line:
				break
			# Format 1DEB923608733DC60010E9CD /* Debug */,
			lineparts = line.rsplit()
			# The third entry is the data needed
			targetlist.append(lineparts[2])

	# Exit with the results
	return targetlist

#
# Build a Mac OS X XCode file
# Return 0 if no error, 1 if an error, 2 if
# XCode was not found
#

def buildxcode(results,fileName,verbose,ignoreerrors):

	# Get the list of build targets
	targetlist = parsexcodeprojdir(fileName)
	fileNamelower = fileName.lower()
	# Use XCode 3 off the root
	if 'xc3' in fileNamelower:
		# On OSX Lion and higher, XCode 3.1.4 is a separate folder
		xcodebuild = '/Xcode3.1.4/usr/bin/xcodebuild'
		if not os.path.isfile(xcodebuild):
			# Use the pre-Lion folder
			xcodebuild = '/Developer/usr/bin/xcodebuild'
    # Invoke XCode 4 or higher from the app store
	else:
		xcodebuild = '/Applications/Xcode.app/Contents/Developer/usr/bin/xcodebuild'

	# Is this version of XCode installed?
	if os.path.isfile(xcodebuild)!=True:
		print 'Can\'t build ' + fileName + ', the proper version of XCode is not installed'
		results.append((0,fileName))
		return 0

	# Build each and every target
	for target in targetlist:
		# Create the build command
		cmd = xcodebuild + ' -project "' + os.path.basename(fileName) + '" -alltargets -parallelizeTargets -configuration "' + target + '"'
		if verbose==True:
			print cmd
		sys.stdout.flush()
		error = subprocess.call(cmd,cwd=os.path.dirname(fileName),shell=True)
		results.append((error,fileName,target))
		if error != 0:
			if ignoreerrors==False:
				return error
	
	return 0

#
# Build a Codeblocks project
#
# Commands available as of 13.12
# --safe-mode
# --no-check-associations
# --no-dde
# --no-splash-screen
# --multiple-instance
# --debug-log
# --no-crash-handler
# --verbose
# --no-log
# --log-to-file
# --debug-log-to-file
# --rebuild
# --build
# --clean
# --target=
# --no-batch-window-close
# --batch-build-notify
# --script=
# --file=
#

def buildcodeblocks(fullpathname,verbose):
	
	if burger.getwindowshosttype()!=False:
		if fullpathname.endswith('osx.cbp'):
			return 0
		# Is Codeblocks installed?
		codeblockspath = os.getenv('CODEBLOCKS')
		if codeblockspath==None:
			print fullpathname + ' requires Codeblocks to be installed to build!'
			return 0
		codeblockspath = os.path.join(codeblockspath,'codeblocks')
		codeblocksflags = '--no-check-associations --no-dde --no-batch-window-close'
	else:
		if not fullpathname.endswith('osx.cbp'):
			return 0
		
		codeblockspath = '/Applications/Codeblocks.app/Contents/MacOS/CodeBlocks'
		codeblocksflags = '--no-ipc'
	# Create the build command
	cmd = '"' + codeblockspath + '" ' + codeblocksflags + ' --no-splash-screen --build "' + fullpathname + '" --target=Everything'
	if verbose==True:
		print cmd
	print cmd
	print 'Codeblocks is currently broken. Disabled for now'
	return 0
	return subprocess.call(cmd,cwd=os.path.dirname(fullpathname),shell=True)

#
# Detect the project type and add it to the list
#

def addproject(projects,fileName):

	# Only process project files

	baseName = os.path.basename(fileName)
	baseNamelower = baseName.lower()
	type = None
	priority = 50
	if baseNamelower=='prebuild.py':
		type = 'python'
		priority = 1
	elif baseNamelower.endswith('.slicerscript'):
		type = 'slicer'
		priority = 20
	elif baseNamelower.endswith('.rezscript'):
		type = 'makerez'
		priority = 25
	elif baseNamelower=='custombuild.py':
		type = 'python'
		priority = 40
	elif baseNamelower.endswith('.sln'):
		type = 'visualstudio'
		priority = 45
	elif baseNamelower.endswith('.mcp'):
		type = 'codewarrior'
	elif baseNamelower=='makefile' or baseNamelower.endswith('.wmk'):
		type = 'watcommakefile'
	elif baseNamelower.endswith('.xcodeproj'):
		type = 'xcode'
	elif baseNamelower.endswith('.cbp'):
		type = 'codeblocks'
	elif baseNamelower=='doxyfile':
		type = 'doxygen'
		priority = 90
	elif baseNamelower=='postbuild.py':
		type = 'python'
		priority = 99

	if type!=None:
		projects.append((fileName,type,priority))
		return True
	return False


#
# Scan a folder for files that need to be 'built'
#

def getprojects(projects,workingDir):

	#
	# Get the list of files in this directory
	#
	
	nameList = os.listdir(workingDir)

	for baseName in nameList:
		fileName = os.path.join(workingDir,baseName)
		addproject(projects,fileName)
		

#
# Recursively scan a folder and look for any project files than need to
# be built. Returns all files in the list "projects"
#

def recursivegetprojects(projects,workingDir):

	# Iterate through this folder and build the contents

	getprojects(projects,workingDir)
			
	nameList = os.listdir(workingDir)
	for baseName in nameList:
		baseNameLower = baseName.lower()
		
		# Skip known folders that contain temp files and not potential projects
		if baseNameLower=='temp':
			continue
		if baseNameLower=='bin':
			continue
		if baseNameLower=='appfolder':
			continue
		# Xcode folders don't have subprojects inside
		if baseNameLower.endswith('.xcodeproj'):
			continue
		# Codewarrior droppings (Case sensitive)
		if baseName.endswith('_Data'):
			continue
		if baseName.endswith(' Data'):
			continue
		fileName = os.path.join(workingDir,baseName)

		# Handle the directories found
		if os.path.isdir(fileName):
			recursivegetprojects(projects,fileName)
			
#
# Command line shell
#

def main():

	# Don't clutter my system with pyc files
	sys.dont_write_bytecode = True
	
	# Was Burgerlib already installed?
	
	sdks = burger.getsdksfolder()
	
	# Where is perforce?
	
	perforce = burger.whereisp4()
	
	# Failsafe to make sure clean is only run from within
	# the Burgerlib projects folder

	workingDir = os.getcwd()
	rootPath = os.path.dirname(sdks)
	if (not workingDir.lower().startswith(rootPath.lower())):
		print 'build can only be run from within the "' + rootPath + '" folder'
		return -1
	
	# Parse the command line
	
	parser = argparse.ArgumentParser(
		description='Build project files. Copyright by Rebecca Ann Heineman. Builds *.sln, *.mcp, *.cbp, *.rezscript, *.slicerscript, doxyfile, makefile and *.xcodeproj files')
	parser.add_argument('-r', dest='recursive', action='store_true',
		default=False,
		help='Perform a recursive build.')
	parser.add_argument('-f', dest='fatal', action='store_true',
		default=False,
		help='Quit immediately on any error.')
	parser.add_argument('-d',dest='directories',action='append',
		help='List of directories to build in.')
	parser.add_argument('-docs',dest='documentation',action='store_true',
		default=False,
		help='Compile Doxyfile files.')
	parser.add_argument('-v','-verbose',dest='verbose',action='store_true',
		default=False,
		help='Verbose output.')
	parser.add_argument('args',nargs=argparse.REMAINDER,help='project filenames')

	args = parser.parse_args()
	
	verbose = args.verbose

	#
	# List of files to build
	#
	
	projects = []

	#
	# Get the list of directories to process
	#
	
	directories = args.directories
	if not directories:
		# Use the current working directory instead
		directories = [workingDir]
		if args.recursive==False:
		
			#
			# If any filenames were passed, add them to the possible projects list
			#
			
			if not len(args.args)==0:
				for filename in args.args:
					projectname = os.path.join(workingDir,filename)
					if addproject(projects,os.path.join(workingDir,projectname))==False:
						print 'Error: ' + projectname + ' is not a known project file'
						return 10
					
	#
	# Create the list of projects that need to be built
	#
	
	if len(projects)==0:
		for mydirName in directories:
			if args.recursive==False:
				getprojects(projects,mydirName)
			else:
				recursivegetprojects(projects,mydirName)

	#
	# If the list is empty, just exit now
	#
	
	if len(projects)==0:
		print 'Nothing to build'
		return 0
	
	#
	# Sort the list by priority (The third parameter is priority from 1-99
	#
	projects = sorted(projects,key=lambda entry:entry[2])
	
	#
	# Let's process each and every file
	#
	
	#
	# args.documentation exists because building Doxygen files
	# are very time consuming
	#
	
	results = []
	anerroroccured = False
	for project in projects:
		fullpathname = project[0]
		type = project[1]
		error = 0
		
		# Is it a python script?
		
		if type=='python':
			if os.path.isfile(fullpathname):
				if verbose==True:
					print 'Invoking ' + fullpathname
				error = invokepython(fullpathname)
				results.append((error,fullpathname))

		# Is it a slicer script?
		
		elif type=='slicer':
			if os.path.isfile(fullpathname):
				error = buildslicerscript(fullpathname,verbose)
				results.append((error,fullpathname))

		# Is it a makerez script?
		
		elif type=='makerez':
			if os.path.isfile(fullpathname):
				error = buildrezscript(fullpathname,verbose)
				results.append((error,fullpathname))

		# Is this a doxygen file?
		
		elif type=='doxygen':
			if args.documentation==True:
				if os.path.isfile(fullpathname):
					error = builddoxygen(fullpathname,verbose)
					results.append((error,fullpathname))
		
		# Is this a Watcom Makefile?
		
		elif type=='watcommakefile':
			if burger.getwindowshosttype()!=False:
				if os.path.isfile(fullpathname):
					error = buildwatcommakefile(results,fullpathname,verbose,args.fatal)
				
		# Visual studio solution files?

		elif type=='visualstudio':	
			if burger.getwindowshosttype()!=False:
				if os.path.isfile(fullpathname):
					error = buildvisualstudio(results,fullpathname,verbose,args.fatal)

		# Metrowerks Codewarrior files?

		elif type=='codewarrior':
			if os.path.isfile(fullpathname):
				if burger.getwindowshosttype()!=False:
					error = buildcodewarriorwindows(fullpathname,verbose,True)
					results.append((error,fullpathname,'Everything'))
				elif burger.iscodewarriormacallowed()==True:
					error = buildcodewarriormac(fullpathname,verbose,True)
					results.append((error,fullpathname,'Everything'))

		# XCode project file?	
		elif type=='xcode':
			if burger.getmachosttype()!=False:
				if os.path.isdir(fullpathname):
					error = buildxcode(results,fullpathname,verbose,True)

		# Codeblocks project file?
		elif type=='codeblocks':
			if os.path.isfile(fullpathname):
				error = buildcodeblocks(fullpathname,verbose)
				results.append((error,fullpathname,'Everything'))
					
		#Abort on error?
		if error!=0:
			anerroroccured = True
			if args.fatal==True:
				break
		
	# List all the projects that failed
			
	if anerroroccured==False:
		print 'Build successful!'
		error = 0
	else:
		print 'Errors detected in the build.'
		for entry in results:
			# Only print entries that failed
			if entry[0]!=0:
				output = 'Error %d in file %s' % (entry[0],entry[1])
				if len(entry)==3:
					output = output + ' target ' + entry[2]
				print output
		if error==0:
			error = 10
	return error

# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main())
