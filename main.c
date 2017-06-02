#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "wordsort.h"

//SORT FUNCTIONS
int alphaForward(const void * s, const void  * t);
int alphaReverse(const void * s, const void  * t);
int compareLength(const void * s, const void  * t);
int byNumberValue(const void * s, const void  * t);
int scrabbleValue(const void * s, const void  * t);

void addWords(char **words, int count, char * filename);
void addUniqueWords(char **words, int count, char * filename);
void printHelp(void);
int scrabbleScore(const char * word);

int main(int argc, char **argv)
{
	int wordcount;
	int argnum = 0, rev = 0, printNum; 
	char **words, *p, option = 'a';
	char filename[50];
	
	//FUNCTION POINTERS USED BASED ON OPTIONS
	void (*add)(char**, int, char *) = addWords;
	int (*compare)(const void * s, const void  * t) = alphaForward; 
	int (*prevop)();
	
	wordcount = wordCounter(argc, argv + 1);
	printf("End: [%d] \n", wordcount);
	words = malloc(wordcount * sizeof(words));
	
	//Default is to print all words
	printNum = wordcount;
	
	if (words == NULL)
	{
		fprintf(stderr, "Failed to get memory for words\n");
		exit(1);
	}
	while (++argnum < argc)
	{
		printf("[%d] [%d]\n", argc, argnum);
		p = argv[argnum];
		
		for (; p < p + strlen(p); p++)
		{
			if(*p == '-')
			{
				printf("I am an option\n");
				prevop = compare;
				option = *++p;
				printf("This is the option: %c \n", option);
				switch (option)
				{
				case 'h':
					printf("HELP!!!\n");
					printHelp();
					exit(1);
				case 'l':
					printf("BY LENGHT\n");
					compare = compareLength;
					break;
				case 'n':
					printf("WE'VE GOT NUMBERS PEOPLE\n");
					compare = byNumberValue;
					break;
				case 'r':
				//MULTIPLE CALLS WILL CANCEL THE USE OF THIS OPTION
					rev++;
					if (rev % 2 == 1)
					{
						printf("LETS REVERSE %d\n", rev);
						compare = alphaReverse;
						break;
					}
					else if ( (argv[argnum - 1][1]) == 'r')
					{
						compare = alphaForward;
					}
					else
					{
						printf("UNREVERSE %d\n", rev);
						compare = prevop; 
					}
					
					break;
				case 's':
					printf("LETS SCRABBLE IT UP\n");
					compare = scrabbleValue;
					break;
				case 'c':  
					//WILL BE FOLLOWED BY A NUMBER OF LINES TO PRINT
					printNum = atoi(argv[++argnum]);
					printf("LETS CAP IT at %d Words\n", printNum);
					break;
				case 'a':
					printf("WE ARE THE DEFAULT \n");
					compare = alphaForward;
					break;
				case 'u':
					printf("THESE MUST BE UNIQUE\n");
					add = addUniqueWords;
					break;
				/*
				case 'p':
					//create -> pass a delimiter array to the function addWords
					break;
				*/
				default:
					printf("I DONT KNOW THIS OPTION\n");
					printHelp();
					exit(2);
				}
			}
			else if( (p - argv[argnum]) == 0 ) 
			{
				printf("|File|%s|\n", p);
				strcpy(filename, p);
				printf("Filename: [%s] Option: [%c]\n", filename, option);
				add(words, wordcount, filename);
				printf("wordcount: [%d] \n", wordcount);
				
				break;
			}
		}
	}
	printf("wordcount: [%d] printNum: [%d]\n", wordcount, printNum);
	//qsort(words, printNum, sizeof(char *), compare);
	printf("after qsort line 128\n");
	
	printf("Print words array\n");
	
	for (int x = 0; x < printNum ; x++)
	{
		if ( words[x] == NULL)
		{
			; //continue;
		}
		printf("Word %4d | %s \n", x, words[x]);
	}
	
	for (int x = 0; x < printNum ; x++)
	{
		free(words[x]);
	}
	free(words);
	
	return 0;
}

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

void addUniqueWords(char **words, int count, char * filename)
{
	FILE *fp;
	char input[100], *p, delims[] = " \t\n";
	static int num = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "%s could not open\n", filename);
	}
	while ( fgets(input, 100, fp) )
	{
		p = strtok(input, delims);
		while ( p != NULL)
		{
			//ADD CHECK AGAIN WORDS ARRAY
			printf("line 289: Token %d| %s \n", num, p);
			
			for (int x = 0; x < num; x++)
			{
				printf("checking the word %s against %s \n", p, words[x]);
				if ( strcmp(words[x], p) == 0)
				{
					p = strtok(NULL, delims);
					printf("line 297: Token %d| %s \n", num, p);
					break;
				}
			}
			if (p == NULL)
			{
				//Ensure NULL is not passed out of the for loop
				continue;
			}
			
			//BELOW = ORIGINAL
			printf("before malloc| size of p: %ld\n", sizeof(p));
			words[num] = (char *) malloc(sizeof(p));
			printf("line 303: Token %d| %s \n", num, p);
			if ( num == count)
			{
				fprintf(stderr,"Out of memory \n");
				return;
			}
			strcpy(words[num++], p);
			printf("Token %d| %s \n", num, words[num - 1]);
			p = strtok(NULL, delims);
		}

	}
	printf("here\n");
	fclose(fp);
	return;
}

void addWords(char **words, int count, char * filename)
{
	FILE *fp;
	char input[100], *p, delims[] = " \t\n";
	static int num = 0;
	
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "%s could not open\n", filename);
	}
	
	printf("in addwords num = %d \n", num);
	while ( fgets(input, 100, fp) )
	{
		p = strtok(input, delims);
		printf("on line 336|p: [%s]\n", p);
		while ( p != NULL)
		{
			printf("before malloc| size of p: [%s]\n", p);
			words[num] = (char *) malloc(sizeof(p));
			printf("Token %d| %s \n", num, p);
			if ( num == count)
			{
				fprintf(stderr,"Out of memory \n");
				return;
			}
			strcpy(words[num++], p);
			printf("Token %d| %s \n", num, words[num - 1]);
			p = strtok(NULL, delims);
		}
	}
	fclose(fp);
	return;
}


