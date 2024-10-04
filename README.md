# Snek 

A simple snake game made using SDL2.

<img src="game.gif"/>

## Dependencies

- CMake >= 3.10
- GCC/G++ >= 13.1

## Local Build Dependencies

- **MinGW-w64** 
    - A suite of development tools installed through MSYS2. You can download it from [here](https://www.mingw-w64.org/downloads/#msys2).

- **SDL2, SDL2_ttf, and SDL2_image**
    - Install these libraries using the following command:
      ```bash
      pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image
      ```

## Local Build Instructions

1. Create a build directory and navigate into it:
    ```bash
    mkdir build && cd build
    ```

2. Configure the project using CMake:
    ```bash
    cmake -G "MinGW Makefiles" ..
    ```

3. Build the project:
    ```bash
    make
    ```

4. Run the game:
    ```bash
    ./snek
    ```

## Notes

- Make sure to set the build type (e.g., Release or Debug) if needed:
    ```bash
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    ```
