CC = g++
OBJECTS = test.o DCT2.o
EXEC = test

$(EXEC): $(OBJECTS)
	g++ -o $@ $^ -O3 `pkg-config --libs --cflags gtkmm-3.0`

%.o : %.cpp
	g++ -c -o $@ $< -O3 `pkg-config --libs --cflags gtkmm-3.0`

clean:
	rm $(OBJECTS) $(EXEC)

DCT2.o: DCT2.h
test.o: DCT2.h
