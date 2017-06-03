#include "wordsort.h"

int wordCounter(int argc, char **argv)
{
	FILE *fp;
	int totalwords = 0;
#ifdef DEBUG
	printf("in wordCounter\n");
#endif
	while (--argc > 0)
	{
#ifdef DEBUG
		printf("argc = %d \n", argc);
		printf("line 10 [%s]\n", argv[0]);
#endif
		if (*argv[0] != '-')
		{
#ifdef DEBUG
			printf("line 13 [%s]\n", *argv);
#endif
			if ( (fp = fopen(*argv , "r")) != NULL)
			{
				countWords(fp, &totalwords);
			}
		}
		argv++;
		
	}
#ifdef DEBUG
	printf("%d \n", totalwords);
#endif
	fclose(fp);
	return totalwords;
}

void countWords(FILE * fp, int * total)
{
	char letter;
	char prevLetter = ' ';
#ifdef DEBUG
	printf("in countWords\n");
#endif
	while( (letter = getc(fp)) != EOF)
    {
#ifdef DEBUG
    	printf("[%c] [%c]\n", letter, prevLetter);
#endif
        if ( !(isspace(letter) )  &&  ( (prevLetter == ' ') || (prevLetter =='\n') || (prevLetter == '\t')))
        {
#ifdef DEBUG
        	printf("count it [%c]\n", letter);
#endif
            (*total)++;
        }
        prevLetter = letter;
    }
#ifdef DEBUG
    printf("Words: [%d] \n", *total);
#endif
}
