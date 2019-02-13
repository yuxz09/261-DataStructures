/**************************************************

CS261 YuxiZhang

Jan 25th, 2019
**************************************************/

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/

char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
	{
		return '\0';	
	}
	else 
	{
		return c;
	}
}


/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	
	post:	
*/
int isBalanced(char* s)
{
	//if input is null, return isbalanced
	if (s == NULL)
	{
		return 1;
	}
	/* FIXME: You will write this function */
	//declare a dynamic array
	DynArr *dynStack = newDynArr(5);
	//initialize a stack
//	initDynArr(dynStack, 5);
	//the first char, s[i]	
	char c = nextChar(s);
	//read one by one, if encounter opening, store corresponding closing parenthesis
	while(c != '\0')
	{
		/*
		//stack is empty
		if (isEmptyDynArr(dynStack) == 1)
		{
			printf("error");
			//end
			return 0;			
		}
		*/
		//stack not empty

			//if encounter opening one
			if (c== '(') 
			{
				pushDynArr(dynStack, ')');
				c = nextChar(s);
			}
			else if (c == '{')
			{
				pushDynArr(dynStack, '}');
				c = nextChar(s);				
			}
			else if (c == '[')
			{
				pushDynArr(dynStack, ']');
				c = nextChar(s);				
			}
			//when encounter closing, pop closing one
			else if ((c == ']' && topDynArr(dynStack) == ']') || (c == '}' && topDynArr(dynStack) == '}') || (c == ')' && topDynArr(dynStack) == ')')) 
			{
				popDynArr(dynStack);
				c = nextChar(s);
			}
			//if not corresponding
			else if ((c == ']' && topDynArr(dynStack) != ']') || (c == '}' && topDynArr(dynStack) != '}') || (c == ')' && topDynArr(dynStack) != ')'))
			{
				printf("error\n");
				//end
				return 0;
			}
			else
			{
				c = nextChar(s);
			}	
	}
	//reach string end && stack is empty now
	if (c == '\0' && isEmptyDynArr(dynStack) == 1)
	{
		//balanced
		return 1;
	}	
	return 0;
}
//argc is the number of command line arguments and argv is array of strings representing command line arguments
int main(int argc, char* argv[])
{
	
	char* s=argv[1];
	int res;
	scanf("%s", s);

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);
	
	return 0;
}
