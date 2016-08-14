CXX = clang++
CFLAGS = -std=c++11 -Wall -g -O0
LDFLAGS = -lSDL2 -lSDL2_image -lGL -lGLU -lGLEW
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = snake
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o $(EXECUTABLE) $(LDFLAGS)

.PHONY: run
run: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: rebuild
rebuild: clean all

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECUTABLE)
