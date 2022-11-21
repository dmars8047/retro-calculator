OBJS = Main.cpp texture.cpp assetmanager.cpp viewport.cpp

CC = g++

MCC = clang++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

APP_NAME = retro-calculator.app

linux : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(APP_NAME)

MAC_INCLUDE_PATHS = -I/opt/homebrew/include/SDL2/
MAC_LIBRARY_PATHS = -L/opt/homebrew/lib

mac : $(OBJS)
	$(MCC) -std=c++17 $(OBJS) $(MAC_INCLUDE_PATHS) $(MAC_LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(APP_NAME)