PowerPCRequired is copyright 1997-2014 by Rebecca Ann Heineman
All rights reserved.
becky@burgerbecky.com
	
Rights granted for free use, modification and 
redistribution of this code without
any compensation to the author. All I'd ask is
if you'd acknowledge my name in the credits, but
this is not a requirement.
	

In other words, this is public domain. So there.


MacOS 8.6 and previous 680x0 machines will display
a cryptic message of "Error 3" when a PowerPC
only application is run. By including
PowerPCRequired.r to your application,
on ancient 680x0 machines, the user will
see a dialog that says "The program
requires a PowerPC or Intel processor."

It's far better to see that instead of Error 3.

To use, just add the file PowerPCRequired.r to
your PowerPC Classic or Carbon app. That's it.

I've also created a .r file with all the data in it
so you can keep the file in a flattened source control
system that gets confused by Macintosh resource forks.

Notes:

I copied over the 680x0 compiler from CodeWarrior 7 
and invoke it from IDE 8.3

Please note, CodeWarrior 9 and higher will NOT work
with the CodeWarrior 7 680x0 compiler. As a result, you
must compile this app with IDE 7.0-8.3

Note: PowerPCReqired.r is the final product converted to an
includeble text file. The rest of the files are the source
and project that built the file.
