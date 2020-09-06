# Usage:
# make        # compile all binary
# make run    # run the binary executable
# make clean  # remove all objects

# Compiler settings
CC     =  clang++
CFLAGS =  -std=c++17

# Frameworks and other flags and paths
FRAMEWORKS = -framework OpenGL

# Includes and paths
INLCUDE_DIRS =

# Libraries and paths
LIB_DIRS  =
LIBS      =  -lglew -lglfw

# Source and main sub directories in fireworks-core
CORE      =  fireworks-core
CORE_SRC  =  $(CORE)/src
GRAPHICS  =  $(CORE_SRC)/graphics
BUFFERS   =  $(GRAPHICS)/buffers
INPUT     =  $(CORE_SRC)/input
MATHS     =  $(CORE_SRC)/maths
SHADERS   =  $(CORE_SRC)/shaders
UTILS     =  $(CORE_SRC)/utils

# Output directories
BIN        =  bin
BIN_CORE   =  $(BIN)/core

# Directory search paths (searches automatically)
VPATH = $(SOURCE_DIRS) $(BIN_DIRS)

cppsrc = $(wildcard $(CORE)/*.cpp) \
		$(wildcard $(GRAPHICS)/*.cpp) \
		$(wildcard $(BUFFERS)/*.cpp) \
		$(wildcard $(MATHS)/*.cpp)

obj = $(cppsrc:.cpp=.o)

.PHONY: clean run

main_game: $(cppsrc)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(LIBS) $^ -o $@;
	mv $@ $(BIN_CORE)

run:
	$(BIN_CORE)/main_game

clean :
	rm -f *.o
