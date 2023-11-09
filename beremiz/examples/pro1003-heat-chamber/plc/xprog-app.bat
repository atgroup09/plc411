@echo off

:: Berimiz application loader
:: xprog-app.bat file.hex

:: Path to stm32flash.exe
:: set Bin="C:\Program Files (x86)\YAPLC-1.1.0\stm32flash\stm32flash.exe"
:: set Bin="D:\User1\builds\stm32flash.exe"
set Bin="stm32flash.exe"

:: COM-port
set Com="COM1"

:: COM-speed (baudrate) 57600 by default
:: set Spd=57600
set Spd=115200

:: Start execution at specified address (0 = flash start)
:: =address
set g=0x0

:: Specify start address and optionally length in bytes for read/write/erase operations
:: =address[:length]
set S=0x08040000

set Hex="build\plc.elf.hex"

:: Start

echo %date% %time%

if not exist %Bin% (
    echo %Bin% is not exists!
    exit
)

if not exist %Hex% (
    echo %Hex% is not exists!
    exit
)

:: stm32flash -w "file.hex" -v -g %g% -S %S% %Com%
echo.
echo %Bin% -w %Hex% -v -g %g% -S %S% -b %Spd% %Com%
%Bin% -w %Hex% -v -g %g% -S %S% -b %Spd% %Com%

:: Start End
