cmake_minimum_required(VERSION 3.28)
project(Assignment_4_Programming_Paradigms)

set(CMAKE_CXX_STANDARD 26)

add_executable(Assignment_4_Programming_Paradigms Assignment_4/main.cpp
        Assignment_4/TextEditor/DynamicArray.cpp
        Assignment_4/TextEditor/DynamicArray.h
        Assignment_4/CaesarCipher/CaesarCipher.cpp
        Assignment_4/CaesarCipher/CaesarCipher.h
        Assignment_4/CaesarCipher/mylib.cpp
        Assignment_4/Text/Text.cpp
        Assignment_4/Text/Text.h)
