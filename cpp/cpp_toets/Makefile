
CC = c++
CFLAGS = -Wall

OBJECTS = main.o notesstream.o instrument.o guitar.o violin.o

all: cpp_toets

cpp_toets: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
	rm `find . -perm +111 -type f`

touch:
	touch ./*.cpp
	touch ./*.h

