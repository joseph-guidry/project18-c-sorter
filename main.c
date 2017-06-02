#include "wordsort.h"

void addWords(char **words, int count, FILE * file, int * totalNum, char *delims);
void addUniqueWords(char **words, int count, FILE * file, int * totalNum, char *delims);


int main(int argc, char **argv)
{
	FILE *fp = stdin;
	int wordcount;
	int argnum = 0, rev = 0, printNum, totalNum = 0, fileNumber = 0; 
	char **words, *p, option = 'a';
	char filename[50], delims[] = {" \t\n"}; //optpdelims[] = {" \t\n,.:;'\"!@#$%^&*()+-_"};
	
	//FUNCTION POINTERS USED BASED ON OPTIONS
	void (*add)(char**, int , FILE *, int *, char *) = addWords;
	int (*compare)(const void * s, const void  * t) = alphaForward; 
	int (*prevop)();
	
	
	
	//strcpy(filename, stdin);
	wordcount = wordCounter(argc, argv + 1);
	printf("End: [%d] \n", wordcount);
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
					rev = rev % 2;
					/*
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
					*/
					break;
				case 's':
					printf("LETS SCRABBLE IT UP\n");
					compare = scrabbleValue;
					break;
				case 'c':  
					//WILL BE FOLLOWED BY A NUMBER OF LINES TO PRINT
					printNum = atoi(argv[++argnum]);
					printf("LETS CAP IT at %d Words\n", printNum);
					if ( printNum < 1) 
					{
						printHelp();
						exit(3);
					}
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
				//STDIN BY DEFAULT?  IF IT GETS HERE IT should change to filename.
				printf("|File|%s|\n", p);
				

				strcpy(filename, p);
				
				FILE *fp;
				
				fp = fopen(filename, "r");
				if (fp == NULL)
				{
					fprintf(stderr, "%s could not open\n", filename);
					break;
				}
				
				printf("Filename: [%s] Option: [%c]\n", filename, option);
				add(words, wordcount, fp, &totalNum, delims);
				printf("wordcount: [%d] \n", wordcount);
				
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
		printf("Get input from a stdin\n");
		add(words, wordcount, fp, &totalNum, delims);
		printNum = totalNum;
	}				
	
	printf("wordcount: [%d] printNum: [%d] totalNum [%d]\n", wordcount, printNum, totalNum);
	//SORT WORDS BASED ON OPTION SELECTED
	qsort(words, totalNum, sizeof(char *), compare);
	printf("after qsort line 145\n");
	
	printf("Print words array|printNum = %d \n", printNum);
	
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
	printf("in addUnique %d wordcount %d num\n", count , num);
	*totalNum +=( num - start);
	fclose(file);
	return;
}

void addWords(char **words, int count, FILE * file, int * totalNum, char *delims)
{
	char input[100], *p;
	static int num = 0;
	int start = num;
	printf("in addwords num = %d \n", num);
	while ( fgets(input, 100, file) )
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
	*totalNum +=( num - start);
 	printf("in addUnique %d wordcount %d num %d totalnum \n", count , num, *totalNum);
	fclose(file);
	return;
}
