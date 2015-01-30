' Given a URL and an output filename, download a file and store it

' Copyright 1995-2014 by Rebecca Ann Heineman becky@burgerbecky.com

' It is released under an MIT Open Source license. Please see LICENSE
' for license details. Yes, you can use it in a
' commercial title without paying anything, just give me a credit.
' Please? It's not like I'm asking you for money!


' Check if there are only 2 arguments

If Wscript.Arguments.Count <> 2 Then
	If Wscript.Arguments.Count = 0 Then
		
		' Likely this was triggered by a user double clicking.
		
		Wscript.Echo "No arguments found. This file wasn't meant to be double clicked."
	Else
	
		' Print an alternate error message
		
		Wscript.Echo "Expected 2 arguments, a URL and an output file, instead ",Wscript.Arguments.Count," argument(s) were passed."
	End if
	Wscript.Quit(10)
End if

' Grab the URL

TheFileURL = WScript.Arguments.Item(0)

' Grab the output filename

Output = WScript.Arguments.Item(1)

' Attempt to open the HTTP file with a GET command

On Error Resume Next
Set objXMLHTTP = CreateObject("WinHttp.WinHttpRequest.5.1")
objXMLHTTP.open "GET", TheFileURL, false

If Err.Number <> 0 Then
	Wscript.Echo "Error """ & Err.Description & """ in calling WinHttpRequest.5.1 with " & TheFileURL
	Wscript.Quit(10)
End If

' Send the command the remote server

objXMLHTTP.send()

If Err.Number <> 0 Then
	Wscript.Echo "Error """ & Err.Description & """ in calling send to WinHttpRequest.5.1"
	Wscript.Quit(10)
End If

' Disable error trapping

On Error GoTo 0

' Was the file found?

If objXMLHTTP.Status = 404 Then
	Wscript.Echo TheFileURL," was not found on the remote server."
	Wscript.Quit(10)

' Any other error?

ElseIf objXMLHTTP.Status <> 200 Then
	Wscript.Echo "Got status ",objXMLHTTP.Status," instead of 200 (OK) when opening ",TheFileURL
	Wscript.Quit(10)

Else

	' Great! Download it!

	' Set some Microsoft constants	
	Const adTypeBinary = 1
	Const adSaveCreateOverWrite = 2

	' Open a binary connection
	Set objADOStream = CreateObject("ADODB.Stream")
	objADOStream.Type = adTypeBinary
	objADOStream.Open
	objADOStream.Position = 0
	objADOStream.Write objXMLHTTP.ResponseBody
	
	' Save off the file
	
	On Error Resume Next
	objADOStream.SaveToFile Output,adSaveCreateOverWrite
	If Err.Number <> 0 Then
		Wscript.Echo "Error """ & Err.Description & """ in saving the file " & Output
		Wscript.Quit(10)
	End If

	objADOStream.Close
End if

' Success!

Wscript.Quit(0)
