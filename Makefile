CC=g++

SRC_DIR=src
BUILD_DIR=build

SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

CFLAGS=-c -Wall -std=c++11

EXECUTABLE=hms

all: $(SRC) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean


