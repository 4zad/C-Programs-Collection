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

#include "accountTicketingUI.h"
#include "account.h"

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