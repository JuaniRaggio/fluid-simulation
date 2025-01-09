# Fluid simulator -> Colisions between liquids and solids
---
Video frames are affected by the gif conversion
![Simulator preview](assets/output.gif)
![Simulator preview2](assets/simulator-preview.gif)
> [!important] Note
> This implementation doesn't depend of the operating system so it should be working independently of the OS
> You require to have SDL2 installed

## Archives
---
- build.sh: Works as a makefile, it is used to compile the proyect with the desired flags, compiler and manages
included directories
- linuxBuild.sh: Idem build but works for linux, its more reliable
- main.c: Manages the workflow of the simulation, calls functions in order to make the program work properly and
calls functions to manage errors
- src/: Directory with the source of the functions called by the main file
- include/; Directory with the header files of the functions called by the main file, window formats and
error-management files

