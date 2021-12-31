/*
	==================================================
	Assignment #1 (Milestone-3):
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
	account->accountNmbr = getInteger();

	printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
	account->accountType = getCharOption("AC");

	printf("\n");

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

	printf("\n");

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

	printf("\n");

}
