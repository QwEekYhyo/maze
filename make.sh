#!/bin/bash

g++ -o $1 -std=C++20 -lsfml-graphics -lsfml-window -lsfml-system ${@:2}
