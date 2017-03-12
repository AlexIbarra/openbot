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
	
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp #$(INCDIR)/moduloBroker.h $(INCDIR)/moduloMotor.h $(INCDIR)/moduloCamara.h $(INCDIR)/moduloCentral.h
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloBroker.o: $(SRCDIR)/moduloBroker.cpp #$(INCDIR)/moduloBroker.h
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloBroker.o $(SRCDIR)/moduloBroker.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloMotor.o: $(SRCDIR)/moduloMotor.cpp #$(INCDIR)/moduloMotor.h
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloMotor.o $(SRCDIR)/moduloMotor.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloCamara.o: $(SRCDIR)/moduloCamara2.cpp #$(INCDIR)/moduloCamara.h
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCamara.o $(SRCDIR)/moduloCamara2.cpp -I$(INCDIR)
		
$(OBJDIR)/moduloCentral.o: $(SRCDIR)/moduloCentral.cpp #$(INCDIR)/moduloCentral.h
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCentral.o $(SRCDIR)/moduloCentral.cpp -I$(INCDIR)

.PHONY:clean
clean: 
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
