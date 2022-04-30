cmake_minimum_required(VERSION 3.22)
project(Exercise_5)

set(CMAKE_CXX_STANDARD 23)

add_executable(Exercise_5 main.cpp type.h item.cpp item.h exception.h character.cpp character.h hero.cpp hero.h npc.cpp npc.h fighter.cpp fighter.h sorcerer.cpp sorcerer.h game.cpp game.h)
