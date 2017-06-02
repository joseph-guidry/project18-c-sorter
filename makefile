#
#	Make File for Wordsorter Project
#

all: wordsorter

wordsorter: main.c wordCount.o sortFunction.o
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o main main.c wordCount.o sortFunction.o
    
clean:
	rm -rf ./*
