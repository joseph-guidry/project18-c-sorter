#
#	Make File for Wordsorter Project
#

all: wordsorter

wordsorter: main.c wordCount.o sortFunction.o
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o ws main.c wordCount.o sortFunction.o

debug: main.c wordCount.o sortFunction.o
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -DDEBUG -o ws main.c wordCount.o sortFunction.o    

clean:
	rm ./*
