@echo off

echo Start compile
set files=main.c game.c utils.c
set flags=-Wall -Werror -Wextra
gcc %flags% -lkernel32 %files% -o snake
echo Programm created

echo Start program
rem echo on
rem cls
rem snake.exe
