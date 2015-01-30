#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Rebuild a project
#

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

import build
import clean
import sys

#
# Command line shell
#

def main():
	
	# Clean, then build. Couldn't be simpler!
	
	error = clean.main()
	if error!=0:
		return error
	return build.main()

# 
# If called as a function and not a class,
# call my main
#

if __name__ == "__main__":
	sys.exit(main())
