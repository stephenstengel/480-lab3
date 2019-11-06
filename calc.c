/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for using exit()

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
			
			charptr = workingArray;
			printf("This is the value of charptr: %c\n", *charptr);////
			printf("This is the value of charptr+1: %c\n", *(charptr+1)  );////
			
			double answer = plusMinus();
			printf("= %f\n", answer);
			
			
			free(workingArray); //! Don't forget this, lol
		}
		
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


//expression in the book
double plusMinus()
{
	//~ double leftVal = multiplyDivide(); //may need to pass values or make a global var.
	
	//get a token. Will need to have pointer to current char in workArray
	//~ Token myToken = getToken();
	
	
	return 1.1;
}


double multiplyDivide()
{
	return 1.1;
}




