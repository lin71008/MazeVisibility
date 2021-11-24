.DEFAULT_GOAL := all
.PHONY: all clean

CC = gcc
CXX = g++
RM = rm -f

CFLAGS = -std=c11
CXXFLAGS = -std=c++11
CPPFLAGS = -m32 -DPROJECT_DIR=\"$(PROJECT_ROOT_DIR)\" -DWIN32

LDFLAGS = -lm -static-libgcc -static-libstdc++

# debug setting

# CPPFLAGS += -g -Wall -Wextra -Wno-unused
CPPFLAGS += -DNDEBUG


# project setting I (path & library)

PROJECT_ROOT_DIR = .
SRC_DIR = $(PROJECT_ROOT_DIR)/src/
LIB_DIR = $(PROJECT_ROOT_DIR)/lib/
BUILD_DIR = $(PROJECT_ROOT_DIR)/build/

FLTK_OPTION = --use-gl --use-images --use-glut --use-forms

CFLAGS += $(shell fltk-config $(FLTK_OPTION) --cflags)
CXXFLAGS += $(shell fltk-config $(FLTK_OPTION) --cxxflags)
LDFLAGS += $(shell fltk-config $(FLTK_OPTION) --ldflags)


# project setting II (target relation & export format)

TARGETS = Matrix.so Maze.so MazeVisibility

Matrix.so: $(SRC_DIR)Matrix.o

Maze.so: $(SRC_DIR)Maze.o \
		 $(SRC_DIR)Cell.o \
		 $(SRC_DIR)Edge.o \
		 $(SRC_DIR)LineSeg.o \
		 $(SRC_DIR)Vertex.o
Maze.so: LDFLAGS += Matrix.so

MazeVisibility: $(SRC_DIR)Maze.o \
				$(SRC_DIR)MapWidget.o \
				$(SRC_DIR)MazeWindow.o \
				$(SRC_DIR)RunMaze.o
MazeVisibility: LDFLAGS += Maze.so Matrix.so


# loader configuration

ifeq ($(OS),Windows_NT)
	LDFLAGS += -Wl,--subsystem,windows -mwindows
endif

ifneq ($(SRC_DIR),$(LIB_DIR))
	LDFLAGS += -L"$(LIB_DIR)"
endif

ifneq ($(LDFLAGS),"")
	LDFLAGS += -lstdc++
endif


all: $(TARGETS)
	@


clean:
	$(RM) $(DEPENDS) $(patsubst %,$(BUILD_DIR)%,$(notdir $(OBJECTS)))


help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@for target in $(TARGETS); do \
	 echo "... $$target" ; \
	done
	@for object in $(OBJECTS); do \
	 echo "... $$object" ; \
	done

.PHONY: help


# project independent option

SRCS = $(wildcard $(SRC_DIR)*.c*)

SRC_C = $(filter %.c,$(SRCS))
SRC_CXX = $(filter %.cpp,$(SRCS))
DEPENDS = $(SRC_C:.c=.d) $(SRC_CXX:.cpp=.d)

OBJ_C = $(SRC_C:.c=.o)
OBJ_CXX = $(SRC_CXX:.cpp=.o)

OBJECTS = $(OBJ_C) $(OBJ_CXX)

TARGET_A = $(filter %.a,$(TARGETS))
TARGET_SO = $(filter %.so,$(TARGETS))
TARGET_DLL = $(filter %.dll,$(TARGETS))
TARGET_EXC = $(filter-out $(TARGET_A)$(TARGET_SO)$(TARGET_DLL),$(TARGETS))

# include source depends

$(SRC_C:.c=.d):%d:%c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MM $< >$@

$(SRC_CXX:.cpp=.d):%d:%cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM $< >$@

-include $(DEPENDS)

# compile object

$(OBJ_C):%o:%c
	@echo "Building C object $@"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $(BUILD_DIR)$(notdir $@) $<

$(OBJ_CXX):%o:%cpp
	@echo "Building CXX object $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(BUILD_DIR)$(notdir $@) $<

# linking object

# $(TARGET_A): LDFLAGS += -rcs

$(TARGET_SO): CPPFLAGS += -fPIC
$(TARGET_SO): LDFLAGS += -shared

$(TARGET_A):
	@echo "Building static library $@"
	@$(AR) -rcs lib$@ $(patsubst %,$(BUILD_DIR)%,$(notdir $^))

$(TARGET_SO):
	@echo "Building shared library $@"
	@$(CC) -o $@ $(patsubst %,$(BUILD_DIR)%,$(notdir $^)) $(LDFLAGS)

$(TARGET_EXC):
	@echo "Building executable $@"
	@$(CC) -o $@ $(patsubst %,$(BUILD_DIR)%,$(notdir $^)) $(LDFLAGS)
