/*
	==================================================
	Assignment #2 (Milestone-1):
	==================================================
	Name   : Muhammad Ahmed
	ID     : 146 908 207
	Email  : mahmed224@myseneca.ca
	Section: NCC
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//Safeguard
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

//Function prototypes:
//1. Get the current 4-digit year from the system
int currentYear(void);

//2. Empty the standard input buffer
void clearStandardInputBuffer(void);

//3. Ensures integer value is entered
int getInteger(void);

//4. Ensures positive integer value is entered
int getPositiveInteger(void);

//5. Ensures double value is entered
double getDouble(void);

//6. Ensures positive double value is entered
double getPositiveDouble(void);

//7. Ensures integer value is entered and is in specified range
int getIntFromRange(int lowLimit, int highLimit);

//8. Ensures the entered character matches any of the characters in a C string
char getCharOption(const char validValueList[]);

//9. Gets string and ensures entered number of characters is within the specified range
void getCString(char* stringRecieved, int lowLimit, int highLimit);

//Safeguard
#endif // !COMMON_HELPERS_H_

