/*This program takes as arguments: a string of unique characters and a positive integer which represents the size of the group. Then it displays all the posible combinations (no repeated). Example: 

./combinations abcde 3
output:
abc
abd
abe
acd
ace
ade
bcd
bce
bde
cde

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int noArguments(int argc, char * argv[], char* version, char* author);
void combinations(char inputString[], const int groupSize);

int main(int argc, char * argv[])
{	
	if(argc < 3)
	{
		printf("Thre could be some data missing in: %s\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	const int tokenSize = atoi(argv[2]);
	combinations(argv[1], tokenSize);
	
	
	return EXIT_SUCCESS;
}

void combinations(char inputString[], const int GROUP_SIZE)
{
	const int MAX_LENGTH = 95, SKIP_LAST_CHAR = 2;
	unsigned int range, nextTokenBeginAt, index, inputSize;
	char token[GROUP_SIZE+1], newPosition[MAX_LENGTH], *position;
	
	range = nextTokenBeginAt = GROUP_SIZE-SKIP_LAST_CHAR; 
	index = GROUP_SIZE-1; 
	inputSize = strlen(inputString);
	
	strncpy(token, inputString, GROUP_SIZE);
	token[GROUP_SIZE] = '\0';
	/*When the token at it's first position reaches the last posible character of the input string the while loop will end, 
	for example: ABCDEFGH, token[0] == 'E' for a token size of 4*/
	while(token[0] != inputString[(inputSize-1) - (GROUP_SIZE-1)] )
	{
		printf("%s\n", token);
		index++; // you'll move through the next chars until you reach the end of the string. ABCD -> ABCE -> ABCF -> ABCG...
		if(index == inputSize)// you've reached the end of the string for any of the groups. ABCH or BFGH
		{
			while(inputSize-range-1 == GROUP_SIZE-nextTokenBeginAt-1) // to go from AFGH to BCDE
			{//example: AFGH will have 4 iterations till we have nextTokenBeginAt == 0, and we'll replace A in the next lines of code
				//
				position = strchr(inputString, token[nextTokenBeginAt-1]);
				sprintf(newPosition, "%ld", position-inputString);
				range = atoi(newPosition);
				//
				nextTokenBeginAt--;// this will decrease until we get the next position to be replaced.
				
			}
			
			range++;// range represents the range of chars after the ones in the token to replace the last char. ABCD, range {EFGH}
			index = range + (GROUP_SIZE -1 -nextTokenBeginAt);
			
			int step = 0;/*this loop creates a brand new token using the the new value for range, ABCD becomes ACDE
			but when -nextTokenBeginAt- is 0 that means we've all the combinations with one char and we'll move to the next one.
			for example: AFGH becomes BCDE*/
			for(int a = nextTokenBeginAt; a<GROUP_SIZE; a++)
				token[a] = inputString[range+step++];
			nextTokenBeginAt = GROUP_SIZE-SKIP_LAST_CHAR;// the one before the last char of token
			
			//
			position = strchr(inputString, token[nextTokenBeginAt]);
			sprintf(newPosition, "%ld", position-inputString );
			range = atoi(newPosition); // we get the new value of range with the position
			//
		}
		token[GROUP_SIZE-1] = inputString[index]; //The last char of token will be replaced for a char that is not in the group.
	}
	printf("%s\n", token);
	
}


