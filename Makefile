CC = g++
CFLAGS = -c -g -Wall -Wno-unused-variable
BASEDIR = $(shell pwd)
OBJDIR = $(BASEDIR)/obj
BINDIR = $(BASEDIR)/bin
INCDIR = $(BASEDIR)/include
SRCDIR = $(BASEDIR)/src
TESTSDIR = $(BASEDIR)/tests
LIBS=`pkg-config --libs opencv` -lwiringPi -lmosquitto -lmosquittopp -lpthread
EXEC = openbot

all: $(EXEC)

$(EXEC): $(OBJDIR)/main.o $(OBJDIR)/moduloMotor.o $(OBJDIR)/moduloCamara.o $(OBJDIR)/moduloCentral.o $(OBJDIR)/moduloBroker.o $(OBJDIR)/Object.o
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/moduloMotor.o $(OBJDIR)/moduloCamara.o $(OBJDIR)/Object.o $(OBJDIR)/moduloCentral.o $(OBJDIR)/moduloBroker.o -o $(BINDIR)/openbot $(LIBS)
	
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloBroker.o: $(SRCDIR)/moduloBroker.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloBroker.o $(SRCDIR)/moduloBroker.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloMotor.o: $(SRCDIR)/moduloMotor.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloMotor.o $(SRCDIR)/moduloMotor.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloCamara.o: $(SRCDIR)/moduloCamara.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCamara.o $(SRCDIR)/moduloCamara.cpp -I$(INCDIR)
	
$(OBJDIR)/Object.o: $(SRCDIR)/Object.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/Object.o $(SRCDIR)/Object.cpp -I$(INCDIR)
		
$(OBJDIR)/moduloCentral.o: $(SRCDIR)/moduloCentral.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCentral.o $(SRCDIR)/moduloCentral.cpp -I$(INCDIR)
	
test:
	
testMosqReader: $(OBJDIR)/testMosqReader.o $(OBJDIR)/moduloBroker.o
	$(CC) $(OBJDIR)/testMosqReader.o $(OBJDIR)/moduloBroker.o -o $(TESTSDIR)/bin/testMosqReader $(LIBS)

$(OBJDIR)/testMosqReader.o: $(TESTSDIR)/testMosqReader.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/testMosqReader.o $(TESTSDIR)/testMosqReader.cpp -I$(INCDIR)
	
$(OBJDIR)/testMosqPublisher.o: $(TESTSDIR)/testMosqPublisher.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/testMosqPublisher.o $(TESTSDIR)/testMosqPublisher.cpp -I$(INCDIR)

.PHONY:clean
clean: 
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
