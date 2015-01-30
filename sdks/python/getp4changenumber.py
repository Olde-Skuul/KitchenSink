#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Prints the current change list number to stdout
#

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import os
import subprocess
import sys
import burger
import shlex

#
# This function assumes version control is with perforce!
#
# Get the last change list and create a header
# with this information (Only modify the output file if 
# the contents have changed)
#

def getp4changenumber(workingdir):
	
	#
	# Get the last change list
	# Parse "Change 3361 on 2012/05/15 by burgerbecky@burgeroctocore 'Made a p4 change'"
	# -m 1 / Limit to one entry
	#

	p4exe = burger.whereisp4()
	cmd = p4exe + ' changes -m 1 ...#have'
	proc = subprocess.Popen(shlex.split(cmd),stdout=subprocess.PIPE,stderr=subprocess.PIPE,cwd=workingdir,shell=True)
	output,err = proc.communicate()
	error = proc.returncode
	
	if error!=0:
		# Uh oh...
		print 'Error in calling ' + cmd
		return error
		
	#
	# Parse out the file contents
	#
	
	p4changes = output.split(' ')

	#
	# Print the change number
	#
	
	print p4changes[1]
	return error

#
# Command line shell
#

def main():
	return getp4changenumber(os.getcwd())

# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main())
	
