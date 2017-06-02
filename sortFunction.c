#include "wordsort.h"

int scrabbleValue(const void * s, const void  * t)
{	
	const char **is = (const char **)s;
	const char **it = (const char **)t;
	return (scrabbleScore(*it) < scrabbleScore(*is));
}

int scrabbleScore(const char * word)
{
	int total = 0;
	printf("Scrabble word: [%s] \n", word);
	for (; word < word + strlen(word); word++)
	{
		switch (tolower(*word))
		{
			case 'a':
			case 'e':
			case 'i':
			case 'l':
			case 'n':
			case 'o':
			case 'r':
			case 's':
			case 't':
			case 'u':
				printf("letter: [%c] \n", *word);
				total += 1;
				break;
			case 'd':
			case 'g':
				printf("letter: [%c] \n", *word);
				total += 2;
				break;
			case 'b':
			case 'c':
			case 'm':
			case 'p':
				printf("letter: [%c] \n", *word);
				total += 3;
				break;
			case 'f':
			case 'h':
			case 'v':
			case 'w':
			case 'y':
				printf("letter: [%c] \n", *word);
				total += 4;
				break;
			case 'k':
				printf("letter: [%c] \n", *word);
				total += 5;
				break;
			case 'j':
			case 'x':
				printf("letter: [%c] \n", *word);
				total += 8;
				break;
			case 'q':
			case 'z':
				printf("letter: [%c] \n", *word);
				total += 10;
				break;
			default:
				printf("not a scrabble character: %c \n", *word);
				break;
				
		}
	}
	printf("Total value for %s is %d \n", word, total);
	return total;
}

int byNumberValue(const void * s, const void  * t)
{	
	const char **is = (const char **)s;
	const char **it = (const char **)t;
	return (atoi(*it) < atoi(*is));
}


int compareLength(const void * s, const void  * t)
{
	const char **is = (const char **)s;
	const char **it = (const char **)t;
	return (strlen(*it) < strlen(*is));
}

int alphaReverse(const void * s, const void  * t)
{
	const char **is = (const char **)s;
	const char **it = (const char **)t;
	return strcmp(*it, *is);
}

int alphaForward(const void * s, const void  * t)
{	
	const char **is = (const char **)s;
	const char **it = (const char **)t;
	return (strcmp(*is, *it));
}

void printHelp(void)
{
	puts("Usage:  wordsorter <options> <filename> <filenames...>\n"
		 "options:\n\n"
		 "\t-l 		-sort by word length\n"
		 "\t-c <n>	\t-print n number of lines.\n"
		 "\t-r		-reverse sort order\n"
		 "\t-s 		-sort based on words value in Scrabble\n"
		 "\t-a		-lexigraphical (default) sort\n"
		 "\t-n		-sort in numerical value order\n"
		 "\t-u		-print only unique words\n"
		 "\t-h		-print this help menu\n"
		 "\t-p		-print words with no punctuation\n"
		 "\n\t Option selected will be most recent( last option on command line)\n"
		 "\t Option -r will be canceled upon pairs of reverse sort calls\n\n"); 
		
}


