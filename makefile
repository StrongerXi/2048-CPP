# This is intended to be a template for makefile (default to C project)
# Header to .c file dependency still needs to be fixed.
# Auto dependency generation is needed.

CC = g++
CFLAGS = -g -Wall -std=c++11 -I./$(HDRDIR) 

SRCDIR = .
TESTDIR = .
OBJDIR= .
HDRDIR  = .
PROJDIR = .

PROGRAM := $(PROJDIR)/2048run
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)

all : $(PROGRAM)

$(PROGRAM) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

-include .dependencies

$(OBJS) : $(OBJDIR)/%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -MM $< >> .dependencies


# List file.o : header1.h header2.h ... below

.PHONY : clean

clean :
	rm $(OBJS) $(PROGRAM)

