OBJS = 02_getting_an_image_on_the_screen.cpp

CC = g++

COMPILER-FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = 02_image

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
