# maliobro
malioBro(); is a Super Mario Bros game remake using purely C++ and SDL library.

# Dependency
install SDL Library
https://www.libsdl.org/download-2.0.php
you can follow the instructions here (for windows, DevC++)
https://github.com/sunderipranata/maliobro/files/2530865/SDL.Tutorial.pdf


# Running
Compile and run the program.
You can also compile and run the tile generator to create the world map.

# To play without installing
Just go to the project folder and run `test.exe`
You can also generate the maps using tile generator from `/TILE GENERATOR/TILE GENERATOR.exe`


    brew install sdl
    brew install sdl_mixer
    brew install sdl_ttf

then copy the include & lib folder to the project folder

compiling
    g++ main.cpp -o play -I include -L lib -l SDL-1.2.0 -l SDL_mixer-1.2.0 -l SDL_ttf-2.0.0