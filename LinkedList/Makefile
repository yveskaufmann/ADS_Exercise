#
# Algorithm and data structures
# Exercise: 01_List 
#
# Author: Yves Kaufmann
# 

CC= gcc
CFLAGS= -g -Wall -std=c99 -Winline -x c 
LDFLAGS= -lm
TARGET= list
STATIC_LIB= lib$(TARGET).a
DEBUG_OPTIONS= -Oo -fno-inline
OBJECTS=node.o \
		student.o \
		readerHelper.o \
		list.o 

DOC= doxygen
DOCCONFIG= doxygen.config
MEMCHECKPRGRAM= valgrind 
MEMCHECKPARAMETERS= --tool=memcheck -v 
TESTARGUMENTS=

all:	clean $(TARGET) $(STATIC_LIB)

.PHONY:	clean all
clean:
	rm -f $(TARGET) $(OBJECTS) $(STATIC_LIB)  main.o
	rm -rf doc 
		
$(TARGET) : $(OBJECTS) main.o
	$(CC) -o $(TARGET) $(OBJECTS) main.o
	
$(STATIC_LIB):	$(OBJECTS)
	ar rcs $@ $^
	
run: $(TARGET)
	./$(TARGET) $(TESTARGUMENTS)	
	
doc: *.c
	$(DOC) $(DOCCONFIG) 

mem-check:
	$(MEMCHECKPRGRAM) $(MEMCHECKPARAMETERS) ./$(TARGET) $(TESTARGUMENTS)

help:
	@echo "make                - build all and run"
	@echo "make $(TARGET)           - build the executable"
	@echo "make lib$(TARGET).a      - build the static library"
	@echo "make run            - run $(TARGET)"
	@echo "make clean          - clean the build directory"
	@echo "make mem-check      - performs a memory check for memory leak detection"
