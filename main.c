#include <string.h>
#include <stdlib.h>

#include "wordsort.h"

void addWords(char **words, int count, char * file);

int main(int argc, char **argv)
{
	int wordcount;
	int argnum = 0, rev = 0; 
	char **words, *p, option = 'a', prevop;
	char filename[50];
	void (*add)(char**, int, char *) = addWords;
	//int (*compare)(char *, char*) = alphaForward;
	
	
	wordcount = wordCounter(argc, argv + 1);
	printf("End: [%d] \n", wordcount);
	words = malloc(wordcount * sizeof(words));
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
				prevop = option;
				option = *++p;
				printf("This is the option: %c \n", option);
				switch (option)
				{
				case 'h':
					printf("HELP!!!\n");
					exit(1);
				case 'l':
					printf("BY LENGHT\n");
					break;
				case 'n':
					printf("WE'VE GOT NUMBERS PEOPLE\n");
					break;
				case 'r':
				//MULTIPLE CALLS WILL CANCEL THE USE OF THIS OPTION
					rev++;
					if (rev % 2 == 1)
					{
						printf("LETS REVERSE\n");
						break;
					}
					else 
					{
						printf("UNREVERSE\n");
						option = prevop;
					}
					break;
				case 's':
					printf("LETS SCRABBLE IT UP\n");
					break;
				case 'c':  //WILL BE FOLLOWED BY A NUMBER OF LINES TO PRINT
					printf("%s \n", argv[++argnum]);
					//printNum = argv[++argnum];
					printf("LETS CAP IT\n");
					break;
				case 'a':
					printf("WE ARE THE DEFAULT \n");
					break;
				case 'u':
					printf("THESE MUST BE UNIQUE\n");
					//add = addUnique;
					break;
				default:
					printf("I DONT KNOW THIS OPTION\n");
					break;
				}
			}
			else if( (p - argv[argnum]) == 0 ) 
			{
				printf("|File|%s|\n", p);
				strcpy(filename, p);
				printf("Filename: [%s] Option: [%c]\n", filename, option);
				//if( option 
				add(words, wordcount, filename);
				break;
				//MOVE POINTER TO END OF ARG?
			}
			//printf("|%c|%c|\n", *p, *p + 1);
			
		}
		
		/*
		printf("GET WORDS FROM FILENAME\n");
		printf("SORT WORDS\n");-> do qsort();
		printf("PRITN WORDS\n");
		*/
		printf("Print words array\n");
		
		for (int x = 0; x < wordcount ; x++)
		{
			printf("Word %d | %s \n", x, words[x]);
		}
	}
	
	for (int x = 0; x < wordcount ; x++)
	{
		free(words[x]);
	}
	free(words);
	
	return 0;
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


