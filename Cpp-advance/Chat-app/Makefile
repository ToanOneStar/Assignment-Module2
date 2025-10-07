CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread -I./inc
TARGET = chat_app
SOURCES = $(wildcard src/*.cpp) \
       main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean