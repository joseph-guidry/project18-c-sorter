#include <string.h>
#include <stdlib.h>

#include "wordsort.h"

int main(int argc, char **argv)
{
	int wordcount;
	int argnum = 0, rev = 0; 
	char **words, *p, option = 'a', prevop;
	//char filename[50];
	//char functionOp;
	
	wordcount = wordCounter(argc, argv + 1);
	printf("End: [%d] \n", wordcount);
//exit(10);
	words = malloc(wordcount * sizeof(words));
	if (words == NULL)
	{
		fprintf(stderr, "Failed to get memory for words\n");
		exit(1);
	}
	//argnum = argc;
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
				
					printf("%c \n", prevop);
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
					break;
				default:
					printf("I DONT KNOW THIS OPTION\n");
					break;
				}
				break;		
			}
			/*printf("after switch\n");
			
			if( (*p != '-') &&  ((p - argv[argnum]) == 0 ) )
			{
				//printf("|File|%s|\n", p);
				strcpy(filename, p);
				break;
				//MOVE POINTER TO END OF ARG?
			}

			//printf("|%c|%c|\n", *p, *p + 1);
			*/
		}
		printf("Option: [%c]\n", option);
		/*
		printf("GET WORDS FROM FILENAME\n");
		printf("SORT WORDS\n");
		printf("PRITN WORDS\n");
		printf("next arg\n");
		*/
	}
	
	return 0;
}
