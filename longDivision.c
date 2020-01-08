#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*The program receives as arguments, two unsigned integers, first the dividend and then the divisor. The dividend should alwyas be >= the divisor.

This program uses an implementation of the "longSubtraction" program that's way the variable names are the ones of the "longSubtraction".

NOTE: the coutient will replace the dividend, so you may want to copy it to a different location.
*/

char *longDivision(char *dividend, char divisor[]);
int noArguments(int argc, char * argv[], char* version, char* author);

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
	unsigned long long minuendSize = strlen(minuend), subtrahendSize = strlen(subtrahend), resultSize;
	char *result, *absMinuend, *absSubtrahend, *cuotient, subChar[2];
	bool remainderZero = false;
	int sub, loans;
	
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

	while(!remainderZero )
	{		
		//Subtraction loop, it's practically the same as in "LongSubtraction"
		unsigned long long int subIndex = resultSize; // we subtract from left to right.
		do
		{
			subIndex--;	
			sub = (absMinuend[subIndex] - '0') - (absSubtrahend[subIndex] - '0');
			if(sub < 0 && subIndex > 0)//case when we have, for example: 54678-9 
			{
				sub +=10;
				
				int next = 1;
				loans = absMinuend[subIndex - next] - '0';//the one who loans 1
				
				while(loans == 0)// when in minuend we have, for exmple: 50008 - 9
				{
					absMinuend[ subIndex - next ] = '9';
					next++;
					loans = absMinuend[ subIndex - next ] - '0';	
				}
				sprintf(subChar,"%u", loans-1);
				absMinuend[ subIndex - next ] = subChar[0];
			}
			sprintf(subChar,"%u", sub);
			result[ subIndex ] = subChar[0];
			
		}while(subIndex > 0);//subIndex is unsigned so it'd cause a runtime error if it gets to -1
		/*Here we check if we have a reminder of zero, in that case the we've finished long division*/
		
		//printf("%s\n", result);
		//getchar();		
		remainderZero = true;
		unsigned long long zeros = 0;
		for(unsigned long long index = 0; index<resultSize && remainderZero; index++)
			if( result[index] != '0')
				remainderZero = false;
			else
				zeros++;
		/**************************************/
		
		/*Here we add one to the cuotient, since we've been able to subtract once the subtrahend from the minuend*/
		long int CuotientIndex = resultSize;
		bool added = false;
		do
		{
			CuotientIndex--;
			if(cuotient[CuotientIndex] < '9')
			{
				cuotient[CuotientIndex]++;
				added = true;
			}
			else if( CuotientIndex > 0)
				cuotient[CuotientIndex] = '0';

		}while( CuotientIndex > 0 && !added );
		/*************************************/	
		
		strcpy(absMinuend, result);// we use the last result as our new minuend
		
		
		if( resultSize - (zeros) == subtrahendSize )
			remainderZero = ( ( (absMinuend[zeros]-'0') - (subtrahend[0]-'0') ) < 0 ) ? true: false;
  		else if( resultSize - (zeros) < subtrahendSize )
			remainderZero = true;
	}
	
	//most of the times you'll have spare zeros in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 1)
		memmove(result, result+1, resultSize*sizeof(char)+1);
	while(cuotient[0] == '0' && strlen(result) > 1)
		memmove(cuotient, cuotient+1, resultSize*sizeof(char)+1);
	
	strcpy(minuend, cuotient);// so the value pointed by the minuend is now our cuotient
	
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
