/*
 * Stephen Stengel <stephen.stengel@cwu.edu> 40819903
 * 
 * Header file for calc.c
 * Might not really be needed.
 * 
 */
#ifndef CALC_H_LOL
#define CALC_H_LOL

int helpCheckPrint(int argc, char** argv);

char getNextChar(); //returns a char, advances pointer.
void putCharBack(); //just un-advance the pointer?

double numbersAndParentheses(); //what inputs for these?
double multiplyDivide();
double plusMinus();

int calculator();
char askIfContinue(char iWillContinue);

struct Token
{
	char dataType;
	double value; //if a number
};



#endif
