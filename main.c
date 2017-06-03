#include "wordsort.h"

void addWords(char **words, int count, FILE * file, int * totalNum, char *delims);
void addUniqueWords(char **words, int count, FILE * file, int * totalNum, char *delims);


int main(int argc, char **argv)
{
	FILE *fp = stdin;
	int wordcount;
	int argnum = 0, rev = 0, printNum, totalNum = 0, fileNumber = 0; 
	char **words, *p, option = 'a';
	char filename[50], delims[22]; //optpdelims[] = {" \t\n,.:;'\"!@#$%^&*()+-_"};
	
	strcpy(delims, " \t\n");


	//FUNCTION POINTERS USED BASED ON OPTIONS
	void (*add)(char**, int , FILE *, int *, char *) = addWords;
	int (*compare)(const void * s, const void  * t) = alphaForward; 
	
	wordcount = wordCounter(argc, argv + 1);
#ifdef DEBUG
	printf("End: [%d] \n", wordcount);
#endif
	words = malloc(wordcount * sizeof(words));
	
	for (int x = 1; x < argc; x++)
	{
		if (argv[x][0] != '-')
			fileNumber++;
	}
	
	//Default is to print all words
	printNum = wordcount;
	
	if (words == NULL)
	{
		fprintf(stderr, "Failed to get memory for words\n");
		exit(1);
	}
	while (++argnum < argc)
	{
#ifdef DEBUG
		printf("[%d] [%d]\n", argc, argnum);
#endif
		p = argv[argnum];
		
		for (; p < p + strlen(p); p++)
		{
			if(*p == '-')
			{
#ifdef DEBUG
				printf("I am an option\n");
#endif
				option = *++p;
				
#ifdef DEBUG
				printf("This is the option: %c \n", option);
#endif
				switch (option)
				{
				case 'h':
#ifdef DEBUG
					printf("HELP!!!\n");
#endif
					printHelp();
					exit(1);
				case 'l':
#ifdef DEBUG
					printf("BY LENGHT\n");
#endif
					compare = compareLength;
					break;
				case 'n':
#ifdef DEBUG
					printf("WE'VE GOT NUMBERS PEOPLE\n");
#endif
					compare = byNumberValue;
					break;
				case 'r':
				//MULTIPLE CALLS WILL CANCEL THE USE OF THIS OPTION
					rev++;
					rev = rev % 2;
					break;
				case 's':
#ifdef DEBUG
					printf("LETS SCRABBLE IT UP\n");
#endif
					compare = scrabbleValue;
					break;
				case 'c':  
					//WILL BE FOLLOWED BY A NUMBER OF LINES TO PRINT
					printNum = atoi(argv[++argnum]);
#ifdef DEBUG
					printf("LETS CAP IT at %d Words\n", printNum);
#endif
					if ( printNum < 1) 
					{
						printHelp();
						exit(3);
					}
					break;
				case 'a':
#ifdef DEBUG
					printf("WE ARE THE DEFAULT \n");
#endif
					compare = alphaForward;
					break;
				case 'u':
#ifdef DEBUG
					printf("THESE MUST BE UNIQUE\n");
#endif
					add = addUniqueWords;
					break;
/*
				case 'p':
					strcpy(delims, " \t\n,.:;'!@#$%^&*()+-_");
					break;
*/
				default:
#ifdef DEBUG
					printf("I DONT KNOW THIS OPTION\n");
#endif
					printHelp();
					exit(2);
				}
			}
			else if( (p - argv[argnum]) == 0 ) 
			{
				//STDIN BY DEFAULT?  IF IT GETS HERE IT should change to filename.
#ifdef DEBUG
				printf("|File|%s|\n", p);
#endif
				

				strcpy(filename, p);
				
				FILE *fp;
				
				fp = fopen(filename, "r");
				if (fp == NULL)
				{
					fprintf(stderr, "%s could not open\n", filename);
					break;
				}
#ifdef DEBUG
				printf("Filename: [%s] Option: [%c]\n", filename, option);
#endif
				add(words, wordcount, fp, &totalNum, delims);
#ifdef DEBUG
				printf("wordcount: [%d] \n", wordcount);
#endif
				
				break;
			}
		}
	}
	
	//TO GET WORDS FROM THE STDIN
	if (fileNumber < 1)
	{
		//IF NO FILENAME WAS GIVEN
								
		wordcount = 100;
		words = malloc( wordcount * sizeof(char *));
		if (words == NULL)
		{
			fprintf(stderr, "No memory for wordlist \n");
			exit(4);
		}
#ifdef DEBUG
		printf("Get input from a stdin\n");
#endif
		add(words, wordcount, fp, &totalNum, delims);
		printNum = totalNum;
	}				
#ifdef DEBUG
	printf("wordcount: [%d] printNum: [%d] totalNum [%d]\n", wordcount, printNum, totalNum);
#endif
	//SORT WORDS BASED ON OPTION SELECTED
	qsort(words, totalNum, sizeof(char *), compare);
#ifdef DEBUG
	printf("after qsort line 145\n");
#endif
	
#ifdef DEBUG	
	printf("Print words array|printNum = %d \n", printNum);
#endif
	
	if (rev == 1)
	{
		for ( int x = printNum -1; x >= 0; x--)
		{
			if ( words[x] == NULL)
			{
				continue;
			}
			printf("Word %4d | %s \n", x + 1, words[x]);
		}
	}
	else
	{
		for (int x = 0; x < printNum ; x++)
		{
			if ( words[x] == NULL)
			{
				continue;
			}
			printf("Word %4d | %s \n", x + 1, words[x]);
		}
	}

#ifdef DEBUG
	printf("After printing words\n");
#endif
	for (int x = 0; x < wordcount ; x++)
	{
		free(words[x]);
	}
	free(words);
	
	return 0;
}

void addUniqueWords(char **words, int count, FILE * file, int * totalNum, char *delims)
{
	char input[100], *p; // delims[] = " \t\n";
	static int num = 0;
	int start = num;
	
	
	while ( fgets(input, 100, file) )
	{
		p = strtok(input, delims);
		while ( p != NULL)
		{
			//ADD CHECK AGAIN WORDS ARRAY
#ifdef DEBUG
			printf("line 289: Token %d| %s \n", num, p);
#endif
			
			for (int x = 0; x < num; x++)
			{
#ifdef DEBUG
				printf("checking the word %s against %s \n", p, words[x]);
#endif
				if ( strcmp(words[x], p) == 0)
				{
					p = strtok(NULL, delims);
#ifdef DEBUG
					printf("line 297: Token %d| %s \n", num, p);
#endif
					break;
				}
			}
			if (p == NULL)
			{
				//Ensure NULL is not passed out of the for loop
				continue;
			}
			
			//BELOW = ORIGINAL
#ifdef DEBUG
			printf("before malloc| size of p: %ld\n", sizeof(p));
#endif
			words[num] = (char *) malloc(sizeof(p));
#ifdef DEBUG
			printf("line 303: Token %d| %s \n", num, p);
#endif
			if ( num == count) 
			{
				fprintf(stderr,"Out of memory \n");
				return;
			}
			strcpy(words[num++], p);
			
#ifdef DEBUG
			printf("Token %d| %s \n", num, words[num - 1]);
#endif
			p = strtok(NULL, delims);
		}

	}
#ifdef DEBUG
	printf("in addUnique %d wordcount %d num\n", count , num);
#endif
	*totalNum +=( num - start);
	fclose(file);
	return;
}

void addWords(char **words, int count, FILE * file, int * totalNum, char *delims)
{
	char input[100], *p;
	static int num = 0;
	int start = num;
#ifdef DEBUG
	printf("in addwords num = %d \n", num);
#endif
	while ( fgets(input, 100, file) )
	{
		p = strtok(input, delims);
#ifdef DEBUG
		printf("on line 336|p: [%s]\n", p);
#endif
		while ( p != NULL)
		{
#ifdef DEBUG
			printf("before malloc| size of p: [%s]\n", p);
#endif
			words[num] = (char *) malloc(sizeof(p));
#ifdef DEBUG
			printf("Token %d| %s \n", num, p);
#endif
			if ( num == count)
			{
				fprintf(stderr,"Out of memory \n");
				return;
			}
			strcpy(words[num++], p);
#ifdef DEBUG
			printf("Token %d| %s \n", num, words[num - 1]);
#endif
			p = strtok(NULL, delims);
		}
	}
	*totalNum +=( num - start);
#ifdef DEBUG
 	printf("in addUnique %d wordcount %d num %d totalnum \n", count , num, *totalNum);
#endif
	fclose(file);
	return;
}
