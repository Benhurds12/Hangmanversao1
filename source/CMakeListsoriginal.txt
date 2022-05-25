cmake_minimum_required(VERSION 3.5)
project (PigDiceGame)

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
#set( PREPROCESSING_FLAGS  "-D PRINT")
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#=== Main App ===
include_directories(core)
add_executable(hangman  core/main.cpp
                        core/hangman_gm.cpp
                        core/hm_word.cpp
                        core/player.cpp
                        core/dice.cpp)

#define C++17 as the standard.
# set_target_properties( hangman PROPERTIES CXX_STANDARD 17 )
target_compile_features( hangman PUBLIC cxx_std_17 )
