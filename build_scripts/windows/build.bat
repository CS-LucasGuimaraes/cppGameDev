@REM To re-build a single file use:
@REM g++ -fdiagnostics-color=always -Wall -g3 -c -O2 -flto ${file} -o build/${filename}.o -Iinclude -Isrc

cd ..\..\build

g++ ^
  -fdiagnostics-color=always ^
  -Wall ^
  -g3 ^
  -c ^
  -O2 ^
  -flto ^
  ..\src\main.cpp ^
  ..\src\core\*.cpp ^
  ..\src\main\*.cpp  ^
  ..\src\classes\*.cpp ^
  -I..\include

@echo Build process finished!
