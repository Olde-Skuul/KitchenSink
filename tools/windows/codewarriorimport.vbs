' Given a URL and an output filename, download a file and store it

' Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

' It is released under an MIT Open Source license. Please see LICENSE
' for license details. Yes, you can use it in a
' commercial title without paying anything, just give me a credit.
' Please? It's not like I'm asking you for money!


' Locate CodeWarrior

Set WSHShell=Wscript.CreateObject("Wscript.Shell")
CodeWarriorPath = WSHShell.ExpandEnvironmentStrings( "%CWFolder%" )
If CodeWarriorPath = "%CWFolder%" Then
	WScript.Echo "CWFolder was not set"
	WScript.Quit(10)
End If

' Find the exe file

CodeWarriorPath = CodeWarriorPath & "\Bin\ide.exe"

' Launch Codewarrior for Windows

WSHShell.Run """" & CodeWarriorPath & """",9,false
WScript.Sleep 500
WSHShell.SendKeys "%ef"		' Open the prefs using Alt-E and Alt-F
WScript.Sleep 500

' TODO: Select "Source Trees" and then manually Import cwsdksvar.xml

'WSHShell.SendKeys "%{F4}"	' Close it with Alt-F4

' Success!

Wscript.Quit(0)
