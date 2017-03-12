CC = g++
CFLAGS = -c -g -Wall
BASEDIR = $(shell pwd)
OBJDIR = $(BASEDIR)/obj
BINDIR = $(BASEDIR)/bin
INCDIR = $(BASEDIR)/include
SRCDIR = $(BASEDIR)/src
LIBS=`pkg-config --libs opencv` -lwiringPi -lmosquitto -lmosquittopp
EXEC = openbot

all: $(EXEC)

$(EXEC): $(OBJDIR)/main.o $(OBJDIR)/moduloMotor.o $(OBJDIR)/moduloCamara.o $(OBJDIR)/moduloCentral.o $(OBJDIR)/moduloBroker.o
	$(CC) $(OBJDIR)/main.o $(OBJDIR)/moduloMotor.o $(OBJDIR)/moduloCamara.o $(OBJDIR)/moduloCentral.o $(OBJDIR)/moduloBroker.o -o $(BINDIR)/openbot $(LIBS)
	
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloBroker.o: $(SRCDIR)/moduloBroker.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloBroker.o $(SRCDIR)/moduloBroker.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloMotor.o: $(SRCDIR)/moduloMotor.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloMotor.o $(SRCDIR)/moduloMotor.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloCamara.o: $(SRCDIR)/moduloCamara.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCamara.o $(SRCDIR)/moduloCamara.cpp -I$(INCDIR)
		
$(OBJDIR)/moduloCentral.o: $(SRCDIR)/moduloCentral.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCentral.o $(SRCDIR)/moduloCentral.cpp -I$(INCDIR)

.PHONY:clean
clean: 
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
