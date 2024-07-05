# Snek 

A simple snake game made in simple SDL2.

<img src="game.gif"/>

## Dependencies

- make >= 3.8

- gcc/g++ >= 13.1

## Local Release Instructions

1. Run : `mkdir release && cd release`
2. Ensure `libfreetype-6.dll` `SDL2_ttf.dll`,`SDL2.dll` are present in this directory.
3. Compile & run: `cd .. && make release && make rrun`.

## Local Build Dependencies

- MinGW-w64 

    - Installed through MSYS2 from [here](https://www.mingw-w64.org/downloads/#msys2).

- SDL2 >= 2.0

  - Latest version can be found [here](https://github.com/libsdl-org/SDL/releases/latest).

- SDL2_ttf >= 2.0

  - Latest version can be found [here](https://github.com/libsdl-org/SDL_ttf/releases/latest).

- (Optional) Freetype
  
  - Installing through msys2 using command found [here](https://packages.msys2.org/package/mingw-w64-x86_64-freetype?repo=mingw64).

## Local Build Instructions

1. Copy installed SDL2 & SDL2_ttf include directories into `src/include`.
2. Copy SDL2 & SDL2_ttf lib directories in `src/lib`.
3. Copy SDL2 & SDL2_ttf dll into main directory.
4. Either install freetype or place `libfreetype-6.dll` in this directory.
5. Compile & run: `make && make run`.