/*
	==================================================
	Assignment #1 (Milestone-4):
	==================================================
	Name   : Muhammad Ahmed
	ID     : 146 908 207
	Email  : mahmed224@myseneca.ca
	Section: NCC
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#include "commonHelpers.h"

//1. Get the current 4-digit year from the system
int currentYear(void) {

	time_t currentTime = time(NULL);

	return localtime(&currentTime)->tm_year + 1900;
}

//2. Empty the standard input buffer
void clearStandardInputBuffer(void) {

	while (getchar() != '\n') {
		; // On purpose: do nothing
	}

}

//3. Ensure integer value is entered
int getInteger(void) {

	int intTest, flag = 0;
	char charTest = 'x';

	do {

		scanf("%d%c", &intTest, &charTest);

		if (charTest == '\n') {
			flag = 1;

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");

		}

	} while (!flag);

	return intTest;
}

//4. Ensures positive integer value is entered
int getPositiveInteger(void) {

	int intTest, flag = 0;
	char charTest;

	do {

		intTest = 0;
		charTest = 'x';

		scanf("%d%c", &intTest, &charTest);

		if (charTest == '\n') {

			if (intTest > 0) {
				flag = 1;

			} else {
				printf("ERROR: Value must be a positive integer greater than zero: ");

			}

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");

		}

	} while (!flag);

	return intTest;
}

//5. Ensures double value is entered
double getDouble(void) {

	double doubleTest;
	int flag = 0;
	char charTest = 'x';

	do {

		scanf("%lf%c", &doubleTest, &charTest);

		if (charTest == '\n') {
			flag = 1;

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");

		}

	} while (!flag);

	return doubleTest;
}

//6. Ensures positive double value is entered
double getPositiveDouble(void) {

	double doubleTest;
	int flag = 0;
	char charTest;

	do {

		doubleTest = 0;
		charTest = 'x';

		scanf("%lf%c", &doubleTest, &charTest);

		if (charTest == '\n') {

			if (doubleTest > 0) {
				flag = 1;

			} else {
				printf("ERROR: Value must be a positive double floating-point number: ");

			}

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (!flag);

	return doubleTest;

}

//7. Ensures integer value is entered and is in specified range
int getIntFromRange(int lowLimit, int highLimit) {

	int intRangeTest, flag = 0;
	char charTest;

	do {

		intRangeTest = 0;
		charTest = 'x';

		scanf("%d%c", &intRangeTest, &charTest);

		if (charTest == '\n') {

			if (intRangeTest >= lowLimit && intRangeTest <= highLimit) {
				flag = 1;

			} else {
				printf("ERROR: Value must be between %d and %d inclusive: ", lowLimit, highLimit);

			}

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");

		}

	} while (!flag);

	return intRangeTest;
}

//8. Ensures the entered character matches any of the characters in a C string
char getCharOption(const char validValueList[]) {

	int i, flag = 0;
	char charRangeTest;
	char charAmntTwo;

	do {

		scanf(" %c%c", &charRangeTest, &charAmntTwo);

		if (charAmntTwo == '\n') {

			for (i = 0; validValueList[i] != '\0'; i++) {

				if (charRangeTest == validValueList[i]) {
					flag = 1;
				}

			}

			if (!flag) {
				printf("ERROR: Character must be one of [%s]: ", validValueList);

			}

		} else {
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", validValueList);
			

		}

	} while (!flag);

	return charRangeTest;
}


//9. Gets string and ensures entered number of characters is within the specified range
void getCString(char* stringRecieved, int lowLimit, int highLimit) {

	int i, stringLength, flag = 0;
	char stringInput[1000];

	do {

		scanf(" %999[^\n]", stringInput);

		clearStandardInputBuffer();

		for (stringLength = 0; stringInput[stringLength] != '\0'; stringLength++) {
			//No body is on purpose
		}

		if (stringLength <= highLimit && stringLength >= lowLimit) {

			for (i = 0; i < stringLength; i++) {

				stringRecieved[i] = stringInput[i];

			}

			stringRecieved[stringLength] = '\0';

			flag = 1;

		} else if (lowLimit == highLimit) {
			printf("ERROR: String length must be exactly %d chars: ", highLimit);

		} else if (stringLength > highLimit) {
			printf("ERROR: String length must be no more than %d chars: ", highLimit);

		} else if (stringLength < lowLimit) {
			printf("ERROR: String length must be between %d and %d chars: ", lowLimit, highLimit);

		}

	} while (!flag);

}





