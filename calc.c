/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 * Rudimentary Calculator.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for using exit(), atof()
#include <ctype.h> //for isdigit()
#include <math.h> //for pow()

#include "calc.h"

//Main function!
int main(int argc, char **argv)
{
	helpCheckPrint(argc, argv);
	printf("\nHello, this is my calculator!\n\n");

	calculator();
	
	printf("\nGoodbye!\n\n");

	return 0;
}


//Checks the command line flags for a help request. Prints one if needed.
int helpCheckPrint(int argc, char** argv)
{
	if (argc > 1 && (!strcmp(argv[1], "help")
					|| !strcmp(argv[1], "-help")
					|| !strcmp(argv[1], "--help")
					|| !strcmp(argv[1], "-h") ) )
	{
		printf("\nThis is my calculator.\n");
		printf("To run it, type ./calc\n");
		printf("You may then enter an arithmatic expression consisting\n"
				"of real numbers, and the operators: +, -, *, /, and ^.\n"
				"You may also use parentheses ().\n");
		printf("THE EXPRESSION MUST END WITH A SEMICOLON! ;\n");
		printf("\nExample:\n");
		printf("Entering:\n    2+3*(-4^2);\n");
		printf("after the prompt and pressing enter will cause the "
				"calculator to output:\n");
		printf("    = 50");
		printf("\n\nStephen Stengel "
				"<stephen.stengel@cwu.edu> "
				"40819903\n");
		
		exit(0);
	}
	
	return 0;
}


//Calls the calculator logic.
int calculator()
{
	char iWillContinue = 'y';
	while ( iWillContinue == 'y' )
	{
		printf("Hi!\n");
		
		char* workingArray = NULL; //for holding the input string.
		
		printf("Enter an arithmetic string to calculate!:\n > ");
											
		scanf("%ms", &workingArray); //The m specifies that scanf will 
		if ( workingArray == NULL)   //automatically allocate memory with
		{                            //with malloc
			printf("THE ARRAY IS STILL NULL FOR SOME REASON! LOL\n");
			exit(1);
		}
		else
		{
			//Perform calculation!
			
			currentCharPointer = workingArray;
			
			double answer = plusMinus(workingArray);
			printf("= %f\n", answer);
			
			free(workingArray); //! Don't forget this, lol
		}
		
		isBufferToken = FALSE;
		iWillContinue = askIfContinue(iWillContinue);
		printf("\n");
	}
										
	return 0;
}


//Asks the user if they want to do another calculation. Single character input.
char askIfContinue(char myChar)
{
	printf("Enter y to go again! Press any other letter to exit.");
	int c;
	while ( (c = getchar()) != '\n'){}; //munch characters in stdin.
	
	system("stty raw"); //switches to get single character mode
	myChar = getchar();
	system("stty cooked"); //Switches back to get line mode.
	
	return myChar;
}


//The basic function of the calculator. Adds the results of the multiplication
//and division function, multiplyDivide().
double plusMinus()
{
	double leftVal = multiplyDivide();
	
	struct Token myToken = getNextToken();
	
	while ( TRUE )
	{
		switch( myToken.dataType )
		{
			case '+':
				leftVal += multiplyDivide();
				myToken = getNextToken();
				break;
			case '-':
				leftVal -= multiplyDivide();
				myToken = getNextToken();
				break;
			default:
				goBackOneChar(myToken);
				return leftVal;
		}
	}
}


//Performs multiplication, exponentiation, and division on the results of the
//numbersAndParentheses() function.
double multiplyDivide()
{
	double leftVal = numbersAndParentheses();
	
	struct Token myToken = getNextToken();
	
	while ( TRUE )
	{
		switch( myToken.dataType )
		{
			case '^':
				leftVal = pow(leftVal, numbersAndParentheses() );
				myToken = getNextToken();
				break;
			case '*':
				leftVal *= numbersAndParentheses();
				myToken = getNextToken();
				break;
			case '/':
			{
				double tempDouble = numbersAndParentheses();
				if (tempDouble == 0)
				{
					printf("DIVIDE BY ZERO ERROR LOL!\n");
					exit(2);
				}
				leftVal /= tempDouble;
				myToken = getNextToken();
				break;
			}
			default:
				goBackOneChar(myToken);
				return leftVal;
		}
	}
}


//Finds numbers and returns them. Finds Parentheses, +, -, and returns them.
double numbersAndParentheses()
{
	struct Token myToken = getNextToken();
	
	switch(myToken.dataType)
	{
		case '(':
		{
			double tempDouble = plusMinus();
			myToken = getNextToken();
			if ( myToken.dataType != ')' )
			{
				printf("ERROR! Expected a ending parentheses ')' character"
						" but it wasn't there!\n");
				exit(3);
			}
			
			return tempDouble;
		}
		case 'n':      //n is the character I'm using to represent number tokens
			return myToken.value;
			
		case '-':
			return -numbersAndParentheses(); //handling negatives.
			
		case '+':
			return numbersAndParentheses();  //Handling explicit positives.
			
		default:
			printf("ERROR! Was expecting a '(' or a number but it was"
					" something else!\n");
			exit(4);
	}
}


//Returns the next char to consider. Advances the currentCharPointer by 1.
struct Token getNextToken()
{
	//if there is a buffer Token, draw from it instead.
	if ( isBufferToken )
	{
		isBufferToken = FALSE;
		return bufferToken;
	}
	
	char c;
	c = getNextChar();
	
	switch(c)
	{
		case ';':
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		{
			struct Token aToken;
			aToken.dataType = c;
							
			return aToken; //make a token out of this character.
		}
		case '.':  
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			rollBackCharacterPointerOnly();
			double valTemp;
			
			//get the number including decimal as a string
			//! ! ! This is a very messy hack. Will make pretty later. ! ! !//
			int currentStringSize = 100;
			char* tempString = (char*)malloc(currentStringSize + 1);
			char tmpC;
			while ( isdigit( tmpC = getNextChar() ) || tmpC == '.' )
			{
				if( strlen(tempString) + 10 > currentStringSize )
				{
					tempString = (char *)realloc(tempString, currentStringSize*2 + 2);
				}
				
				int tmpLen = strlen(tempString);
				tempString[ tmpLen ] = tmpC;     //Appends a char to the string.
				tempString[ tmpLen + 1] = '\0';
			}
			rollBackCharacterPointerOnly();
			
			//convert that string to a double!
			valTemp = atof( tempString );
			
			struct Token retToken;
			retToken.dataType = 'n'; //Using 'n' for number!!!!!!!!
			retToken.value = valTemp;
			
			free(tempString); ////!!!!
			
			return retToken;
		}
		default:
			//hope this next bit never comes up! (spoiler: it did)
			printf("YOU'VE KILLED ME! AHHHHHHHHhhhhhh...\n"); 
			printf("There was a bad token in the getNextToken function!\n");
			printf("Namely: %c\n", c);
			exit(5);
	}
}


//Returns the next character for consideration in the input string. Also
//increments the currentCharPointer.
char getNextChar()
{
	char* tmp = currentCharPointer;
	currentCharPointer++;
	
	return *tmp;
}


//Decrements the character pointer. Also, places the most recently created token
//into the temporary buffer and sets isBufferToken to TRUE.
void goBackOneChar(struct Token tokenToPutBack)
{
	if ( isBufferToken )
	{
		printf("ERROR! Token already in the buffer!\n");
		exit(6);
	}
	
	bufferToken = tokenToPutBack;
	isBufferToken = TRUE;
	
	rollBackCharacterPointerOnly();
}


//Rolls back the character pointer to the previously considered place.
void rollBackCharacterPointerOnly()
{
	currentCharPointer--;
}
