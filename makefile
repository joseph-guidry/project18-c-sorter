#
#	Make File for Wordsorter Project
#

all: wordsorter

wordsorter: wordsorter.c
	gcc -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -o wordsorter wordsorter.c
    
clean:
	rm -rf ./*
