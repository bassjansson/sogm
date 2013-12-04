
CC = c++
CFLAGS = -Wall

all: ftmain

ftmain: ftmain.o signalgenerator.h fouriertransform.h
	$(CC) -o $@ ftmain.o

clean:
	rm *.o wavelog.* ftmain

.cpp.o:
	$(CC) -c $< $(CFLAGS)

