#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*The program receives as arguments, two unsigned integers

Example:

./longAddition 343456778384378290000000 34434999588887878867487736273762731116372
*/
int noArguments(int argc, char * argv[], char* version, char* author);
char* longAddition( char* summand1,  char* summand2);

int main(int argc, char* argv[])
{	char *result;
	
	noArguments(argc, argv, "1.0", "Aisaac23");
	result = longAddition(argv[1], argv[2]);
	printf("\nResult: %s\n\n", result);
	
}

char* longAddition( char* summand1,  char* summand2)
{
	unsigned long long summand1Size = strlen(summand1), summand2Size = strlen(summand2);
	
	unsigned long long resultSize = (summand1Size >= summand2Size) ? summand1Size+1 : summand2Size+1, accomulator = 0, newSize = 0;
	
	char *normalizedSummand1, *normalizedSummand2, *result, sumChar[2]; 
	unsigned int sum = 0;
	
	// We need to prepare the space for normalized summands and the result... 
	result = calloc( resultSize+1, sizeof(char) );
	normalizedSummand1 = calloc( resultSize+1, sizeof(char) );
	normalizedSummand2 = calloc( resultSize+1, sizeof(char) );

	for(unsigned long long i = 0; i<resultSize; i++)
			result[i] = normalizedSummand1[i] = normalizedSummand2[i] = '0';
	
	//... which means that regardless whether summand1 has more digits than summand2, we create a same-size array for each 	
	// example: 1234 + 12 gets converted to: 1234 + 0012
	memmove( normalizedSummand1+(resultSize-summand1Size), summand1, summand1Size*sizeof(char) );
	memmove( normalizedSummand2+(resultSize-summand2Size), summand2, summand2Size*sizeof(char) );
	
	result[resultSize] = normalizedSummand2[resultSize] = normalizedSummand1[resultSize] = '\0';
	
	//printf("%s + %s = %s\n", normalizedSummand1, normalizedSummand2, result);
	
	for(long int rIndex = resultSize-1; rIndex >= 0; rIndex--)// we sum from left to right.
	{
		sum = (normalizedSummand1[rIndex]-'0') + (normalizedSummand2[rIndex]-'0'); 
		
		sum+=accomulator;
		accomulator = (sum > 9) ? sum/10 : 0;
		sum = (sum > 9) ? sum%10 : sum;
		
		sprintf(sumChar,"%u", sum);
		result[rIndex] = sumChar[0];
	}
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);
	
	//Finally we resize the result to get only the useful numbers.
	newSize = strlen(result);
	result = realloc(result, newSize);
	
	free(normalizedSummand1);
	free(normalizedSummand2);

	return result;
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
