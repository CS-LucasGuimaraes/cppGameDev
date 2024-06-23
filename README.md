# CppGameDev

## Project Dependencies

This project requires the following libraries to be built and run successfully:

- **SDL2** (v2.30.2-1)- Simple DirectMedia Layer 2, a multimedia development
  library.
- **SDL2_image** (v2.8.2-3)- Image loading extension for SDL2.
- **nlohmann-json** (v3.11.3-1)- A single-header JSON library for modern C++.
- **yaml-cpp** (v0.8.0-1)- A YAML parser and emitter in C++ matching the YAML 1.2 spec.

### Installation

**Please choose the installation instructions based on your package manager:**

**Using mingw-w64:**

```bash
pacman -S mingw-w64-x86_64-sdl2  mingw-w64-x86_64-sdl2_image  mingw-w64-x86_64-nlohmann-json  mingw-w64-x86_64-yaml-cpp
```

Replace 'x86_64' with your desired architecture (e.g., i686) if needed

**Using apt-get:**

```bash
sudo apt-get install -y libsdl2-dev  libsdl2-image-dev  nlohmann-json3-dev  libyaml-cpp-dev
```

Note: These commands provide basic installation instructions. You might need to
adjust them based on your specific distribution.

### Further Information

You can find more information about each of the dependecies on:

- **SDL2:** https://www.libsdl.org/
- **SDL2_image:** https://github.com/libsdl-org/SDL_image
- **nlohmann-json:** https://github.com/nlohmann/json

## Building the Project

This section outlines the steps to build your project successfully. Make sure
you have the required dependencies installed as described in the
[Project Dependencies](#project-dependencies) section.

**Compiler Flags:**

The provided commands use the following compiler flags for better development
experience:

- `-fdiagnostics-color=always`: Enables colored error messages for easier
  reading.
- `-Wall`: Enables most warnings from the compiler to help identify potential
  issues.
- `-g3`: Enables generation of debug information for easier debugging.

**Building with Different Compilers:**

The following instructions provide guidance for compiling your project using
either mingw-w64 or Linux g++.

### **Using mingw-w64:**

Alternatively, you can build the project by running the batch scripts in
`build_scripts/windows`.

**Single File Object Compilation:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -c -O2 -flto ${file} -o build/${filename}.o -Iinclude -Isrc
```

Make sure to replace `${file}` to the path to the file that you want to compile
and `{filename}` with the name of the file.

\
**All Files Compilation:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -c -O2 -flto ..\src\main.cpp ..\src\core\*.cpp ..\src\main\*.cpp  ..\src\classes\*.cpp -I..\include
```

Make sure to run this command inside the build folder.

\
**Linking:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -o -flto=auto -O2 ..\bin\app.exe *.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
```

Make sure to run this command inside the build folder.

### **Using Linux g++:**

Alternatively, you can build the project by running the batch scripts in
`build_scripts/linux`.

**Single File Object Compilation:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -c -O2 -flto ${file} -o build/${filename}.o -Iinclude -Isrc
```

Make sure to replace `${file}` to the path to the file that you want to compile
and `{filename}` with the name of the file.

\
**All Files Compilation:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -c -O2 -flto ..\src\main.cpp ..\src\core\*.cpp ..\src\main\*.cpp  ..\src\classes\*.cpp -I..\include
```

Make sure to run this command inside the build folder.

\
**Linking:**

```bash
g++ -fdiagnostics-color=always -Wall -g3 -o -flto=auto -O2 ..\bin\app.out *.o -lSDL2 -lSDL2_image
```

Make sure to run this command inside the build folder.

## Running the Project

Once you've successfully built the project following the instructions in the
[Building the Project](#building-the-project) section, you can run it by
following these steps:

**1. Navigate to the executable:**

Locate the bin directory, where your project's executable is placed.

```bash
cd bin
```

**2. Run the program:**

**Windows:**

```bash
app.exe
```

**Linux:**

```bash
./app.out
```
