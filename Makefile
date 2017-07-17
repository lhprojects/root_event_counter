FLAGS=-Wall -std=c++0x $(shell root-config --cflags)
LIBS=$(shell root-config --libs)

bin/root_event_counter: src/root_event_counter.cxx
	mkdir bin -p
	g++ $(FLAGS) $(LIBS) src/root_event_counter.cxx -o bin/root_event_counter


.PHONY: clean
clean:

