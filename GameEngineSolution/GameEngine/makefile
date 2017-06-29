CC = g++
RMDIR = rm -rf
RM = rm -f
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d
DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
HEADER_PATH = /usr/include/SDL2
BIN_PATH = bin
DEP_PATH = dep
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)
EXEC = JOGO

ifeq ($(OS), Windows_NT)
RMDIR = rd /s /q
RM = del
SDL_PATH = C:/SDL-2.0.5
DIRECTIVES += -I $(SDL_PATH)/include
LIBS = -L $(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
LIBS = -lm -framework SDL2 -framwork lSDL2_image -framework lSDL2_mixer -framework SDL2_ttf
endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: %.cpp
	$(CC) $(DEP_FLAGS) -c -o  $@ $< $(DIRECTIVES)
	
print-% : ; echo $* = $($*)

debug: DIRECTIVES += -ggbd -O0
debug: all

release: DIRECTIVES += -0fast -mtune=native
release: all

clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)
	$(RM) $(EXEC)

.PRECIOUS: $(DEP_PATH)/%.d

.PHONY: debug clean release