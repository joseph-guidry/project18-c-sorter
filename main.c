#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int wordCounter(int argc, char **argv);
void countWords(FILE * fp, int * total);

int main(int argc, char **argv)
{
	int wordcount;
	int argnum = 0, rev = 0; 
	char **words, *p, option;
	//char filename[50];
	//char functionOp;
	
	wordcount = wordCounter(argc, argv);
	printf("End: [%d] \n", wordcount);

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
				
					// SAVE PREVIOUS OPTION;
					rev++;
					if (rev % 2 == 1)
					{
						printf("LETS REVERSE\n");
						break;
					}
					else 
					{
						printf("UNREVERSE\n");
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
			
		}
		
	}
	
	return 0;
}

int wordCounter(int argc, char **argv)
{
	FILE *fp;
	int totalwords = 0;
	printf("in wordCounter\n");
	while (--argc > 0)
	{

		if (*argv++[0] != '-')
		{
			printf("line 25 [%s]\n", *argv);
			if ( (fp = fopen(*argv , "r")) != NULL)
			{
				countWords(fp, &totalwords);
			}
		}
	}
	printf("%d \n", totalwords);
	return totalwords;
}

void countWords(FILE * fp, int * total)
{
	char letter;
	printf("in countWords5\n");
	while( (letter = getc(fp)) != EOF)
    {
        if ( (letter == ' ') || (letter =='\n') || (letter == '\t') )
        {
            (*total)++;
        }
    }
    printf("Words: [%d] \n", *total);
}
