#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# After XCode is done building a command line tool,
# check out the tool from Perforce and update it.
# This is part of the automation process to keep
# all the Burgerlib command line tools up to date
#
# XCode documentation is found here
# http://developer.apple.com/library/mac/#documentation/DeveloperTools/Reference/XcodeBuildSettingRef/1-Build_Setting_Reference/build_setting_ref.html#//apple_ref/doc/uid/TP40003931-CH3-SW105
#

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import os
import sys
import subprocess
import shutil

#
# Command line shell
#

def main():

	# Was Burgerlib already installed?
	
	sdks = os.getenv('SDKS')
	if sdks==None:
		print 'The environment variable "SDKS" is not set, check if your ~/.MacOSX/environment.plist file has been set up properly'
		return -1

	# Only copy the Release build

	buildstyle = os.getenv('BUILD_STYLE')
	if buildstyle!='Release':
		return 0

	# Get the name of the application

	targetname = os.getenv('TARGET_NAME')
	destfile = sdks + '/mactools/' + targetname

	# Is it already checked out?
	# If not, check out from Perforce

	if not os.access(destfile, os.W_OK):
		cmd = sdks + '/mactools/p4 edit "' + destfile + '"'
		print 'Checking out ' + targetname + ' from Perforce'
		sys.stdout.flush()
		error = subprocess.call(cmd,stdout=sys.stdout,stderr=sys.stdout,shell=True)
		if error!=0:
			return error
		if not os.access(destfile, os.W_OK):
			print destfile + ' is not writable!!'
			return -1

	# Copy the tool to the Mac OSX tools folder

	targetdir = os.getenv('TARGET_BUILD_DIR')
	srcfile = targetdir + os.sep + targetname
	try:
		shutil.copy2(srcfile,destfile)
	except (IOError, os.error), why:
		print 'Tried to copy ' + srcfile + ' to ' + destfile
		print str(why)
		return -1

	print 'Copied ' + targetname + ' to ' + sdks + '/mactools'
	return 0

# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main())
