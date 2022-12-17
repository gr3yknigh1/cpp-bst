MKDIR  = mkdir -p
REMOVE = rm -rf

CXX      = clang++
CXXFLAGS = -g -Wall

MKFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR  = $(dir $(MKFILE_PATH))

PROJECT_NAME      = bst
LIBRARY_NAME      = libbst

PROJECT_DIRECTORY = $(MKFILE_DIR:-=)

INCLUDE_DIRECTORY = $(PROJECT_DIRECTORY)include
TESTS_FOLDER      = $(PROJECT_DIRECTORY)tests
SOURCE_DIRECTORY  = $(PROJECT_DIRECTORY)src
BUILD_FOLDER      = $(PROJECT_DIRECTORY)build

OBJ_FOLDER        = $(BUILD_FOLDER)/objs
SOURCES           = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJS              = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJ_FOLDER)/%.o, $(SOURCES))

CLI = $(BUILD_FOLDER)/$(PROJECT_NAME)

LIBRARY                  = $(BUILD_FOLDER)/$(LIBRARY_NAME).a
LIBRARY_SOURCE_DIRECTORY = $(SOURCE_DIRECTORY)/bst
LIBRARY_OBJ_FOLDER       = $(OBJ_FOLDER)/bst

LIBRARY_SOURCES       = $(wildcard $(LIBRARY_SOURCE_DIRECTORY)/*.cpp)
LIBRARY_OBJS          = $(patsubst $(LIBRARY_SOURCE_DIRECTORY)/%.cpp, $(LIBRARY_OBJ_FOLDER)/%.o, $(LIBRARY_SOURCES))

TESTS_BIN_FOLDER  = $(BUILD_FOLDER)/tests
TESTS_SOURCES     = $(wildcard $(TESTS_FOLDER)/*.cpp)
TESTS_BINS        = $(patsubst $(TESTS_FOLDER)/%.cpp, $(TESTS_BIN_FOLDER)/%, $(TESTS_SOURCES))

LIBRARIES = criterion $(LIBRARY)

default: all
all: $(LIBRARY) $(CLI)

release: CFLAGS=-Wall -O3 -DNDEBUG
release: clean
release: $(LIBRARY)

$(BUILD_FOLDER):
	$(MKDIR) $@

$(OBJ_FOLDER):
	$(MKDIR) $@

# -- CLI

$(CLI): $(LIBRARY) $(SOURCES)
	$(CXX) $(CXXFLAGS) -l$(LIBRARIES) -I$(INCLUDE_DIRECTORY) $(SOURCES) -o $@

# -- LIB
$(LIBRARY_OBJ_FOLDER):
	$(MKDIR) $@

$(LIBRARY): $(BUILD_FOLDER) $(LIBRARY_OBJ_FOLDER) $(LIBRARY_OBJS)
	$(RM) $(LIBRARY)
	ar -cvrs $(LIBRARY) $(LIBRARY_OBJS)

$(LIBRARY_OBJ_FOLDER)/%.o: $(LIBRARY_SOURCE_DIRECTORY)/%.cpp $(INCLUDE_DIRECTORY)/bst/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_DIRECTORY)

$(LIBRARY_OBJ_FOLDER)/%.o: $(LIBRARY_SOURCE_DIRECTORY)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_DIRECTORY)


# -- TESTS
$(TESTS_BIN_FOLDER)/%: $(TESTS_FOLDER)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -l$(LIBRARIES) -I$(INCLUDE_DIRECTORY)

tests: $(LIBRARY) $(TESTS_BIN_FOLDER) $(TESTS_BINS)
	for test in $(TESTS_BINS); do $$test ; done

$(TESTS_BIN_FOLDER):
	$(MKDIR) $@


# -- ETC
clean veryclean:
	$(REMOVE) $(BUILD_FOLDER)

.PHONY: default, all, main, clean

