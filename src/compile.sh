#!/bin/bash

g++ -std=c++11 *.cpp -I./SFML-2.0/include -L./SFML-2.0/lib/ -Wl,-rpath -Wl,./SFML-2.0/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
