#Yelanika Gunasekara
#GNSSEN002
#Makefile

CC = g++
CCFLAGS = -std=c++2a

extractor.exe: extractor.o FrameSequence.o 
	$(CC) $(CCFLAGS) FrameSequence.o extractor.o -o extractor.exe

extractor.o: extractor.cpp FrameSequence.h
	$(CC) $(CCFLAGS) extractor.cpp -c

FrameSequence.o: FrameSequence.cpp FrameSequence.h
	$(CC) $(CCFLAGS) FrameSequence.cpp -c

clean:
	rm -f *.o
	rm  *.pgm
	rm extractor.exe