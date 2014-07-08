#
# Algorithm and data structures
# Exercise: 01_List 
#
# Author: Yves Kaufmann
# 

CC=gcc
OPTIONS=-g -Wall -std=c99 -Winline -x c 
DEBUG_OPTIONS= -Oo -fno-inline
TARGET=stack



DOC=doxygen
DOCCONFIG=doxygen.config

MEMCHECKPRGRAM=valgrind 
MEMCHECKPARAMETERS=--tool=memcheck -v 

TESTARGUMENTS=

.c:
	@echo $*

$(TARGET): *.c
	$(CC) $(OPTIONS) *.c -o $(TARGET) -lm 

doc: *.c
	$(DOC) $(DOCCONFIG) 

doc-gen-config-file:
	$(DOC) -g $(DOCCONFIG)

mem-check:
	$(MEMCHECKPRGRAM) $(MEMCHECKPARAMETERS) ./$(TARGET) $(TESTARGUMENTS)

run: $(TARGET)
	./$(TARGET) $(TESTARGUMENTS)

clean:
	rm -f $(TARGET)

doc-clean:
	rm -rf doc 

help:
	@echo Targets
	@echo : doc
	@echo : doc-gen-config-file 
	@echo : doc-clean 
	@echo : mem-check
	@echo : clean
	@echo : run
	@echo : debug
