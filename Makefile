CC = g++
OBJECTS = test.o DCT2.o
EXEC = test

$(EXEC): $(OBJECTS)
	g++ -o $@ $^ -O3 -march=native

%.o : %.cpp
	g++ -c -o $@ $< -O3 -march=native

clean:
	rm $(OBJECTS) $(EXEC)

DCT2.o: DCT2.h
test.o: DCT2.h
