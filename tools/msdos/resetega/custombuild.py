#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Build the MS DOS .COM tool resetega
#

#
# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com
#
# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!
#

import os
import subprocess
import burger
import sys

#
# Build the dos utility resetega.com
#

def main(workingDir):

	#
	# The tool to build a DOS app only exists under windows
	#
	
	if burger.hostmachine()!='windows':
		return 0
		
	#
	# Create the output folder
	#
	
	binfolder = os.path.join(workingDir,'bin')
	burger.createfolderifneeded(binfolder)

	# 
	# Build if needed
	#
	
	comfile = os.path.join(binfolder,'resetega.com')
	sourcefile = os.path.join(workingDir,'resetega.i86')

	if burger.isthesourcenewer(sourcefile,comfile):

		#
		# Use jwasm to create a COM file
		#

		cmd = 'jwasm -bin -Fo"' + comfile + '" "' + sourcefile + '"'
		error = subprocess.call(cmd,cwd=workingDir,shell=True)
		if error!=0:
			return error
	
		#
		# Update in perforce
		#
		
		sdks = burger.getsdksfolder();
		destfile = os.path.join(sdks,'dos','bin','resetega.com')
		error = burger.copyfileandcheckoutifneeded(comfile,destfile)
		if error!=0:
			return 0
	
	return 0
		
# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main(os.path.dirname(os.path.abspath(__file__))))


