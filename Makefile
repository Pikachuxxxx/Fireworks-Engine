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
INLCUDE_DIRS =  -I Dependencies/SOIL/include/ \


# Libraries and paths
LIB_DIRS  = -L Dependencies/SOIL/lib/ \

LIBS      = -lglew -lglfw -lsoil -lfreetype -lfreetype-gl

# Source and main sub directories in fireworks-core
CORE      =  Fireworks-core
CORE_SRC  =  $(CORE)/src
GRAPHICS  =  $(CORE_SRC)/graphics
BUFFERS   =  $(GRAPHICS)/buffers
LAYERS    =  $(GRAPHICS)/layers
INPUT     =  $(CORE_SRC)/input
MATHS     =  $(CORE_SRC)/maths
SHADERS   =  $(CORE_SRC)/shaders
UTILS     =  $(CORE_SRC)/utils

# Output directories
BIN        =  bin
BIN_CORE   =  $(BIN)/core

# Directory search paths (searches automatically)
VPATH = $(SOURCE_DIRS) $(BIN_DIRS)

cppsrc = $(wildcard $(GRAPHICS)/*.cpp) \
		 $(wildcard $(BUFFERS)/*.cpp) \
		 $(wildcard $(LAYERS)/*.cpp) \
		 $(wildcard $(MATHS)/*.cpp)

headersrc = $(wildcard $(GRAPHICS)/*.h) \
			$(wildcard $(BUFFERS)/*.h) \
			$(wildcard $(LAYERS)/*.h) \
			$(wildcard $(MATHS)/*.h)

obj = $(cppsrc:.cpp=.o)
finalobjects = $(wildcard *.o)
.PHONY: clean run

# OG Command
main_game: $(cppsrc)
	clear
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(INLCUDE_DIRS) $(LIB_DIRS) $(LIBS) $(CORE)/main.cpp $^ -o $@;
	mv $@ $(BIN_CORE)

run:
	clear
	$(BIN_CORE)/main_game

# TODO: will have to generate a static and dynamic library later
# the main executable binary

# main_executable: main.o $(obj)
# 	$(CC) $(CFLAGS) $(FRAMEWORKS) $(LIBS) -o $@ main.o $(finalobjects)
#
# main.o : $(CORE)/main.cpp $(cppsrc) $(headersrc)
# 	@ echo "The main file is : "$<
# 	$(CC) $(CFLAGS) -c $<
#
# $(obj) : $(cppsrc) $(headersrc)
#
# %.o: %.cpp
# 	$(CC) $(FLAGS) -c $<


clean :
	rm -f -R *.o
	rm -f -R *.h.gch
