CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20
SRC = $(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)

TARGET = src/main

all: $(TARGET)



$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)



src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f src/*.o $(TARGET)