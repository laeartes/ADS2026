@echo off

if .%USERDOMAIN% == .SavasPC goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
test.exe > test.txt
echo Testo rezultatai įrašyti į test.txt
