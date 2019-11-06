/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 * Header file for calc.c
 * Might not really be needed.
 * 
 */
#ifndef CALC_H_LOL
#define CALC_H_LOL

#define TRUE 1
#define FALSE 0

struct Token
{
	char dataType;
	double value; //if a number
};

int helpCheckPrint(int argc, char** argv);

char getNextChar(); //returns a char, advances pointer.
struct Token getNextToken();
void goBackOneChar();
//void putCharBack(); //just un-advance the pointer?
struct Token bufferToken;
_Bool isBufferToken = FALSE;

char bufferCharacter; //nasty global var
char* currentCharPointer; //current character pointer


double numbersAndParentheses(); //what inputs for these?
double multiplyDivide(); //term in book
double plusMinus(char* workingArray); //expression in book

int calculator();
char askIfContinue(char iWillContinue);






#endif
