/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for using exit(), atof()
#include <ctype.h> //for isdigit()
#include <math.h> //for pow()

#include "calc.h"


//Things to remember
//	Munch beginning spaces and tabs. pg 78. while loop getch;
//	https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
//		This showed me that scanf can dynamically allocate memory now!
//		!!!!!!!!!!Be sure to free it!!!!!!!!!!!!!
//	Need to erase all whitespace characters in the input, before, during, and after the expression

//Use pointer to keep track of which character to be currently considering.
//		This way you son't need to store or manipulate a buffer. Just move a
//		pointer back over the string
//Or I can use the ungetch() method from the book. That will more closely
//	follow the c++ version.


int main(int argc, char **argv)
{
	helpCheckPrint(argc, argv);
	printf("Yeah, heres my calculator!\n");

	int calcFlag = calculator();

	printf("The status code of calculate was: %d: \n", calcFlag);
	
	struct Token myToken;
	myToken.dataType = 'n';
	myToken.value = 200.1;
	printf( "Value of myToken.dataType: %c  Value of myToken.value: %f\n",
			myToken.dataType,
			myToken.value );
		

	
	return 0;
}


//Checks if a help message is needed and prints it if so.
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
		printf("\nExample:\n");
		printf("Entering:\n    2+3*(-4^2)\n");
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


int calculator()
{
	char iWillContinue = 'y';
	while ( iWillContinue == 'y' )
	{
		printf("Hi!\n");
		
		char* workingArray = NULL; //for holding the input string.
		
		printf("Enter a string!:\n > ");
		//~ scanf("%m[^\n]s", &workingArray); 	//The m specifies that scanf will automatically allocate memory
											//~ //The [^\n] makes it keep going until a newline is entered.
											//~ //The m makes a call to malloc, so workingArray is local
											
		scanf("%ms", &workingArray); //this version cannot handle whitespace!
		if ( workingArray == NULL)
		{
			printf("THE ARRAY IS STILL NULL FOR SOME REASON!\n");
			exit(1);
		}
		else
		{
			printf("This is the value of workingArray: %s\n", workingArray);////
			//Perform calculation!
			
			currentCharPointer = workingArray;
			printf("This is the value of charptr: %c\n", *currentCharPointer);////
			printf("This is the value of charptr+1: %c\n", *(currentCharPointer+1)  );////
			
			double answer = plusMinus(workingArray);///////////////////////////////////////////////////PLUSMINUS
			printf("= %f\n", answer);
			
			printf("freeing the workingArray memory.\n");
			free(workingArray); //! Don't forget this, lol
		}
		
		isBufferToken = FALSE;
		
		iWillContinue = askIfContinue(iWillContinue);
		
		printf("\n");
	}
										
	return 0;
}

char askIfContinue(char myChar)
{
	printf("Enter y to go again! Press any other letter to exit.");
	int c;
	while ( (c = getchar()) != '\n'){}; //munch characters.
	
	system("stty raw"); //switches to get single character mode
	myChar = getchar();
	system("stty cooked"); //Switches back to get line mode.
	
	return myChar;
}


//expression in the book  /////////////////////////////////////////////////working here.
double plusMinus()
{
	printf("Calling plusminus\n");
	double leftVal = multiplyDivide(); //may need to pass values or make a global var.
	
	//get a token. Will need to have pointer to current char in workArray
	struct Token myToken = getNextToken();
	printf("Value of the returned token:\n");
	printf("dataType: %c\nValue: %f\n", myToken.dataType, myToken.value);
	
	//~ printf("Value returned from getNextChar: %c\n", getNextChar().);
	
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
	
	
	//~ return ;
}


double multiplyDivide()
{
	printf("Calling multiplyDivide\n");
	double leftVal = numbersAndParentheses(); //may need to pass values or make a global var.
	printf("Back in multiplyDivide\n");
	
	printf("*currentCharPointer: %c\n", *currentCharPointer);
	//~ if ( *currentCharPointer == ';' )
	//~ {
		//~ return leftVal;
	//~ }
	
	//get a token. Will need to have pointer to current char in workArray
	struct Token myToken = getNextToken();
	printf("Value of the returned token:\n");
	printf("dataType: %c\nValue: %f\n", myToken.dataType, myToken.value);
	
	//~ printf("Value returned from getNextChar: %c\n", getNextChar().);
	
	while ( TRUE )
	{
		switch( myToken.dataType )
		{
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
					exit(3);
				}
				leftVal /= tempDouble;
				myToken = getNextToken();
				break;
			}
			case '^':
				leftVal = pow(leftVal, numbersAndParentheses() );
				myToken = getNextToken();
				break;
			default:
				goBackOneChar(myToken);
				return leftVal;
		}
	}
	
	
	
	
	return 1.2222;
}




double numbersAndParentheses()
{
	printf("Calling numbersandparentheses\n");

	struct Token myToken = getNextToken();
	printf("Back in numbersandparentheses\n");
	
	
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
				exit(4);
			}
			return tempDouble;
		}
		case 'n': //n is the character I'm using to represent number tokens
			printf("Returning from numbersandparentheses this value: %f\n", myToken.value);
			return myToken.value;
		case '-':
			return -numbersAndParentheses(); //handling negatives.
		case '+':
			return numbersAndParentheses();
		default:
			printf("ERROR! Was expecting a '(' or a number but it was"
					" something else!\n");
			exit(5);
	}
}


//Returns the next char to consider. Advances the currentCharPointer by 1.
struct Token getNextToken()
{
	printf("Calling getNextToken\n");

	//if there is a buffer Token, draw from it instead.
	
	printf("isBufferToken: %d\n", isBufferToken);
	printf("bufferToken.dataType: %c\n", bufferToken.dataType);
	printf("bufferToken.value: %f\n", bufferToken.value);
	if ( isBufferToken )
	{
		printf("There is a buffer token. Returning it.\n");
		
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
			//~ goBackOneChar(); //Here, I need to reverse the digit in consideration by 1
			rollBackCharacterPointerOnly();
			double valTemp;
			
			//get the number including decimal as a string
			int currentStringSize = 100;
			char* tempString = (char*)malloc(currentStringSize + 1);
			char tmpC;
			while ( isdigit( tmpC = getNextChar() ) || tmpC == '.' )
			{
				printf("While called!\n");
				if( strlen(tempString) + 10 > currentStringSize )
				{
					printf("realloc called lol\n");
					tempString = (char *)realloc(tempString, currentStringSize*2 + 2);
				}
				
				//~ strcat(tempString, (char)tmpC );
				int tmpLen = strlen(tempString);
				printf("tmpLen: %d\n", tmpLen);//////////////////strLen is zero if input is "1;"
				tempString[ tmpLen ] = tmpC;
				tempString[ tmpLen + 1] = '\0';
				
				printf("tempString length: %d\n", (int)strlen(tempString) );
				printf("Contents of tempString: %s\n", tempString);
				
			}
			printf("currentCharPointer just after while: %c\n", *currentCharPointer);
			
			//~ goBackOneChar();//not sure if need go back just char or also token.
			//~ rollBackCharacterPointerOnly();
			printf("currentCharPointer just after goBack: %c\n", *currentCharPointer);
			
			
			//convert that string to a double!
			valTemp = atof( tempString );
			printf("value of valTemp: %f\n", valTemp);
			
			struct Token retToken;
			retToken.dataType = 'n'; //Using 'n' for number!!!!!!!!
			retToken.value = valTemp;
			
			printf("retToken.dataType: %c\n", retToken.dataType);
			printf("retToken.value: %f\n", retToken.value);
			
			printf("currentCharPointer: %c\n", *currentCharPointer);
			
			free(tempString); ////!!!!
			
			return retToken;
		}
		default:
			printf("YOU'VE KILLED ME! AHHHHHHHHhhhhhh...\n"); //hope this never comes up! (spoiler: it did)
			printf("There was a bad token in the getNextToken function!\n");
			printf("Namely: %c\n", c);
			exit(2);
	}
}


char getNextChar()
{
	char* tmp = currentCharPointer;
	
	printf("character that getNextChar is returning: %c\n", *tmp);
	
	currentCharPointer++;
	
	return *tmp;
}


//need to add ability to set buffer equal to true and set buffer!
void goBackOneChar(struct Token tokenToPutBack)
{
	printf("Calling goBackOneChar\n");
	
	if ( isBufferToken )
	{
		printf("ERROR! Token already in the buffer!\n");
		exit(6);
	}
	bufferToken = tokenToPutBack;
	isBufferToken = TRUE;
	
	
	printf("This is the current character: %c\n", *currentCharPointer);
	
	printf("going back one char!\n");
	//~ currentCharPointer--;
	rollBackCharacterPointerOnly();
	
	printf("This is now the current character: %c\n", *currentCharPointer);
}


void rollBackCharacterPointerOnly()
{
	printf("Calling rollBackCharacterPointerOnly\n");
	currentCharPointer--;
}

