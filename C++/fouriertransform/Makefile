
CC = c++
CFLAGS = -Wall

all: ftmain

ftmain: ftmain.o signalgenerator.h fouriertransform.h
	$(CC) -o $@ ftmain.o

ftmain.o: signalgenerator.h fouriertransform.h

clean:
	rm *.o wavelog.* ftmain

.cpp.o:
	$(CC) -c $< $(CFLAGS)

