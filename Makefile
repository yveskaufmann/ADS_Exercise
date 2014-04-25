#
# Algorithm and data structures
# Exercise: 01_List 
#
# Author: Yves Kaufmann
# 

CC=gcc
OPTIONS=-g -Wall -std=c99 -pedantic -Winline -x c
DEBUG_OPTIONS= -Oo -fno-inline
TARGET=list

DOC=doxygen
DOCCONFIG=doxygen.config

MEMCHECKPRGRAM=valgrind 
MEMCHECKPARAMETERS=--tool=memcheck 

TESTARGUMENTS=


all: *.c
	$(CC) $(OPTIONS) main.c list.c -o $(TARGET) 

doc:	*.c
	$(DOC) $(DOCCONFIG) $(TARGET)

doc-gen-config-file:
	$(DOC) -g $(DOCCONFIG)

mem-check:
	$(MEMCHECKPRGRAM) $(MEMCHECKPARAMETERS) ./$(TARGET) $(TESTARGUMENTS)

format: *.c
	$(FORMATPROGRAM) $(TARGET)

run:
	./$(TARGET) $(TESTARGUMENTS)

clean:
	rm -f $(TARGET)

doc-clean:
	rm -rf latex
	rm -rf html

help:
	@echo Targets
	@echo : doc 
	@echo : doc-gen-config-file 
	@echo : doc-clean 
	@echo : mem-check
	@echo : clean
	@echo : run
	@echo : debug
