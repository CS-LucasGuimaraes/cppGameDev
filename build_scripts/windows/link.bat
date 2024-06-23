cd ../../build

g++ ^
  -fdiagnostics-color=always ^
  -Wall ^
  -g3 ^
  -o ^
  ..\bin\app.exe ^
  *.o ^
  -lmingw32 ^
  -lSDL2main ^
  -lSDL2 ^
  -lSDL2_image ^
  -lyaml-cpp
  @REM -flto=auto^
  @REM -O2 ^

@echo Linking process finished!