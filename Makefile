FLAGS=-Wall -std=c++11 $(shell root-config --cflags)
LIBS=$(shell root-config --libs)

bin/root_event_counter: src/root_event_counter.cxx
	mkdir bin -p
#echo FLAGS: $(FLAGS)
#echo  LIBS:$(LIBS)
#g++ $(FLAGS) $(LIBS) -Wl,-rpath=$(shell root-config --prefix)/lib src/root_event_counter.cxx -o bin/root_event_counter
	g++ $(FLAGS)  src/root_event_counter.cxx -o bin/root_event_counter $(LIBS)


.PHONY: clean
clean:

