#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Useful subroutines
#

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import os
import shutil
import subprocess
import platform
import sys
from cStringIO import StringIO

#
# Handy class for capturing stdout from tools and
# python itself
#

class interceptstdout(list):
    def __enter__(self):
    
    	# Attach a StringIO to stdout

        self._stdout = sys.stdout
        sys.stdout = self._stringio = StringIO()
        return self

    def __exit__(self, *args):
    
    	# Restore stdout on exit

        self.extend(self._stringio.getvalue().splitlines())
        sys.stdout = self._stdout
        
#
# Return the path of the sdks folder
#

def getsdksfolder():
	sdks = os.getenv('SDKS')
	if sdks==None:
		print 'The environment variable "SDKS" is not set'
		# Use the location of this file as a reference to where SDKS
		# could be
		sdks = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
	return sdks

#
# Given a pathname, detect if the folder exists
# If not, create it
#

def createfolderifneeded(foldername):
	if not os.path.isdir(foldername):
		os.makedirs(foldername)

#
# Given a pathname, detect if a file exists.
# If so, delete it
#

def deletefileifpresent(filename):
	if os.path.isfile(filename):
		os.remove(filename)

#
# Convert a string to a string array (list)
#

def converttoarray(input):
	# If empty, return an empty array
	if input==None:
		input = []
	elif not type(input) is list:
		# Convert a single entry into an array
		input = [input]
	return input

#
# Convert a filename from linux/mac to windows format
#

def converttowindowsslashes(input):
	return input.replace('/','\\')
	
#
# Convert a filename from windows to linux/mac format
#

def converttolinuxslashes(input):
	return input.replace('\\','/')

#
# Convert a filename from linux/mac to windows format
# and ensure the last character is a slash
# This is needed for visual studio projects
#

def converttowindowsslasheswithendslash(input):
	input = converttowindowsslashes(input)
	if not input.endswith('\\'):
		input.append('\\')
	return input
		
#
# Node class for creating directory trees
# Needed for some projects that have to store
# file entries in nested trees
#

class node(object):
	def __init__(self,value,children = []):
		self.value = value
		self.children = children
	def __repr__(self,level=0):
		ret = "\t"*level+repr(self.value)+"\n"
		for child in self.children:
			ret += child.__repr__(level+1)
		return ret
		
#
# Return the machine this script is running on, 'windows', 'macosx',
# 'linux' or 'unknown'
#

def hostmachine():

	# Only windows reports as NT

	if os.name == 'nt':
		return 'windows'

	# BSD and GNU report as posix

	if os.name == 'posix':
		
		# MacOSX is the Darwin kernel
		
		if platform.system() == 'Darwin':
			return 'macosx'
		
		# Assume linux (Tested on Ubuntu and Red Hat)

		return 'linux'

	# Surrender Dorothy
	
	return 'unknown'

#
# C# applications can launch as is on Windows platforms,
# however, on Mac OSX and Linux, it must be launched
# from mono. Determine the host machine and if not
# windows, automatically prepend "mono" to
# the application's name to properly launch it
#
# This will also encase the name in quotes in case there are
# spaces in the pathname
#
	
def fixcsharp(csharpapplicationpath):
	if hostmachine() != 'windows':
		csharpapplicationpath = 'mono "' + apppath + '"'
	else:
		csharpapplicationpath = '"' + csharpapplicationpath + '"'
	return csharpapplicationpath

#
# Return False if the host is not Windows, x86 if it's a 32 bit host
# and x64 if it's a 64 bit host, and possibly 'arm' if an arm host
#

def getwindowshosttype():

	# Not windows?
	
	if os.name != 'nt':
		return False
		
	# Test the CPU for the type
	
	machine = platform.machine()
	if machine=='AMD64':
		return 'x64'
	return 'x86'

#
# Return False if the host is not Mac OSX. 'ppc' if it's a Power PC based
# system, 'x86' for 32 bit intel and 'x64' for 64 bit intel
#

def getmachosttype():

	# Mac/Linux?
	if os.name != 'posix':
		return False
		
	# Not linux?
	
	if platform.system() != 'Darwin':
		return False

	#
	# Since it's a mac, query the Mac OSX cpu type
	# using the MacOSX python extensions
	#
	
	version,_,cpu = platform.mac_ver()
	if cpu=='x86' or cpu=='x86_64':
		return 'x86'
	return 'ppc'

#
# Return the location of Doxygen's executable
#

def whereisdoxygen():

	# Is Doxygen installed on windows?

	if getwindowshosttype()!=False:
		doxygenpath = os.getenv('DOXYGEN')
		if doxygenpath==None:
			doxygenpath = os.getenv('ProgramFiles')
			if doxygenpath!=None:
				doxygenpath = os.path.join(doxygenpath,'doxygen')
				
		if doxygenpath!=None:
			doxygenpath = os.path.join(doxygenpath,'bin','doxygen.exe')
			if not os.path.isfile(doxygenpath):
				doxygenpath = None
				
		if doxygenpath==None:
			print 'Doxygen needs to be installed to build documentation!'
			return None
			
		return doxygenpath
		
	# MacOSX has it hidden in the application
	elif getmachosttype()!=False:
		doxygenpath = '/Applications/Doxygen.app/Contents/Resources/doxygen'
		if not os.path.isfile(doxygenpath):
			print 'Doxygen needs to be installed in your Applications folder to build documentation!'
			return None
		return doxygenpath
		
	return 'doxygen'
	
#
# Return the location of the p4 executable
#

def whereisp4():

	#
	# Is the folder already specified?
	#
	
	perforcedirectory = os.getenv('PERFORCE')
	if perforcedirectory!=None:
		return '"' + os.path.join(perforcedirectory,'p4') + '"'

	#
	# Use the defaults
	#
	
	if hostmachine() == 'windows':
		# Hard code on windows
		return '"' + os.path.expandvars('${ProgramFiles}\Perforce\p4') + '"'

	# Use the local copy of the p4 client (Universal binary)
			
	if hostmachine() == 'macosx':
		return '"' + os.path.join(os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),'macosx','bin'),'p4') + '"'

	# Use the default directory path
	return 'p4'
	
#
# Given a list of files, checkout (Edit) them in perforce
#

def perforceedit(files):

	# Get the p4 executable

	perforce = whereisp4()

	if type(files) is not list:
		files = [files]
		
	for file in files:
		cmd = perforce + ' edit "' + os.path.abspath(file) + '"'
		error = subprocess.call(cmd,shell=True)
		if error!=0:
			return error
	return 0	

#
# Compare text files for equality, return True if equal
#

def comparefiles(filename1,filename2):

	# Are they the same size?
	
	try:
		f1size = os.path.getsize(filename1)
		f2size = os.path.getsize(filename2)
	except:
		return False

	# Not the same size?
	if f1size != f2size:
		return False

	# Do a data compare as a text file
	
	try:
		f1 = open(filename1,'r')
		fileOneLines = f1.readlines()
		f1.close()

	except:
		f1.close()
		return False
		
	try:
		f2 = open(filename2,'r')
		fileTwoLines = f2.readlines()
		f2.close()
		
	except:
		f2.close()
		return False
	
	# Compare the file contents
	
	x = 0
	for i in fileOneLines:
		if i != fileTwoLines[x]:
			return False
		x += 1
		
	# It's a match!

	return True

#
# Compare text file and a StringIO string for equality, return True if equal
#

def comparefiletostring(filename,string):

	#
	# Do a data compare as a text file
	#
	
	f1 = None
	try:
		f1 = open(filename,'r')
		fileOneLines = f1.readlines()
		f1.close()

	except:
		if f1!=None:
			f1.close()
		return False
	
	#
	# Compare the file contents taking into account
	# different line endings
	#
	
	fileTwoLines = string.getvalue().splitlines(True)
	f1size = len(fileOneLines)
	f2size = len(fileTwoLines)
	
	#
	# Not the same size?
	#
	
	if f1size != f2size:
		return False

	x = 0
	for i in fileOneLines:
		if i != fileTwoLines[x]:
			return False
		x += 1
		
	# It's a match!

	return True
	
#
# This function assumes version control is with perforce!
#
# Get the last change list and create a header
# with this information (Only modify the output file if 
# the contents have changed)
#

def makeversionheader(workingdir,outputfilename):

	# Work filename
	p4tempfilename = 'p4tempfilename1234.h'
	p4temppathname = os.path.join(workingdir,p4tempfilename)
	
	#
	# Get the last change list
	# Parse "Change 3361 on 2012/05/15 13:20:12 by burgerbecky@burgeroctocore 'Made a p4 change'"
	# -m 1 / Limit to one entry
	# -t / Display the time
	# -l / Print out the entire changelist description
	#

	p4exe = whereisp4()
	cmd = p4exe + ' changes -m 1 -t -l ...#have > ' + p4tempfilename
	error = subprocess.call(cmd,cwd=workingdir,shell=True)
	if error!=0:
		# Uh oh...
		deletefileifpresent(p4temppathname)
		print 'Error in calling ' + cmd
		return error
		
	#
	# Parse out the file contents
	#
		
	p4tempfp = open(p4temppathname,'r')
	tempdata = p4tempfp.read().strip()
	p4tempfp.close()
	p4changes = tempdata.split(' ')

	#
	# Get the p4 client
	# Parse "P4CLIENT=burgeroctocore (config)"
	#

	cmd = p4exe + ' set P4CLIENT > ' + p4tempfilename
	error = subprocess.call(cmd,cwd=workingdir,shell=True)
	if error!=0:
		# The P4CLIENT query failed!
		deletefileifpresent(p4temppathname)
		print 'Error in calling ' + cmd
		return error

	#
	# Parse out the P4CLIENT query
	#
	
	p4tempfp = open(p4temppathname,'r')
	tempdata = p4tempfp.read().strip()
	p4tempfp.close()
	p4clients = tempdata.split(' ')
	p4clients = p4clients[0].split('=')

	#
	# Get the p4 user
	# Parse "P4USER=burgerbecky (config)"
	#

	cmd = p4exe + ' set P4USER > ' + p4tempfilename
	error = subprocess.call(cmd,cwd=workingdir,shell=True)
	if error!=0:
		# The P4USER query failed!
		deletefileifpresent(p4temppathname)
		print 'Error in calling ' + cmd
		return error

	#
	# Parse out the P4USER query
	#
	
	p4tempfp = open(p4temppathname,'r')
	tempdata = p4tempfp.read().strip()
	p4tempfp.close()
	os.remove(p4temppathname)
	p4users = tempdata.split(' ')
	p4users = p4users[0].split('=')

	#
	# Name of the temp work file
	#

	tempheaderfile = os.path.join(workingdir,'versioninfo1234.h')
	fp = open(tempheaderfile,'w')
	
	#
	# Write out the header
	#

	fp.write(
		'/***************************************\n'
		'\n'
		'\tThis file was generated by a call to\n'
		'\tburger.makeversionheader() from a build\n'
		'\tpython script\n'
		'\n'
		'***************************************/\n'
		'\n'
		'#ifndef __VERSION_H__\n'
		'#define __VERSION_H__\n'
		'\n')
	
	if len(p4changes)>4:
		fp.write('#define P4_CHANGELIST ' + p4changes[1] + '\n')
		fp.write('#define P4_CHANGEDATE "' + p4changes[3] + '"\n')
		fp.write('#define P4_CHANGETIME "' + p4changes[4] + '"\n')

	if len(p4clients)>1:
		fp.write('#define P4_CLIENT "' + p4clients[1] + '"\n')
	
	if len(p4users)>1:
		fp.write('#define P4_USER "' + p4users[1] + '"\n\n#endif\n')
	fp.close()

	#
	# Check if the file is different than what's already stored on
	# the drive
	#
	
	if os.path.isfile(outputfilename)!=True or \
		comparefiles(tempheaderfile,outputfilename)!=True:
		print 'Copying ' + tempheaderfile + ' -> ' + outputfilename
		try:
			shutil.copyfile(tempheaderfile,outputfilename)
		except IOError, e:
			os.remove(tempheaderfile)
			print e
			return 2
	
	#
	# Clean up
	#
			
	os.remove(tempheaderfile)
	return 0
	
#
# Return True if CodeWarrior for Mac OS can be run
# on a PowerPC compatible Mac
#

def iscodewarriormacallowed():

	# Test if a mac

	if os.name == 'posix':
		# Get the Mac OS version number
		version,_,cpu = platform.mac_ver()
		
		# Convert 10.5.8 to 10.5
		
		digits = version.split('.')
		
		# Snow Leopard (10.6) supports Rosetta
		# Lion (10.7) and Mountain Lion (10.8) do not
		
		if float(digits[0])==10:
			if float(digits[1])<7:
				return True
			
	# Can't run, not a mac or Power PC native or emulation isn't supported
	return False
	
#
# Return True if the source file is newer then the destination file
# by checking the modification times
#

def isthesourcenewer(src,dest):
	# If there is a destination file, check the modification times
	try:
		srctime = os.path.getmtime(src)
	except:
		return 2

	try:
		desttime = os.path.getmtime(dest)
	except:
		return True
		
	# Is the source newer?
	if (srctime<=desttime):
		return False
	return True
	
#
# Copy a file only if the destination is
# missing or is older than the source file
# 
# Returns 0 if no error
#

def copyfileifneeded(src,dest):

	# If there is a destination file, check the modification times

	if isthesourcenewer(src,dest)==True:

		# Copy the file

		print 'Copying ' + src + ' -> ' + dest
		try:
			shutil.copyfile(src,dest)
		except IOError, e:
			print e
			return 2
	return 0

#
# Copy a file only if needed and check out the destination file before the copy
#

def copyfileandcheckoutifneeded(src,dest):
		
	if isthesourcenewer(src,dest)==True:
	
		# Alert perforce that the file is to be modified
		
		perforceedit(dest)
		
		# Copy the file

		print 'Copying ' + src + ' -> ' + dest
		try:
			shutil.copyfile(src,dest)
		except IOError, e:
			print e
			return 2
	return 0

#
# Copy all of the files in a directory into a new directory
# Note: This is a recursive function
#

def copydirectoryifneeded(src,dest,exceptions = []):
	
	#
	# Make sure the output folder exists
	#
	
	createfolderifneeded(dest)
	
	nameList = os.listdir(src)
	for baseName in nameList:
		skip = False
		for item in exceptions:
			if baseName.endswith(item):
				skip = True
		if skip==False:
			fileName = os.path.join(src,baseName)

			# Handle the directories found
			if os.path.isdir(fileName):
				# Recursive!
				error = copydirectoryifneeded(fileName,os.path.join(dest,baseName),exceptions)
			else:
				error = copyfileifneeded(fileName,os.path.join(dest,baseName))

			if error != 0:
				return error

	return 0



