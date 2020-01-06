#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Uses a pointer to a function to print all posible permutations of a given string with all different characters. "printToken" is a pointer to a function with the porpuse of allowing you to customize the output format and even the destination...
*/
void tokenPermutations(unsigned int newSize, char * permutedToken, void (*printToken)( char *token) );
void printToken(char *token);
int noArguments(int argc, char * argv[], char* version, char* author);

int main(int argc, char * argv[])
{	
	
	noArguments(argc, argv, "1.0", "Aisaac23");
	tokenPermutations(strlen(argv[1]), argv[1], printToken);
	
	return EXIT_SUCCESS;
}

void tokenPermutations(unsigned int newSize, char * permutedToken, void (*printToken)( char *token) )
{
	if(newSize == 1)
		return;
	for(int a = 0; a<newSize; a++)
	{
		tokenPermutations(newSize-1, permutedToken, printToken);             
        	if(newSize==2)
            		printToken(permutedToken); 
        	//rotate: depending in the value of newSize we rotate like abcde -> abced or abcde -> abdec
		int k, size = strlen(permutedToken);
		int position = size - newSize;
		char temp = permutedToken[position];

		for(k=position+1; k<size; k++)      
			permutedToken[k-1] = permutedToken[k];
		permutedToken[k-1] = temp; 
		//end of rotate 	
	}
}

void printToken(char *token)
{
	//The following are some posibilities that you use to build your printToken function:
	/*printf("%s\n", token);*/
	
	/*static int count = 1;
	if(count%5 == 0)
		printf("\n");
	else
		printf("%s\n", token);
	count++;*/
	
	/*static int count = 1;
	if(count%5 == 0)
		printf("\n\n");
	else
		printf("%03i:%s\t", count, token);
	count++;*/
	
	/*FILE *tokenFile;
	tokenFile = fopen("tokens.txt", "a+");
	fprintf(tokenFile, token);
	fprintf(tokenFile, ",");
	fclose(tokenFile);*/
	
}

int noArguments(int argc, char * argv[], char* version, char* author)
{
	if(argc <= 1)
	{
		printf("\n%s ver %s by %s\n", argv[0], version, author);
		exit(EXIT_SUCCESS);
	}
	else
		return 1;
}
