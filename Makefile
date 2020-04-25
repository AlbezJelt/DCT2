CC = g++
OBJECTS = test.o DCT2.o
EXEC = test

$(EXEC): $(OBJECTS)
	g++ -o $@ $^ -ltbb

%.o : %.cpp
	g++ -c -o $@ $<

clean:
	rm $(OBJECTS) $(EXEC)

DCT2.o: DCT2.h
test.o: DCT2.h
