# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

# Compiler settings
CC = clang++
CFLAGS = -std=c++17

# Source and main sub directories in fireworks-core
CORE_SRC  =  fireworks-core/src
GRAPHICS  =  $(CORE_SRC)/graphics
BUFFERS   =  $(GRAPHICS)/buffers
INPUT     =  $(CORE_SRC)/input
MATHS     =  $(CORE_SRC)/maths
SHADERS   =  $(CORE_SRC)/shaders
UTILS     =  $(CORE_SRC)/utils

VPATH = $(CORE_SRC) $(GRAPHICS) $(BUFFERS) $(INPUT) $(MATHS) $(SHADERS) $(UTILS)
