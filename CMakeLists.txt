cmake_minimum_required(VERSION 3.27)
project(jogo_da_cobrinha_ed C)

set(CMAKE_C_STANDARD 11)

# Crie o executável
add_executable(jogo_da_cobrinha_ed main.c)

# Vincule a biblioteca ncurses ao executável e libtinfo para resolver o erro
target_link_libraries(jogo_da_cobrinha_ed ncurses tinfo)
