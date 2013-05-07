TARGETS = positive.out negative.out
SOURCES = Graph.cpp HillClimber.cpp LineGraph.cpp TopSort.cpp TwoWayClimber.cpp Negativer.cpp Positiver.cpp
HEADERS = $(SOURCES:.cpp=.hpp)
OBJECTS = $(SOURCES:.cpp=.o)
FLAGS =

all: positive negative

positive: positive.out

negative: negative.out

%.o: %.cpp
	g++ $(FLAGS) -c $<

positive.out: $(OBJECTS) main_pos.o $(HEADERS)
	g++ $(FLAGS) $(OBJECTS) main_pos.o -o positive.out

negative.out: $(OBJECTS) main_neg.o $(HEADERS)
	g++ $(FLAGS) $(OBJECTS) main_neg.o -o negative.out
clean:
	rm -f $(OBJECTS) $(TARGETS) *~

debug: FLAGS += -g
debug: positive negative


.PHONY: all clean debug
