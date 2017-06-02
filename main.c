#include <string.h>
#include <stdlib.h>

#include "wordsort.h"

//SORT FUNCTIONS
int alphaForward(const void * s, const void  * t);
int alphaReverse(const void * s, const void  * t);
int compareLength(const void * s, const void  * t);
int byNumberValue(const void * s, const void  * t);

void addWords(char **words, int count, char * file);
void addUniqueWords(char **words, int count, char * filename);
void printHelp(void);

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
						printf("LETS REVERSE\n");
						compare = alphaReverse;
						break;
					}
					else 
					{
						printf("UNREVERSE\n");
						compare = prevop; 
					}
					break;
				case 's':
					printf("LETS SCRABBLE IT UP\n");
					break;
				case 'c':  //WILL BE FOLLOWED BY A NUMBER OF LINES TO PRINT
					printNum = atoi(argv[++argnum]);
					printf("LETS CAP IT at %d Words\n", printNum);
					break;
				case 'a':
					printf("WE ARE THE DEFAULT \n");
					compare = alphaForward;
					break;
				case 'u':
					printf("THESE MUST BE UNIQUE\n");
					//add = addUnique;
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
				break;
			}
		}
	}
	
	qsort(words, wordcount, sizeof(char *), compare);
		
	
	printf("Print words array\n");
	
	for (int x = 0; x < printNum ; x++)
	{
		printf("Word %d | %s \n", x, words[x]);
	}
	
	for (int x = 0; x < wordcount ; x++)
	{
		free(words[x]);
	}
	free(words);
	
	return 0;
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
/*
void addUniqueWords(char **words, int count, char * filename);
{

}
*/
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
	while ( fgets(input, 100, fp) )
	{
		p = strtok(input, delims);
		while ( p != NULL)
		{
			printf("before malloc| size of p: %ld\n", sizeof(p));
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
}


