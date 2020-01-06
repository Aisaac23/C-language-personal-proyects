//The following program allows you to calculate from up to 99!

/*
The greater N! that you can calculate in an average computer using C (and most of languages) is 20!. This
is because: 21! > 18,446,774,073,709,551,615 which is 2^64 (unsigned long long).

The following snippet allows you to calculate from 21! to 99! by doing long multiplication (yes, like in elementary school). Here is an
example if you don't remember what I'm talking about:
2432902008176640000     = 20!
x 21
-------------------------
02432902008176640000    = 2432902008176640000*1
4865804016353280000     = 2432902008176640000*2 
-------------------------
51090942171709440000    = 2432902008176640000 + 4865804016353280000 = 21! 

The first parameter should be "1" and the second the factorial number we need, for example, 88.

Please note that this is only for positive integer numbers. 

This could also be achieved using integers instead of chars but a char is most of the times 4 times smaller than an integer.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* moreThan20Factorial( char factor1[],  char factor2[]);

int main(int argc, char* argv[])
{
	char *result; 
	
	result = calloc( strlen(argv[1])+1, sizeof(char) );
	strcpy( result, argv[1] );
	
	result = moreThan20Factorial(result, argv[2]);
	printf("%s! = %s\n", argv[2], result);
	
}

char* moreThan20Factorial( char factor1[],  char factor2[])
{
	const int factor1Size = strlen(factor1), factor2Size = strlen(factor2);
	
	/*The number of digits of the result is always at most the sum of the number of digits of both factors. We also need  
	to add +1 for the null terminating char (this is important).*/
	const int resultSize = factor1Size+factor2Size+1;
	
	int accomulator = 0; 
	char summand1[resultSize], summand2[resultSize]; //The two summands result of the long multiplication.
	char *result = (char*)calloc( resultSize+1, sizeof(char)); // here we'll store the result.
	
	
	unsigned int sum = 0;
	char sumChar[2], factor1Temp[]={'0','\0'}, factor2Temp[]={'0','\0'};
	
	result[resultSize-1] = summand1[resultSize-1] = summand2[resultSize-1] = '\0';
	for(int index = 0; index < resultSize-1;index++)// we use "index < resultSize-1" because of the null terminating char
		result[index] = summand1[index] = summand2[index] = '0';
	
	int f1Index; //In this pair of for loops we do a long multiplication and generate two summands. 
	for(int f2Index = factor2Size-1; f2Index >= 0; f2Index--) //we go backwards because in a long multiplication we go from right to left
	{
		f1Index = factor1Size-1; // We use two indexes because factor1Size < resultSize. 
		for(int sumIndex = resultSize-2; sumIndex>= 0; sumIndex--)
		{
			factor1Temp[0] = factor1[f1Index--];
			factor2Temp[0] = factor2[f2Index];
			
			sum = atoi(factor1Temp) * atoi(factor2Temp);
			sum+=accomulator;
			accomulator = (sum > 9) ? sum/10 : 0;
			sum = (sum > 9) ? sum%10 : sum;
			
			sprintf(sumChar,"%u", sum);
			
			if(f2Index || factor2Size < 2)
				summand1[sumIndex] = sumChar[0];
			else
				summand2[sumIndex] = sumChar[0];
		}
		accomulator = 0;
	}
	
	result[resultSize-2] = summand1[resultSize-2];//we store the last number of the summand1 in result.
	
	for(int rIndex = resultSize-2; rIndex >= 0; rIndex--)// we sum from left to right.
	{
		factor1Temp[0] = (rIndex-1) >=0 ? summand1[rIndex-1] : '0';// the first summand will get to zero before the second.
		factor2Temp[0] = summand2[rIndex];
		
		sum = atoi(factor1Temp) + atoi(factor2Temp);
		
		sum+=accomulator;
		accomulator = (sum > 9) ? sum/10 : 0;
		sum = (sum > 9) ? sum%10 : sum;
		
		sprintf(sumChar,"%u", sum);
		result[rIndex-1] = sumChar[0];
	}

	//mostof the times you'll have one spare zero in the left, so we rotate 
	while(result[0] == '0' && strlen(result) > 2)
		memmove(result, result+1, resultSize*sizeof(char)+1);
	
	unsigned int f2 = atoi(factor2);
	if( f2 <= 2)
		return result;
	else
	{
		
		char newFactor[3];
		sprintf(newFactor,"%02i", --f2);
		return moreThan20Factorial(result, newFactor);
	}
}
