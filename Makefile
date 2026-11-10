CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -g
SRC = src/main.cpp src/Item.cpp src/Tracker.cpp
TARGET = bin/tracker

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf bin/ tracker_data.csv tracker_data.csv.tmp