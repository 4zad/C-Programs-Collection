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
#include <string.h>
#include <ctype.h>

#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

//Function definitions:
//1. Promts user for and recieves account data
void getAccount(struct AccountTicketingData* database, int indexNmbr) {

	int i, highestAccNmbr = 0;

	for (i = 0; i < database->ACCOUNT_MAX_SIZE; i++) {

		if (highestAccNmbr < database->accounts[i].accountNmbr) {
			highestAccNmbr = database->accounts[i].accountNmbr;

		}

	}

	database->accounts[indexNmbr].accountNmbr = highestAccNmbr + 1;

	printf("New Account Data: Account#:%d\n", database->accounts[indexNmbr].accountNmbr);
	printf("----------------------------------------\n");

	printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
	database->accounts[indexNmbr].accountType = getCharOption("AC");

	putchar('\n');

}

//2. Promts user for and recieves user login data
void getUserLogin(struct UserLogin* userLogin) {

	int digit, uppercase, lowercase, symbol, whitespace, flag = 0;

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	do {

		printf("Enter user login (%d chars max): ", USER_CHAR_MAX);
		getCString(userLogin->userName, 1, USER_CHAR_MAX);

		getStringStats(userLogin->userName, NULL, NULL, NULL, NULL, &whitespace);

		if (whitespace > 0) {
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");

		} else {
			flag = 1;

		}

	} while (!flag);

	flag = 0;

	printf("Enter the display name (%d chars max): ", DISPLAY_CHAR_MAX);
	getCString(userLogin->displayName, 1, DISPLAY_CHAR_MAX);

	do {

		printf("Enter the password (must be %d chars in length): ", PASS_CHAR_MAX);
		getCString(userLogin->userPass, PASS_CHAR_MAX, PASS_CHAR_MAX);

		getStringStats(userLogin->userPass, &digit, &uppercase, &lowercase, &symbol, NULL);

		if (digit == 2 && uppercase == 2 && lowercase == 2 && symbol == 2) {
			flag = 1;

		} else {
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");

		}

	} while (!flag);

	putchar('\n');

}

//3. Promts user for and recieves user demographic data
void getDemographic(struct Demographic* demographic) {

	int i, currentYearVar;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");

	currentYearVar = currentYear();

	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	demographic->birthYear = getIntFromRange(currentYearVar - MAX_AGE, currentYearVar - MIN_AGE);

	printf("Enter the household Income: $");
	demographic->householdIncome = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", COUNTRY_CHAR_MAX);
	getCString(demographic->residenceCountry, 1, COUNTRY_CHAR_MAX);

	for (i = 0; i < strlen(demographic->residenceCountry); i++) {

		demographic->residenceCountry[i] = toupper(demographic->residenceCountry[i]);

	}

	putchar('\n');

}

//4. Displays working menu to update all information
void updateAccount(struct Account* account) {

	int menuSelection, flag = 0;

	do {

		printf("Account: %d - Update Options\n", account->accountNmbr);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 3);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
			account->accountType = getCharOption("AC");
			putchar('\n');
			break;

		case 2:
			updateUserLogin(&account->userLogin);
			break;

		case 3:
			updateDemographic(&account->demographic);
			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//5. Displays working menu to update user login information
void updateUserLogin(struct UserLogin* userLogin) {

	int menuSelection, digit, uppercase, lowercase, symbol, flag = 0;

	do {

		printf("User Login: %s - Update Options\n", userLogin->userName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", userLogin->displayName);
		printf("2) Password\n");
		printf("0) Done\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 2);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			printf("Enter the display name (%d chars max): ", DISPLAY_CHAR_MAX);
			getCString(userLogin->displayName, 1, DISPLAY_CHAR_MAX);
			putchar('\n');
			break;

		case 2:
			do {

				printf("Enter the password (must be %d chars in length): ", PASS_CHAR_MAX);
				getCString(userLogin->userPass, PASS_CHAR_MAX, PASS_CHAR_MAX);

				getStringStats(userLogin->userPass, &digit, &uppercase, &lowercase, &symbol, NULL);

				if (digit == 2 && uppercase == 2 && lowercase == 2 && symbol == 2) {
					flag = 1;

				} else {
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*\n");

				}

			} while (!flag);

			flag = 0;

			putchar('\n');
			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//6. Displays working menu to update demographic information
void updateDemographic(struct Demographic* demographic) {

	int i, menuSelection, flag = 0;

	do {

		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demographic->householdIncome);
		printf("2) Country (current value: %s)\n", demographic->residenceCountry);
		printf("0) Done\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 2);
		printf("\n");

		switch (menuSelection) {

		case 1:
			printf("Enter the household Income: $");
			demographic->householdIncome = getPositiveDouble();
			putchar('\n');
			break;

		case 2:
			printf("Enter the country (%d chars max.): ", COUNTRY_CHAR_MAX);
			getCString(demographic->residenceCountry, 1, COUNTRY_CHAR_MAX);

			for (i = 0; i < strlen(demographic->residenceCountry); i++) {

				demographic->residenceCountry[i] = toupper(demographic->residenceCountry[i]);

			}

			putchar('\n');
			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//7. Gets number of digits, uppercase, lowercase, symbols, and whitespace in a string
void getStringStats(const char string[], int* digitPointer, int* uppercasePointer, int* lowercasePointer, int* symbolPointer, int* whitespacePointer) {

	int i, digit, uppercase, lowercase, symbol, whitespace;

	for (i = 0, digit = 0, uppercase = 0, lowercase = 0, symbol = 0, whitespace = 0; i < strlen(string); i++) {

		if (isdigit(string[i]) > 0) {
			digit++;

		} else if (isupper(string[i]) > 0) {
			uppercase++;

		} else if (islower(string[i]) > 0) {
			lowercase++;

		} else if (isspace(string[i]) > 0) {
			whitespace = 1;

		} else {
			symbol++;

		}

	}

	if (digitPointer != NULL)
		*digitPointer = digit;

	if (uppercasePointer != NULL)
		*uppercasePointer = uppercase;

	if (lowercasePointer != NULL)
		*lowercasePointer = lowercase;

	if (symbolPointer != NULL)
		*symbolPointer = symbol;

	if (whitespacePointer != NULL)
		*whitespacePointer = whitespace;

}




