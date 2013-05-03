TARGET = a.out
SOURCES = Graph.cpp HillClimber.cpp LineGraph.cpp TopSort.cpp TwoWayClimber.cpp
HEADERS = $(SOURCES:.cpp=.hpp)
OBJECTS = $(SOURCES:.cpp=.o)
FLAGS =

debug: FLAGS += -g
debug: $(TARGET)

all: $(TARGET)

%.o: %.cpp
	g++ $(FLAGS) -c $<

$(TARGET): $(OBJECTS) main.o $(HEADERS)
	g++ $(FLAGS) $(OBJECTS) main.o
clean:
	rm -f $(OBJECTS) $(TARGET) *~

.PHONY: all clean debug
