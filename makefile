#
#	Make File for Wordsorter Project
#

all: wordsorter

wordsorter: main.c wordCount.o
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o main main.c wordCount.o
    
clean:
	rm -rf ./*
