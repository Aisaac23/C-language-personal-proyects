#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int noArguments(int argc, char * argv[], char* version, char* author);
void combinations(char inputString[], const int groupSize);

int main(int argc, char * argv[])
{	
	//This program takes as arguments: a string of unique characters and a positive integer which represents the size of the group.
	noArguments(argc, argv, "1.0", "Aisaac23");
	const int tokenSize = atoi(argv[2]);
	combinations(argv[1], tokenSize);
	
	
	return EXIT_SUCCESS;
}

void combinations(char inputString[], const int groupSize)
{
	int range = groupSize-2, nextTokenBeginAt = groupSize-2, index = groupSize-1, inputSize = strlen(inputString);
	char token[groupSize+1], newPosition[2];
	char *position;
	
	
	strncpy(token, inputString, groupSize);
	token[groupSize] = '\0';
	/*When the token at it's first position reaches the last posible character of the input string the while loop will end, 
	for example: ABCDEFGH, token[0] == 'E' for a token size of 4*/
	while(token[0] != inputString[(inputSize-1) - (groupSize-1)] )
	{
		printf("%s\n", token);
		index++; // you'll move through the next chars until you reach the end of the string.
		if(index == inputSize)// you've reached the end of the string
		{
			while(inputSize-range-1 == groupSize-nextTokenBeginAt-1) /* When range reaches the last (groupSize-nextTokenBeginAt-1) chars we'll look for the char that's next to be replaced...*/
			{//example: AIJKLM will have 4 iterations till we have nextTokenBeginAt == 0, and we'll replace A in the next lines of code
				//
				position = strchr(inputString, token[nextTokenBeginAt-1]);
				sprintf(newPosition, "%ld", position-inputString);
				range = atoi(newPosition);
				//
				nextTokenBeginAt--;// this will decrease until we get the next position to be replaced.
				
			}
			
			range++;// range represents the range of chars after the ones in the token to replace the last char.
			//-range- will move forward each time we've reached the last char of the string with -index-.
			index = range + (groupSize -1 -nextTokenBeginAt);
			
			int step = 0;/*this loop creates a brand new token using the the new value for range, ABCD becomes ACDE
			but when -nextTokenBeginAt- is 0 that means we've all the combinations with one char and we'll move to the next one.
			for example: AEFG becomes BCDE*/
			for(int a = nextTokenBeginAt; a<groupSize; a++)// a could begin from groupSize-2 to 0
				token[a] = inputString[range+step++];
			nextTokenBeginAt = groupSize-2;// the one before the last char of token
			
			//
			position = strchr(inputString, token[nextTokenBeginAt]);
			sprintf(newPosition, "%ld", position-inputString );
			range = atoi(newPosition); // we get the new value of range with the position that, the char at groupSize-2 in token, has in inputString.
			//
		}
		token[groupSize-1] = inputString[index]; //2) the last char of token will be replaced for the next one in the input string.
	}
	printf("%s\n", token);
	
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
