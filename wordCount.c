#include "wordsort.h"

int wordCounter(int argc, char **argv)
{
	FILE *fp;
	int totalwords = 0;
	printf("in wordCounter\n");
	while (--argc > 0)
	{
		printf("argc = %d \n", argc);
		printf("line 10 [%s]\n", argv[0]);
		if (*argv[0] != '-')
		{
			printf("line 13 [%s]\n", *argv);
			//continue;
			if ( (fp = fopen(*argv , "r")) != NULL)
			{
				countWords(fp, &totalwords);
			}
			
		}
		argv++;
		
	}
	printf("%d \n", totalwords);
	return totalwords;
}

void countWords(FILE * fp, int * total)
{
	char letter;
	printf("in countWords\n");
	while( (letter = getc(fp)) != EOF)
    {
    	printf("[%c] \n", letter);
        if ( (letter == ' ') || (letter =='\n') || (letter == '\t') )
        {
            (*total)++;
        }
    }
    printf("Words: [%d] \n", *total);
}
