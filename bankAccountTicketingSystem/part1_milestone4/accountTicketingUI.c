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

#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"

//Function definitions:
//1. Displays header for summary of account details
void displayAccountSummaryHeader(void) {

	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");

}

//2. Displays header for detailed display of account information
void displayAccountDetailHeader(void) {

	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");

}

//3. Displays data summary of account details
void displayAccountSummaryRecord(const struct Account* account) {

	printf("%05d %-9s %5d\n", account->accountNmbr, account->accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", account->demographic.birthYear);

}

//4. Displays detailed display of account information
void displayAccountDetailRecord(const struct Account* account) {

	char hiddenUserPass[9];
	int i;

	for (i = 0; i < PASS_CHAR_MAX; i++) {

		if (i % 2 == 0) {

			hiddenUserPass[i] = account->userLogin.userPass[i];

		} else {

			hiddenUserPass[i] = '*';

		}

	}

	hiddenUserPass[8] = '\0';

	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account->accountNmbr, account->accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", account->demographic.birthYear, account->demographic.householdIncome, account->demographic.residenceCountry, account->userLogin.displayName, account->userLogin.userName, hiddenUserPass);

}

//6. Displays a working login menu
int menuLogin(const struct Account accDatabase[], int maxElmnt) {

	int menuSelection, flag = 0, indexMatch = -1;
	char confirmSelection;

	do {

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");

		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 1);

		putchar('\n');

		switch (menuSelection) {

			case 1:
			indexMatch = findAccountIndexbyAccNum(0, accDatabase, maxElmnt, 1);

			if (indexMatch == -1) {
				printf("\nERROR: Access Denied.\n\n");
				pauseExecution();

			} else {
				putchar('\n');
				flag = 1;

			}

			break;

			case 0:
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			confirmSelection = getCharOption("yYnN");

			if (confirmSelection == 'y' || confirmSelection == 'Y') {
				flag = 1;
				indexMatch = -1;

			}

			putchar('\n');
			break;

		}

	} while (!flag);

	return indexMatch;
}

//7. Displays working menu for agent's accounts
void menuAgent(struct Account accDatabase[], int maxElmnt, const struct Account* account) {

	int menuSelection, indexNmbr, flag = 0;
	char confirmSelection;

	do {

		printf("AGENT: %s (%d)\n", account->userLogin.displayName, account->accountNmbr);

		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");

		printf("1) Add a new account\n");
		printf("2) Modify an existing account\n");
		printf("3) Remove an account\n");
		printf("4) List Accounts: summary view\n");
		printf("5) List Accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 5);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			indexNmbr = findAccountIndexbyAccNum(0, accDatabase, maxElmnt, 0);

			if (indexNmbr == -1) {
				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");

			} else {
				getAccount(&accDatabase[indexNmbr]);
				getUserLogin(&accDatabase[indexNmbr].userLogin);
				getDemographic(&accDatabase[indexNmbr].demographic);

				printf("*** New account added! ***\n\n");

				pauseExecution();

			}

			break;

		case 2:
			indexNmbr = findAccountIndexbyAccNum(account->accountNmbr, accDatabase, maxElmnt, 1);
			putchar('\n');

			updateAccount(&accDatabase[indexNmbr]);
			break;

		case 3:
			indexNmbr = findAccountIndexbyAccNum(account->accountNmbr, accDatabase, maxElmnt, 1);

			if (accDatabase[indexNmbr].accountNmbr == account->accountNmbr) {
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();

			} else if (indexNmbr == -1) {
				printf("\nERROR: Access Denied.\n\n");
				pauseExecution();

			} else {
				displayAccountDetailHeader();
				displayAccountDetailRecord(&accDatabase[indexNmbr]);

				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");

				switch (confirmSelection) {
				case 'Y':
					accDatabase[indexNmbr].accountNmbr = 0;

					printf("\n*** Account Removed! ***\n\n");
					pauseExecution();
					break;

				default:
					printf("\n*** No changes made! ***\n\n");
					pauseExecution();
					break;

				}

			}

			break;

		case 4:
			displayAllAccountSummaryRecords(accDatabase, maxElmnt);
			break;

		case 5:
			displayAllAccountDetailRecords(accDatabase, maxElmnt);
			break;

		case 0:
			printf("### LOGGED OUT ###\n\n");
			flag = 1;
			break;

		}

	} while (!flag);

}

//8. To search and retrieve index number for the matching account number entered
int findAccountIndexbyAccNum(int accNmbr, const struct Account accDatabase[], int maxElmnt, int prompt) {

	int i, indexMatch = -1;

	if (prompt) {
		printf("Enter the account#: ");
		accNmbr = getInteger();

	}

	for (i = 0; i < maxElmnt && indexMatch == -1; i++) {

		if (accNmbr == accDatabase[i].accountNmbr) {
			indexMatch = i;

		}

	}

	return indexMatch;
}

//9. Displays summary of all account records
void displayAllAccountSummaryRecords(const struct Account accDatabase[], int maxElmnt) {

	int i;

	displayAccountSummaryHeader();

	for (i = 0; i < maxElmnt; i++) {

		if (accDatabase[i].accountNmbr != 0)
			displayAccountSummaryRecord(&accDatabase[i]);

	}

	putchar('\n');

	pauseExecution();

}

//10. Displays detailed list of all account records
void displayAllAccountDetailRecords(const struct Account accDatabase[], int maxElmnt) {

	int i;

	displayAccountDetailHeader();


	for (i = 0; i < maxElmnt; i++) {

		if (accDatabase[i].accountNmbr != 0)
			displayAccountDetailRecord(&accDatabase[i]);

	}

	putchar('\n');

	pauseExecution();

}

//11. Pause execution until user enters the enter key
void pauseExecution(void) {

	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');

}

//5. Entry point to application logic
void applicationStartup(struct Account accDatabase[], int maxElmnt) {

	int exit = 0;

	do {

		exit = menuLogin(accDatabase, maxElmnt);

		if (accDatabase[exit].accountType == 'C') {
			printf("CUSTOMER: home menu currently unavailable...\n\n");
			pauseExecution();

		} else if (exit > -1) {
			menuAgent(accDatabase, maxElmnt, &accDatabase[exit]);

		}

	} while (exit != -1);

	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");

}





