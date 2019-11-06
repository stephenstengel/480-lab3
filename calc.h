/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 * Header file for calc.c
 * 
 */
#ifndef CALC_H_LOL
#define CALC_H_LOL

#define TRUE 1
#define FALSE 0

//Operators represent themselves as a character. Numbers represented by 'n'.
//End of expression character is ';'
struct Token
{
	char dataType;
	double value; //Defined if a number. Undefined otherwise.
};

int helpCheckPrint(int argc, char** argv);

char getNextChar();
struct Token getNextToken();
void goBackOneChar();
struct Token bufferToken;
_Bool isBufferToken = FALSE;
void rollBackCharacterPointerOnly();

char bufferCharacter;
char* currentCharPointer;

double numbersAndParentheses();
double multiplyDivide();
double plusMinus();

int calculator();
char askIfContinue(char iWillContinue);

#endif
