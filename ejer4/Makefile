CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = pipe_game
SOURCE = pipe_game.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
