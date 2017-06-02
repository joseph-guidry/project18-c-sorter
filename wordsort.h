#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//SORT FUNCTIONS
int alphaForward(const void * s, const void  * t);
int alphaReverse(const void * s, const void  * t);
int compareLength(const void * s, const void  * t);
int byNumberValue(const void * s, const void  * t);
int scrabbleValue(const void * s, const void  * t);

void printHelp(void);
int scrabbleScore(const char * word);

int wordCounter(int argc, char **argv);
void countWords(FILE * fp, int * total);
