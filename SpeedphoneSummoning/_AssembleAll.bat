@echo off

set startDir=C:\devkitPro\devkitARM\bin\

set as="%startDir%arm-none-eabi-as"
set readelf="%startDir%arm-none-eabi-readelf"
set objcopy="%startDir%arm-none-eabi-objcopy"

for /r %~dp0\bin\ %%g in (*.bin) do del %%g
for /r %~dp0\asm\ %%g in (*.asm) do echo "%%g" >> asmlist.txt
for /f "tokens=*" %%m in (asmlist.txt) do (
	%as% -g -mcpu=arm7tdmi -mthumb-interwork -I %~dp0\asm\ %%m -o "%~dp0\bin\%%~nm.elf"
	%readelf% -s "%~dp0\bin\%%~nm.elf" > "%~dp0\bin\%%~nm.symbols.log"
	%objcopy% -S "%~dp0\bin\%%~nm.elf" -O binary "%~dp0\bin\%%~nm.bin"
	del "%~dp0\bin\%%~nm.elf"
	del "%~dp0\bin\%%~nm.symbols.log"
)

del asmlist.txt

pause