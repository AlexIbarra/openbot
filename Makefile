CC = g++
CFLAGS = -c -ggdb -Wall -Wno-unused-variable
BASEDIR = $(shell pwd)
OBJDIR = $(BASEDIR)/obj
OBJ = $(OBJDIR)/main.o $(OBJDIR)/moduloMotor.o $(OBJDIR)/moduloCamara.o $(OBJDIR)/moduloCentral.o $(OBJDIR)/moduloNavegacion.o
BINDIR = $(BASEDIR)/bin
INCDIR = $(BASEDIR)/include
SRCDIR = $(BASEDIR)/src
LIBS=`pkg-config --libs opencv` -lwiringPi -lpthread
EXEC = openbot

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(BINDIR)/openbot $(LIBS)
	
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloMotor.o: $(SRCDIR)/moduloMotor.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloMotor.o $(SRCDIR)/moduloMotor.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloCamara.o: $(SRCDIR)/moduloCamara.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCamara.o $(SRCDIR)/moduloCamara.cpp -I$(INCDIR)	
			
$(OBJDIR)/moduloCentral.o: $(SRCDIR)/moduloCentral.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloCentral.o $(SRCDIR)/moduloCentral.cpp -I$(INCDIR)
	
$(OBJDIR)/moduloNavegacion.o: $(SRCDIR)/moduloNavegacion.cpp
	$(CC) $(CFLAGS) -o $(OBJDIR)/moduloNavegacion.o $(SRCDIR)/moduloNavegacion.cpp -I$(INCDIR)
	

.PHONY:clean
clean: 
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
