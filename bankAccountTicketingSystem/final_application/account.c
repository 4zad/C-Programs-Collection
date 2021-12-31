/*
	==================================================
	Assignment #2 (Milestone-3):
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
void getAccount(struct AccountTicketingData* database, int indexNum) {

	int i, highestAccNum = 0;

	//looks for the highest current existing account number
	for (i = 0; i < database->ACCOUNT_MAX_SIZE; i++) {

		if (highestAccNum < database->accounts[i].accountNum) {
			highestAccNum = database->accounts[i].accountNum;

		}

	}

	database->accounts[indexNum].accountNum = highestAccNum + 1; //assigns highest (account number + 1) to new account

	printf("New Account Data (Account#:%d)\n", database->accounts[indexNum].accountNum);
	printf("----------------------------------------\n");

	printf("Enter the account type (%c=Agent | %c=Customer): ", AGENT_IDENTIFIER, CUSTOMER_IDENTIFIER);
	database->accounts[indexNum].accountType = getCharOption("AC");

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

		if (digit == 2 && uppercase == 2 && lowercase == 2 && symbol == 2) { //password criteria check
			flag = 1; //criteria met and password will be kept

		} else { //password did not meet criteria and thus, error with criteria is displayed
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

		printf("Account: %d - Update Options\n", account->accountNum);
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

				getStringStats(userLogin->userPass, &digit, &uppercase, &lowercase, &symbol, NULL); //checks to see what type of characters and how many of each are contained in the password

				if (digit == 2 && uppercase == 2 && lowercase == 2 && symbol == 2) { //password criteria check
					flag = 1; //criteria met and password will be kept

				} else { //password did not meet criteria and thus, error with criteria is displayed
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

			//loops through the length of entered country string
			for (i = 0; i < strlen(demographic->residenceCountry); i++) {

				demographic->residenceCountry[i] = toupper(demographic->residenceCountry[i]); //each letter is converted to uppercase

			}

			putchar('\n');
			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//7. Writes all existing, non-empty accounts to 'accounts.txt' database/storage file
int writeAccountRecords(const struct Account* accDatabase, const int accountMaxSize) {

	int i, accRecCount = 0;

	FILE* fp = fopen("accounts.txt", "w");

	if (fp != NULL) {

		for (i = 0; i < accountMaxSize; i++) {

			accRecCount += appendAccountRecord(&accDatabase[i], fp);

		}

		//safely closing file:
		fflush(fp);
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //error to display that address of file was not received and thus, account records cannot be written

	}

	return accRecCount;
}

//8. Writes a single line of account data onto a file based on the writing mode used in the file address parameter recieved
int appendAccountRecord(const struct Account* accDatabase, FILE* fp) {

	int i, bytesPrinted = 0;

	if (fp != NULL) {

		if (accDatabase->accountNum > 0) { //ensures only accounts that have not been deleted and exist are written to file

			bytesPrinted = fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s",
				accDatabase->accountNum,
				accDatabase->accountType,
				accDatabase->userLogin.displayName,
				accDatabase->userLogin.userName,
				accDatabase->userLogin.userPass,
				accDatabase->demographic.birthYear,
				accDatabase->demographic.householdIncome,
				accDatabase->demographic.residenceCountry);

			bytesPrinted = fputc('\n', fp);

		}

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //error to display that address of file was not received and thus, account records cannot be written

	}

	return bytesPrinted > 0 ? 1 : 0;
}

//9. Calculates the number of account records that are saved in the accounts archive file "accounts_arc.txt"
int calcArchivedAccountStats(void) {

	int i, accRecCount = 0, fieldCount = 0;
	struct Account accArchive = { 0 };

	FILE* fp = fopen("accounts_arc.txt", "r"); //reading data from 'accounts_arc.txt'

	if (fp != NULL) {

		do {

			fieldCount = fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]",
				&accArchive.accountNum,
				&accArchive.accountType,
				accArchive.userLogin.displayName,
				accArchive.userLogin.userName,
				accArchive.userLogin.userPass,
				&accArchive.demographic.birthYear,
				&accArchive.demographic.householdIncome,
				accArchive.demographic.residenceCountry);

			if (fieldCount == 8) {

				while (fgetc(fp) != '\n'); //discards any remaining chararacters on the line, until and including '\n'
				accRecCount++; //increments counter which keeps count of total records read so far

			}

		} while (!feof(fp)); //determines if end of file is reached

		fflush(fp);
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //error to display that address of file was not received and thus, account records cannot be read

	}

	return accRecCount;
}

//10. Load all account records onto the system from 'accounts.txt' file
int loadAccounts(struct Account* accDatabase, const int accountMaxSize) {

	int accRecCount = 0, fieldCount = 0;

	FILE* fp = fopen("accounts.txt", "r"); //reading data from 'accounts.txt'

	if (fp != NULL) {

		do {

			fieldCount = fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]",
				&accDatabase[accRecCount].accountNum,
				&accDatabase[accRecCount].accountType,
				accDatabase[accRecCount].userLogin.displayName,
				accDatabase[accRecCount].userLogin.userName,
				accDatabase[accRecCount].userLogin.userPass,
				&accDatabase[accRecCount].demographic.birthYear,
				&accDatabase[accRecCount].demographic.householdIncome,
				accDatabase[accRecCount].demographic.residenceCountry);



			if (fieldCount == 8) {

				while (fgetc(fp) != '\n'); //discards any remaining chararacters on the line, until and including '\n'
				accRecCount++; //increments counter to be used to read values to next index and keeps count of total records read so far

			}


		} while (!feof(fp) && accRecCount < accountMaxSize); //determines if end of file is reached or max allowed entries have been reached to decide whether to exit loop or not

		//safely closing file:
		fflush(fp);
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //error to display that address of file was not received and thus, account records cannot be read

	}

	return accRecCount;
}



