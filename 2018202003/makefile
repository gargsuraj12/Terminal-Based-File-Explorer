#Name: Suraj Garg
#Roll No: 2018202003

CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = cpUtility.h lsUtility.h renameUtility.h termiControl.h constants.h tbfeDriver.h createUtility.h deleteUtility.h searchUtility.h
OBJ = termiControl.o cpUtility.o lsUtility.o renameUtility.o tbfeDriver.o createUtility.o deleteUtility.o searchUtility.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tbfeDriver: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

