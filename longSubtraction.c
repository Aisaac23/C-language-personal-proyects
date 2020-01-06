#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *longSubtraction(char minuend[], char subtrahend[]);
int noArguments(int argc, char * argv[], char* version, char* author);
/*The program receives as arguments, two unsigned integers, first the minuend and then the subtrahend.*/
int main(int argc, char* argv[])
{
	noArguments(argc, argv, "1.0", "Aisaac23");
	char *result;
	result = longSubtraction(argv[1], argv[2]);
	
	printf("\nResult: %s\n", result);
	
	return EXIT_SUCCESS;
}

char *longSubtraction(char minuend[], char subtrahend[])
{
	long int minuendSize = strlen(minuend), subtrahendSize = strlen(subtrahend), resultSize, newSize;
	int sub, loans;
	char *result, *absMinuend, *absSubtrahend, minuendDigit[2], subtrahendDigit[2], subChar[2];
	bool negativeResult = false;
	
	resultSize = (minuendSize >= subtrahendSize) ? minuendSize : subtrahendSize;
	
	// We prepare the size for the result and for normalized minuend and subtrahend, so 1234 - 45 turns into: 1234 - 0045
	result = calloc( resultSize+1, sizeof(char) );//+2 to have space for the sign and for the \0
	absMinuend = calloc( resultSize+1, sizeof(char) );
	absSubtrahend = calloc( resultSize+1, sizeof(char) );

	for(long int i = 0; i<resultSize; i++)
			result[i] = absMinuend[i] = absSubtrahend[i] = '0';
	/*I turned these commented lines in the two that are bellow them... Leaving this as an achievment mark:	
	if( minuendSize > subtrahendSize )
	{
		long int absIndex = resultSize-1;
		for(long int i = subtrahendSize-1; i>=0; i--)
			absSubtrahend[absIndex--] = subtrahend[i];	
		strcpy(absMinuend, minuend);
	}
	else if( minuendSize < subtrahendSize )
 	{
		long int absIndex = resultSize;
		for(long int i = minuendSize-1; i>=0; i--)
			absMinuend[--absIndex] = minuend[i];
		strcpy(absSubtrahend, subtrahend);
	}
	else
	{
		strcpy(absMinuend, minuend);
		strcpy(absSubtrahend, subtrahend);
	}*/
	memmove( absMinuend+(resultSize-minuendSize), minuend, minuendSize*sizeof(char) );
	memmove( absSubtrahend+(resultSize-subtrahendSize), subtrahend, subtrahendSize*sizeof(char) );
	
	// the next 10 lines of code check if the result will be negative, which is important so we can add a sign (-) 
	//at the end and make a proper calculation.
	minuendDigit[0] = absMinuend[0];
	subtrahendDigit[0] = absSubtrahend[0];
	sub = atoi(minuendDigit) - atoi(subtrahendDigit);
	if(minuendSize < subtrahendSize || ( minuendSize == subtrahendSize && sub<0 ) )
	{
		negativeResult = true;
		strcpy(result, absMinuend);
		strcpy(absMinuend, absSubtrahend);
		strcpy(absSubtrahend, result);
	}
	
	absMinuend[resultSize] = '\0';
	absSubtrahend[resultSize] = '\0';
	minuendDigit[1] = subtrahendDigit[1] = '\0'; 
	result[resultSize] = '\0';
	
	for(long int index = resultSize-1; index >= 0; index--)// we subtract from left to right.
	{
		minuendDigit[0] = absMinuend[index];
		subtrahendDigit[0] = absSubtrahend[index];
		
		sub = atoi(minuendDigit) - atoi(subtrahendDigit); //we first get the one digit and then make a subtraction
		if(sub < 0 && index > 0)// this is for cases like: 0 - 9
		{
			sub +=10;
			
			int next = 1;
			subChar[0] = absMinuend[index-next];
			loans = atoi( subChar );//the one who loans 1
			
			while(loans == 0) // for succesive zeros on the minuend
			{
				sprintf(subChar,"%u", 9);
				absMinuend[index - next] = subChar[0];
				next++;
				subChar[0] = absMinuend[index-next];
				loans = atoi( subChar );	
			}
			sprintf(subChar,"%u", loans-1);
			absMinuend[index - next] = subChar[0];
		}

		sprintf(subChar,"%u", sub);
		result[index] = subChar[0];
	}
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);
	
	if(negativeResult) //if the result was negative, we add the - sign.
	{
		result = realloc( result, resultSize*sizeof(char)+2 );
		memmove(result+1, result, resultSize*sizeof(char)+1);
		result[0]='-';	
	}
	
	//Finally we resize the result to get only the useful numbers.
	newSize = strlen(result);
	result = realloc(result, newSize);
	
	free(absSubtrahend);
	free(absMinuend);

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
