@echo off

set /p cppFile= Enter the file you want to moc: 
set /p mocFile= Enter the name of the new file: 

C:\Qt\5.4\msvc2012_opengl\bin\moc.exe %cppFile% -o%mocFile%

pause