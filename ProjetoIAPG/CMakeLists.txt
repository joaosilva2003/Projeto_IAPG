cmake_minimum_required(VERSION 3.26)
project(ProjetoIAPG C)

set(CMAKE_C_STANDARD 17)

add_executable(ProjetoIAPG main.c
        cmake-build-debug/Estruturas.h
        funcoes.c
        funcoes.h
)
