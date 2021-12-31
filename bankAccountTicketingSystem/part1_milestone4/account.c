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

#include "account.h"
#include "commonHelpers.h"

//Function definitions:
//1. Promts user for and recieves account data
void getAccount(struct Account* account) {

	printf("Account Data: New Record\n");
	printf("----------------------------------------\n");

	printf("Enter the account number: ");
	account->accountNmbr = getPositiveInteger();

	printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
	account->accountType = getCharOption("AC");

	putchar('\n');

}

//2. Promts user for and recieves user login data
void getUserLogin(struct UserLogin* userLogin) {

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	printf("Enter user login (%d chars max): ", USER_CHAR_MAX);
	getCString(userLogin->userName, 1, USER_CHAR_MAX);

	printf("Enter the display name (%d chars max): ", DISPLAY_CHAR_MAX);
	getCString(userLogin->displayName, 1, DISPLAY_CHAR_MAX);

	printf("Enter the password (must be %d chars in length): ", PASS_CHAR_MAX);
	getCString(userLogin->userPass, PASS_CHAR_MAX, PASS_CHAR_MAX);

	putchar('\n');

}

//3. Promts user for and recieves user demographic data
void getDemographic(struct Demographic* demographic) {

	int currentYearVar;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");

	currentYearVar = currentYear();

	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	demographic->birthYear = getIntFromRange(currentYearVar - MAX_AGE, currentYearVar - MIN_AGE);

	printf("Enter the household Income: $");
	demographic->householdIncome = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", COUNTRY_CHAR_MAX);
	getCString(demographic->residenceCountry, 1, COUNTRY_CHAR_MAX);

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

	int menuSelection, flag = 0;

	do {

		printf("User Login: Williamson - Update Options\n");
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
			printf("Enter the password (must be %d chars in length): ", PASS_CHAR_MAX);
			getCString(userLogin->userPass, PASS_CHAR_MAX, PASS_CHAR_MAX);
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

	int menuSelection, flag = 0;

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
			putchar('\n');
			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}




