##############################################################
# Makefile for Unfolder

TARGET = mora
LIBS = 
FLAGS = 
INCLUDES =

##############################################################

DEBUG = -g
WARNINGS = -Wall -pedantic

CC = gcc $(DEBUG) $(INCLUDES) $(WARNINGS) $(FLAGS)
SHELL = /bin/sh

TMPFILES =

OBJECTS = main.o common.o readlib.o \
	  netconv.o nodelist.o readpep.o dot.o \
	  unfold.o marking.o pe.o order.o compress.o
	  
default: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TMPFILES) $(TARGET) core* *.output *.d .deps gmon.out

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Dependencies

%.d: %.c
	  $(SHELL) -ec '$(CC)  -MM $? | sed '\''s/$*\.o/& $@/g'\'' > $@'

DEPS = $(OBJECTS:%.o=%.d)

.deps: $(DEPS)
	echo " " $(DEPS) | \
	sed 's/[ 	][ 	]*/#include /g' | tr '#' '\012' > .deps

include .deps
