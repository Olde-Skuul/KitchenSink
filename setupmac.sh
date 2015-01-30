#!/bin/bash
cd $0/..

# Get the current directory
SCRIPTDIR="$( cd "$( dirname "$0" )" && pwd )"

# Make sure the environment variables are set

# The standard way is to add the variables to ~/.MacOSX/environment.plist
if [ ! -d ~/.MacOSX ]; then mkdir ~/.MacOSX; fi
defaults write ~/.MacOSX/environment SDKS -string "$SCRIPTDIR/sdks"
defaults write ~/.MacOSX/environment P4CONFIG -string "p4config"
plutil -convert binary1 ~/.MacOSX/environment.plist 

# Fix for MacOSX Lion 10.7.4 to reenable environment variables
sudo touch /var/db/.launchd_allow_global_dyld_envvars

# MacOSX Mountain Lion doesn't use ~/.MacOSX/environment
# Use /etc/launchd.conf instead
echo setenv SDKS "$SCRIPTDIR/sdks" > launchd.conf.tmp
echo setenv P4CONFIG p4config >> launchd.conf.tmp
sudo cp launchd.conf.tmp /private/etc/launchd.conf
rm launchd.conf.tmp

# Install python argparse for earlier versions of Mac OS X
sudo easy_install argparse

#
# Get the MacOSX version (+4), 13 = 10.9, 12 = 10.8, etc
#

darwinos_major=`sysctl -n kern.osrelease | cut -d . -f 1`

#
# Mac ports is needed to continue
#

if [ ! -f /opt/local/bin/port ]; then
	open https://www.macports.org/install.php
	exit
fi

#
# Update mac ports
#

sudo port -v selfupdate

#
# install stuff!
#

if [ ! -f /opt/local/bin/doxygen ]; then
	sudo port install doxygen
fi

if [ ! -f /opt/local/bin/dot ]; then
	sudo port install graphviz
fi

if [ ! -f /opt/local/bin/python2.7 ]; then
	sudo port install python27
fi

if [ ! -f /opt/local/bin/git ]; then
	sudo port install git
fi

if [ ! -f /opt/local/bin/gcc-mp-4.8 ]; then
	sudo port install gcc48
fi

if [ ! -f /opt/local/bin/gcc-mp-4.9 ]; then
	sudo port install gcc49
fi

#
# Upgrade anything that was missed
#

sudo port upgrade outdated


#
# Useful, but not needed code
#

#
# Install the XCode command line tools
#

#xcode-select --install

#if [ $darwinos_major -eq 13 ]; then
#	curl -o MacPorts-2.3.1-10.9-Mavericks.pkg 'https://distfiles.macports.org/MacPorts/MacPorts-2.3.1-10.9-Mavericks.pkg'
#	sudo installer -pkg MacPorts-2.3.1-10.9-Mavericks.pkg -target /
#fi
# cd /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.5.sdk/usr/include/c++/4.2.1
# sudo ln -s i686-apple-darwin9 i686-apple-darwin11
# sudo ln -s x86_64-apple-darwin9 x86_64-apple-darwin11
# sudo ln -s powerpc-apple-darwin9 powerpc-apple-darwin11
# sudo ln -s powerpc64-apple-darwin9 powerpc64-apple-darwin11
# cd /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.5.sdk/usr/lib
# sudo ln -s libstdc++.6.0.4.dylib libstdc++.dylib