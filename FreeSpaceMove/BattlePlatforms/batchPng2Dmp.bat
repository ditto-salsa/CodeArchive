@echo off

@cd %~dp0\png

@dir *.png /b > png.txt

for /f "tokens=*" %%m in (png.txt) do echo %%m

for /f "tokens=*" %%m in (png.txt) do ..\..\..\EventAssembler\Tools\Png2Dmp.exe %%m --lz77 -o ..\dmp\%%~nm".lz77" -po ..\dmp\%%~nm".pal"

@del png.txt

echo Done!

pause