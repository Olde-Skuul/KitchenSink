#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Remove all temporary files in a project's folder
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
import burger

#
# Dispose of a folder and print it's name if need be
#

def removefolder(foldername,verbose):
	if verbose==True:
		print 'Deleting the folder ' + foldername
	shutil.rmtree(foldername,ignore_errors=True)

#
# Remove data that's stored globally
# so it's only needed to be invoked once
# for either a once shot or recursive clean
#

def removeglobaldata(verbose):

	objectsremoved = 0
	
	#
	# Metrowerks has some defaults it leaves on build
	# but only for the Windows hosts
	#
			
	if (os.name == 'nt'):
		localAppData = os.getenv('LOCALAPPDATA')
		if (localAppData != None):
			defaultCww = os.path.join(localAppData,'Metrowerks','default.cww')
			if os.path.isfile(defaultCww):
				if verbose==True:
					print 'Deleting the file ' + defaultCww
				os.remove(defaultCww)
				objectsremoved = objectsremoved+1
	
	return objectsremoved

#
# Remove all files with specific extensions
#

def removebyfileextension(workingDir,extensionList,verbose):

	objectsremoved = 0

	# Get the files in the directory
	nameList = os.listdir(workingDir)
	for baseName in nameList:
		fileName = os.path.join(workingDir,baseName)
		# Is it a file?
		if os.path.isfile(fileName):
			# Check against the extension list
			for extension in extensionList:
				if baseName.endswith(extension):
					# Bye bye!
					if verbose==True:
						print 'Deleting the file ' + fileName
					os.remove(fileName)
					objectsremoved = objectsremoved+1
					break
					
	return objectsremoved

#
# Perform a "clean" operation on the current folder
#

def clean(workingDir,verbose):

	# Iterate through this folder and clean out the contents

	if verbose==True:
		print 'Cleaning the directory "' + workingDir + '"'
	
	objectsremoved = 0

	# If the file Doxyfile exists, then assume that this is a documentation folder

	docs=False
	docsfilename = os.path.join(workingDir,'Doxyfile')
	if os.path.isfile(docsfilename):
		docs=True

	# Iterate over all the files/folders for things to purge

	nameList = os.listdir(workingDir)
	for baseName in nameList:
		fileName = os.path.join(workingDir,baseName)

		# Handle the directories found
		if os.path.isdir(fileName):
		
			#
			# These directories get nuked
			# _Data and Data are Codewarrior temp files
			# appfolder is obsolete
			# temp is obvious ;)
			# ipch is from Visual Studio
			# bin is the final output folder
			# build is from xcode
			#

			if baseName.endswith('_Data') or \
				baseName.endswith(' Data') or \
				baseName == 'build' or \
				baseName == 'appfolder' or \
				baseName == 'temp' or \
				baseName == 'ipch' or \
				baseName == 'bin' :
				removefolder(fileName,verbose)
				objectsremoved = objectsremoved+1
		
			#
			# Is it an XCode project folder?
			#
			
			elif baseName.endswith('.xcodeproj'):
			
				# Remove a user's pref files

				objectsremoved = objectsremoved + \
					removebyfileextension(fileName,['.mode1v3','.pbxuser'],verbose)

				xcuserdata = os.path.join(fileName,'xcuserdata')
				if os.path.isdir(xcuserdata):
					removefolder(xcuserdata,verbose)
					objectsremoved = objectsremoved + 1

				xcworkspace = os.path.join(fileName,'project.xcworkspace')
				if os.path.isdir(xcworkspace):
					removefolder(xcworkspace,verbose)
					objectsremoved = objectsremoved + 1

		# Files to delete...
		# .suo is from Visual Studio
		# .user is from Visual Studio
		# .ncb is from Visual Studio
		# .err is from Watcom and CodeWarrior on Mac and Windows
		# .sdf is from Visual Studio
		# .pyc is from python
		# .layout.cbTemp is from CodeBlocks
		# .DS_Store is from the Mac Finder
		
		# If Doxygen is found
		# .chm is a documentation file
		# .chw is a chm index/history file
		# .tmp Doxygen work file
		
		elif os.path.isfile(fileName):
			# These file extensions are history
			if baseName.endswith('.suo') or \
				baseName.endswith('.user') or \
				baseName.endswith('.ncb') or \
				baseName.endswith('.err') or \
				baseName.endswith('.sdf') or \
				baseName.endswith('.pyc') or \
				baseName.endswith('.layout.cbTemp') or \
				baseName == '.DS_Store':
				if verbose==True:
					print 'Deleting file ' + fileName
				try:
					os.remove(fileName)
				except Exception,e:
					print e
				objectsremoved = objectsremoved+1
				
			# Remove CodeBlocks files ONLY if a codeblocks project is present
			# to prevent accidental deletion of legitimate files
			
			elif baseName.endswith('.layout') or \
				baseName.endswith('.depend'):
				if os.path.isfile(os.path.join(workingDir,os.path.splitext(baseName)[0] + '.cbp')) :
					if verbose==True:
						print 'Deleting file ' + fileName
					try:
						os.remove(fileName)
					except Exception,e:
						print e
					objectsremoved = objectsremoved+1
					
			# Is it possible to have doxygen leftovers?
			
			elif docs==True:
				if baseName=='doxygenerrors.txt' or \
					baseName.endswith('.chm') or \
					baseName.endswith('.chw') or \
					baseName.endswith('.tmp'):
						if verbose==True:
							print 'Deleting file ' + fileName
						os.remove(fileName)
						objectsremoved = objectsremoved+1


	return objectsremoved

#
# Perform a "clean" operation on the current folder and every folder
# down the line recursively
# Returns the number of objects removed (In total)
#

def recursiveclean(workingDir,verbose):

	# Iterate through this folder and clean out the contents

	# Perform the clean first, to prevent iterating down any
	# folders that will be erased anyways

	objectsremoved = clean(workingDir,verbose)

	# Now, iterate through the current folder for folders to recurse through
		
	nameList = os.listdir(workingDir)
	for baseName in nameList:
		fileName = os.path.join(workingDir,baseName)
		# Handle the directories found
		if os.path.isdir(fileName):
			objectsremoved = objectsremoved + recursiveclean(fileName,verbose)

	return objectsremoved
	
#
# Command line shell
#

def main():

	# Was Burgerlib already installed?
	
	sdks = burger.getsdksfolder()
	
	#
	# Failsafe to make sure clean is only run from within
	# the Burgerlib projects folder
	# 
	# This is to prevent someone from accidentally deleting
	# a shared drive's file contents
	#

	workingDir = os.getcwd()
	rootPath = os.path.dirname(sdks)
	
	# Parse the command line
	
	parser = argparse.ArgumentParser(
		description='Remove project output files. Copyright by Rebecca Ann Heineman',
		usage='clean [-h] [-r] [-v]')
	parser.add_argument('-r','-all', dest='all', action='store_true',
		default=False,
		help='Perform a recursive clean')
	parser.add_argument('-f','-force', dest='force', action='store_true',
		default=False,
		help='Disable the check if in the "burger" folder')
	parser.add_argument('-v','-verbose', dest='verbose', action='store_true',
		default=False,
		help='Verbose output')

	args = parser.parse_args()
	if args.force==False:
		if (not workingDir.lower().startswith(rootPath.lower())):
			print 'clean can only be run from within the "' + rootPath + '" folder'
			return 1

	# True if debug spew is requested
	
	verbose = args.verbose

	# Get rid of one shot data
	
	objectsremoved = removeglobaldata(verbose)
	
	# Get rid of local data
	
	if args.all==False:
		objectsremoved = clean(workingDir,verbose) + objectsremoved
	else:
		if verbose==True:
			print 'Performing a recursive clean'
		objectsremoved = recursiveclean(workingDir,verbose) + objectsremoved
	
	if objectsremoved != 0:
		print 'Removed ' + str(objectsremoved) + ' objects'
	else:
		print 'No action performed, already clean'
	return 0
		

# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main())