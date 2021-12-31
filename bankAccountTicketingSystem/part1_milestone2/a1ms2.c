// ===================================================================================
//  Assignment: 1 
//  Milestone : 2
// ===================================================================================
//  Student Name  : Muhammad Ahmed
//  Student ID    : 146908207
//  Student Email : mahmed224@myseneca.ca
//  Course Section: NCC
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "account.h"                         // *** DO NOT MODIFY THIS LINE ***
#include "commonHelpers.h"                   // *** DO NOT MODIFY THIS LINE ***

//Macros
#define AGENT_IDENTIFIER 'A'
#define CUSTOMER_IDENTIFIER 'C'
#define MIN_AGE 18
#define MAX_AGE 110

// ------------------------------------------------------------------
// Function Prototypes:

// Confirm MS1 stuff still works and grades can be applied to MS1
void commonHelpersTest(void);                   // *** DO NOT MODIFY THIS LINE ***

// Display Account details                              // *** DO NOT MODIFY THIS PROTOTYPE ***
void displayAccount(const struct Account account, const struct UserLogin login, const struct Demographic demo);


// ------------------------------------------------------------------
// Main entry point to application:

int main(void) {
	struct Account account = { 0 };            // *** DO NOT MODIFY THIS LINE ***
	struct UserLogin login = { {0} };          // *** DO NOT MODIFY THIS LINE ***
	struct Demographic demographic = { 0 };    // *** DO NOT MODIFY THIS LINE ***

	// Declare other variables you may need here:
	int currentYearVar;

	printf("Assignment 1 Milestone 2\n");                    // *** DO NOT MODIFY THIS LINE ***
	printf("=============================================\n\n"); // *** DO NOT MODIFY THIS LINE ***

	// ---------------------------------------------------------
	// Confirm MS1 deliverables - Test commonHelper functions
	// ---------------------------------------------------------
	commonHelpersTest();     // *** DO NOT MODIFY THIS LINE ***

	// ---------------------------------------------------------
	// Account Data: get user input
	// ---------------------------------------------------------
	printf("Account Data Input\n");                   // *** DO NOT MODIFY THIS LINE ***
	printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

	// Add the necessary code to get user input for each Account member:
	printf("Enter the account number: ");
	account.accountNmbr = getInteger();

	printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
	account.accountType = getCharOption("AC");

	printf("\n");

	// ---------------------------------------------------------
	// UserLogin Data: get user input
	// ---------------------------------------------------------
	printf("User Login Data Input\n");                 // *** DO NOT MODIFY THIS LINE ***
	printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

	// Add the necessary code to get user input for each UserLogin member:

	printf("Enter user login (%d chars max): ", USER_CHAR_MAX);
	getCString(login.userName, 1, USER_CHAR_MAX);

	printf("Enter the display name (%d chars max): ", DISPLAY_CHAR_MAX);
	getCString(login.displayName, 1, DISPLAY_CHAR_MAX);

	printf("Enter the password (must be %d chars in length): ", PASS_CHAR_MAX);
	getCString(login.userPass, PASS_CHAR_MAX, PASS_CHAR_MAX);

	printf("\n");

	// ---------------------------------------------------------
	// Demographic Data: get user input
	// ---------------------------------------------------------
	printf("Demographic Data Input\n");                // *** DO NOT MODIFY THIS LINE ***
	printf("----------------------------------------\n"); // *** DO NOT MODIFY THIS LINE ***

	// Add the necessary code to get user input for each Demographic member:
	// NOTE: You will need to get the CURRENT YEAR to devise the appropriate range
	//       when prompting for the birth year data.  There is a function in the 
	//       commonHelpers library that gives you this!
	currentYearVar = currentYear();

	printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
	demographic.birthYear = getIntFromRange(currentYearVar - MAX_AGE, currentYearVar - MIN_AGE);

	printf("Enter the household Income: $");
	demographic.householdIncome = getPositiveDouble();

	printf("Enter the country (%d chars max.): ", COUNTRY_CHAR_MAX);
	getCString(demographic.residenceCountry, 1, COUNTRY_CHAR_MAX);

	// ---------------------------------------------------------
	// Display all the entered data
	// ---------------------------------------------------------

	// Call function to display the Account record (see function prototype above and definition below):
	displayAccount(account, login, demographic);

	printf("\n");

	printf("\nAssignment #1 Milestone #2 completed!\n"); // *** DO NOT MODIFY THIS LINE ***

	return 0; // *** DO NOT MODIFY THIS LINE ***
}


// ------------------------------------------------------------------
// Function definitions:


// Display Account details: Add the missing code!
void displayAccount(const struct Account account, const struct UserLogin login, const struct Demographic demo) {
	
	// Give this formatting to the student
	printf("\nAcct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");

	// Display the respective data to align to the table header above:
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s", account.accountNmbr, account.accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", demo.birthYear, demo.householdIncome, demo.residenceCountry, login.displayName, login.userName, login.userPass);

}


// Confirm MS1 stuff still works so grades may be applied to MS1
// *** DO NOT MODIFY THIS FUNCTION DEFINITION ***
void commonHelpersTest(void) {
	int intValue;
	double dblValue;
	char charValue, cstringValue[7];

	printf("TEST #1: Enter the word 'error' [ENTER], then the number -100: ");
	intValue = getInteger();
	if (intValue == -100) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #2: Enter the number -100 [ENTER], then the number 200: ");
	intValue = getPositiveInteger();
	if (intValue == 200) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #3: Enter the number -4 [ENTER], then 12 [ENTER], then -3: ");
	intValue = getIntFromRange(-3, 11);
	if (intValue == -3) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #4: Enter the word 'error' then, the number -150.75: ");
	dblValue = getDouble();
	if (dblValue == -150.75) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #5: Enter the number -22.11 [ENTER], the number 225.55: ");
	dblValue = getPositiveDouble();
	if (dblValue == 225.55) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #6: Enter the word 'error' then, the number 11: ");
	intValue = getIntFromRange(-3, 11);
	if (intValue == 11) {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #7: Enter the character 'R' [ENTER], then 'p' [ENTER], then 'r': ");
	charValue = getCharOption("qwerty");
	if (charValue == 'r') {
		printf("*** PASS *** \n\n");
	} else {
		printf("### FAILED ###\n\n");
	}

	printf("TEST #8: Enter the word 'horse' [ENTER], then 'SENECA': ");
	getCString(cstringValue, 6, 6);
	printf("Your Result: %s (Answer: SENECA)\n\n", cstringValue);

	printf("TEST #9: Enter the words 'Seneca College' [ENTER], then 'IPC': ");
	getCString(cstringValue, 3, 6);
	printf("Your Result: %s (Answer: IPC)\n\n", cstringValue);

	printf("TEST #10: Enter the words 'ipc' [ENTER], then 'SCHOOL': ");
	getCString(cstringValue, 4, 6);
	printf("Your Result: %s (Answer: SCHOOL)\n\n", cstringValue);
}
