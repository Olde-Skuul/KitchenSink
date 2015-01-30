#!/bin/bash
# -*- coding: utf-8 -*-

# This script will copy a compiled libary using 
# Metrowerks Codewarrior 10 for MacOSX into the
# Perforce repository

# Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

# It is released under an MIT Open Source license. Please see LICENSE
# for license details. Yes, you can use it in a
# commercial title without paying anything, just give me a credit.
# Please? It's not like I'm asking you for money!

# Docs for environment variables are found in Targeting_Mac_OS.pdf
# Page 345-350

# Check the file out with perforce

"${SDKS}/macosx/bin/p4" edit "${SDKS}/mac/burgerlib/$MW_OUTPUT_NAME"

# Copy the output file into the final location

cp "$MW_OUTPUT_FILE" "${SDKS}/mac/burgerlib/$MW_OUTPUT_NAME"
