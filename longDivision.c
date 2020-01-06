#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *longDivision(char *dividend, char divisor[]);
int noArguments(int argc, char * argv[], char* version, char* author);
/*The program receives as arguments, two unsigned integers, first the dividend and then the divisor.*/
int main(int argc, char* argv[])
{
	noArguments(argc, argv, "1.0", "Aisaac23");
	char *result;
	char *cuotient = calloc(strlen(argv[1])+1, sizeof(char));
	strcpy(cuotient, argv[1]);
	result = longDivision(cuotient, argv[2]);
	
	printf("Reminder: %s, Cuotient: %s\n", result, cuotient);
	
	return EXIT_SUCCESS;
}

char *longDivision(char *minuend, char subtrahend[])
{
	//With this one I reused the longSubtraction's function code and made some modifications.  
	unsigned long long minuendSize = strlen(minuend), subtrahendSize = strlen(subtrahend), resultSize, newSize;
	int sub, loans;
	char *result, *absMinuend, *absSubtrahend, *cuotient, minuendDigit[2], subtrahendDigit[2], subChar[2];
	bool remainderZero = false;
	
	resultSize = (minuendSize >= subtrahendSize) ? minuendSize : subtrahendSize;
	
	result = calloc( resultSize+1, sizeof(char) );
	absMinuend = calloc( resultSize+1, sizeof(char) );
	absSubtrahend = calloc( resultSize+1, sizeof(char) );
	cuotient = calloc( resultSize+1, sizeof(char) );//added
	
	for(long int i = 0; i<resultSize; i++)
			cuotient[i] = result[i] = absMinuend[i] = absSubtrahend[i] = '0';
		
	memmove( absMinuend+(resultSize-minuendSize), minuend, minuendSize*sizeof(char) );
	memmove( absSubtrahend+(resultSize-subtrahendSize), subtrahend, subtrahendSize*sizeof(char) );	

	absMinuend[resultSize] = result[resultSize] = absSubtrahend[resultSize] = cuotient[resultSize] = '\0';
	minuendDigit[1] = subtrahendDigit[1] = '\0'; 
	
	subtrahendDigit[0] = subtrahend[0];
	int absSubtrahendFirst = atoi(subtrahendDigit);
	while(!remainderZero )
	{
		/***************************************/
		minuendSize = 0;
		int minuendFirst = 1;
		for(long int i = 0; i<resultSize; i++)
			if(absMinuend[i] == '0')
				minuendFirst++;
			else
				i = resultSize;
		minuendSize = strlen(absMinuend) - (minuendFirst-1);
		minuendDigit[0] = absMinuend[ minuendFirst-1 ];
		
		/**************************************************/
		sub = atoi(minuendDigit) - absSubtrahendFirst;
		if(minuendSize < subtrahendSize || ( minuendSize == subtrahendSize && sub<0 ) )
			break;
		
		for(long int index = resultSize-1; index >= 0; index--)// we subtract from left to right.
		{
			minuendDigit[0] = absMinuend[index];
			subtrahendDigit[0] = absSubtrahend[index];
			
			sub = atoi(minuendDigit) - atoi(subtrahendDigit);
			if(sub < 0 && index > 0)
			{
				sub +=10;
				
				int next = 1;
				subChar[0] = absMinuend[index-next];
				loans = atoi( subChar );//the one who loans 1
				
				while(loans == 0)
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
		/*Here we check if we have a reminder of zero, in that case the we've finished long division*/
		remainderZero = true;
		for(unsigned long long index = 0; index<resultSize; index++)
			if( result[index] != '0')
				remainderZero = false;
		/**************************************/
		
		/*Here we add one to the cuotient, since we've been able to subtract once the subtrahend from the minuend*/
		long int CuotientIndex = resultSize-1;
		bool added = false;
		while( CuotientIndex >= 0 && !added )
		{
			if(cuotient[CuotientIndex] < '9')
			{
				cuotient[CuotientIndex]++;
				added = true;
			}
			else if( CuotientIndex > 0)
				cuotient[CuotientIndex] = '0';
			CuotientIndex--;
		}
		/*************************************/	
		strcpy(absMinuend, result);// we use the result of the last result as new minuend

	}
	
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);
	while(cuotient[0] == '0' && strlen(result) > 1)
		memmove(cuotient, cuotient+1, resultSize*sizeof(char)+1);
	
	strcpy(minuend, cuotient);// so the value pointed by the minuend is now our cuotient
	
	newSize = strlen(result);
	result = realloc(result, newSize);
	
	free(absSubtrahend);
	free(absMinuend);
	free(cuotient);

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
