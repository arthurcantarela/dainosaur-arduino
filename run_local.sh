#!/bin/bash
cd Tfc
g++ -DFEATURE_ARDUINO=0 -o ../local_run/local_program.o ../local_run/Main.cpp Game.cpp GameObject.cpp Dino.cpp Bird.cpp Cactus.cpp QLearning.cpp
../local_run/local_program.o