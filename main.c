#include <stdio.h>

int wordCounter(int argc, char **argv);
void countWords(FILE * fp, int * total);

int main(int argc, char **argv)
{
	int wordcount;
	
	wordcount = wordCounter(argc, argv);
	
	printf("End: [%d] \n", wordcount);
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
