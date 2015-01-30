#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import burger
import os
import sys
	
#
# Copy up the common command line batch files to sdks/windows/bin/x86
#

def main(workingDir):

	#
	# Locate the SDKs folder so the files can be copied there
	#
	
	sdks = burger.getsdksfolder()

	#
	# Files to copy if changed
	#
	
	batchfiles = [
		'build.cmd',
		'candle.cmd',
		'clean.cmd',
		'disasmx36.cmd',
		'doxygen.cmd',
		'getp4changenumber.cmd',
		'git.cmd',
		'light.cmd',
		'makeprojects.cmd',
		'p4.cmd',
		'rebuild.cmd',
		'wdisasm.cmd'
		]
	
	#
	# Ensure the destination directory exists
	#
	
	destfolder = os.path.join(sdks,'windows','bin','x86')
	burger.createfolderifneeded(destfolder)

	#
	# Copy all the changed files
	#

	error = 0
	for item in batchfiles:
		
		#
		# If the file had changed, update it in perforce
		#
		
		sourcefile = os.path.join(workingDir,item)
		destfile = os.path.join(destfolder,item)
		if os.path.isfile(destfile)!=True or \
			burger.comparefiles(sourcefile,destfile)!=True:
			
			error = burger.copyfileandcheckoutifneeded(sourcefile,destfile)
			if error!=0:
				break

	return error
		
# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main(os.path.dirname(os.path.abspath(__file__))))

