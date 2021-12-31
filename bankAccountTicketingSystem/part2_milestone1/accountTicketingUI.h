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
#include <ctype.h>

//Safeguard
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

//User Libraries
#include "account.h"
#include "ticket.h"

//Structures
struct AccountTicketingData {

	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array

};

//Function prototypes:
//1. Displays header for summary of account details
void displayAccountSummaryHeader(void);

//2. Displays header for detailed display of account information
void displayAccountDetailHeader(void);

//3. Displays data summary of account details
void displayAccountSummaryRecord(const struct Account* account);

//4. Displays detailed display of account information
void displayAccountDetailRecord(const struct Account* account);

//6. Displays a working login menu
int menuLogin(const struct Account accDatabase[], int maxElmnt);

//7. Displays working menu for agent's accounts
void menuAgent(struct AccountTicketingData* database, const struct Account* account);

//8. To search and retrieve index number for the matching account number entered
int findAccountIndexbyAccNum(int accNmbr, const struct Account accDatabase[], int maxElmnt, int prompt);

//9. Displays summary of all account records
void displayAllAccountSummaryRecords(const struct Account accDatabase[], int maxElmnt);

//10. Displays detailed list of all account records
void displayAllAccountDetailRecords(const struct Account accDatabase[], int maxElmnt);

//11. Pause execution until user enters the enter key
void pauseExecution(void);

//12. Displays working menu for customer accounts


//5. Entry point to application logic
void applicationStartup(struct AccountTicketingData* database);

//Safeguard
#endif // !ACCOUNT_TICKETING_UI_H_
