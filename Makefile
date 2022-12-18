MKDIR = mkdir -p
RM = rm -rf

CXX = clang++
CXXFLAGS = -g -Wall


BUILD_FOLDER = build
OBJ_FOLDER  = $(BUILD_FOLDER)/objs

SOURCE_DIRECTORY = src

SOURCES      = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJS         = $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(OBJ_FOLDER)/%.o, $(SOURCES))

OUTPUT  = $(BUILD_FOLDER)/prog

INCLUDE = include

default: all

all: $(OUTPUT)

$(OUTPUT): $(BUILD_FOLDER) $(OBJ_FOLDER) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT) -I$(INCLUDE)

$(BUILD_FOLDER):
	$(MKDIR) $@

$(OBJ_FOLDER):
	$(MKDIR) $@

$(OBJ_FOLDER)/%.o: $(SOURCE_DIRECTORY)/%.cpp $(INCLUDE_DIRECTORY)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

$(OBJ_FOLDER)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE)

clean veryclean:
	$(REMOVE) $(BUILD_FOLDER)

.PHONY: default, all, main, clean

