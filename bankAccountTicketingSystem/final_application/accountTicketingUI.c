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

#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

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

	printf("%05d %-9s %5d\n", account->accountNum, account->accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", account->demographic.birthYear);

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

	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account->accountNum, account->accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", account->demographic.birthYear, account->demographic.householdIncome, account->demographic.residenceCountry, account->userLogin.displayName, account->userLogin.userName, hiddenUserPass);

}

//6. Displays a working login menu
int menuLogin(const struct Account* accDatabase, int maxElmnt) {

	char loginTest[1000];
	char passTest[1000];
	int i, menuSelection, accNum, flag = 0, indexMatch = -1;
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

			for (i = 0; i < MAX_LOGIN_ATTEMPT && !flag; i++) {

				printf("Enter the account#: ");
				accNum = getPositiveInteger();
				indexMatch = findAccountIndexbyAccNum(accNum, accDatabase, maxElmnt, 0);

				printf("User Login    : ");
				getCString(loginTest, 0, 999);

				printf("Password      : ");
				getCString(passTest, 0, 999);

				if (strcmp(loginTest, accDatabase[indexMatch].userLogin.userName) == 0 && strcmp(passTest, accDatabase[indexMatch].userLogin.userPass) == 0) {
					flag = 1;

				} else {
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", MAX_LOGIN_ATTEMPT - 1 - i);

				}

				putchar('\n');

			}

			if (!flag) {
				printf("ERROR:  Login failed!\n\n");
				pauseExecution();

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

//7. Displays working menu for agent accounts
void menuAgent(struct AccountTicketingData* database, const struct Account* account) {

	int i, menuSelection, indexNum, ticketIndex, flag = 0, accNum = 0, ticketSaved = 0, accSaved = 0, mssgSaved = 0;
	char confirmSelection;

	do {

		printf("AGENT: %s (%d)\n", account->userLogin.displayName, account->accountNum);

		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");

		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 12);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			indexNum = findAccountIndexbyAccNum(0, database->accounts, database->ACCOUNT_MAX_SIZE, 0); //searching for index of an empty account spot in accounts array

			if (indexNum == -1) { //checks to see if empty accounts element does not exist and system is full
				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();

			} else {
				getAccount(database, indexNum); //account setting data is prompted for in this function
				getUserLogin(&database->accounts[indexNum].userLogin); //account login data is prompted for in this function
				getDemographic(&database->accounts[indexNum].demographic); //account demographic data is prompted for in this function

				printf("*** New account added! ***\n\n");
				pauseExecution();

			}

			break;

		case 2:
			printf("Enter the account#: ");
			accNum = getPositiveInteger();
			indexNum = findAccountIndexbyAccNum(accNum, database->accounts, database->ACCOUNT_MAX_SIZE, 0); //search for index of user selected account through account number
			putchar('\n');

			updateAccount(&database->accounts[indexNum]); //function to update account called
			break;

		case 3:
			printf("Enter the account#: ");
			accNum = getPositiveInteger();
			indexNum = findAccountIndexbyAccNum(accNum, database->accounts, database->ACCOUNT_MAX_SIZE, 0); //search for index of user selected account through account number

			if (database->accounts[indexNum].accountNum == account->accountNum) { //check to see if user has selected their own account, which is not allowed
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();

			} else if (indexNum == -1) { //check to see if entered account does not exist
				printf("\nERROR:  Access Denied.\n\n");
				pauseExecution();

			} else { //if account is not the logged on user's and exists, the system enters this body of code
				displayAccountDetailHeader();
				displayAccountDetailRecord(&database->accounts[indexNum]); //display selected account information

				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");

				if (confirmSelection == 'Y') {

					FILE* fp = fopen("tickets_arc.txt", "a"); //assigning 'fp' the address of 'tickets_arc.txt' and opening the file in appending mode

					if (fp != NULL) {

						for (i = 0; i < database->TICKET_MAX_SIZE; i++) {

							if (database->accounts[indexNum].accountNum == database->tickets[i].accountNum) { //condition to check if ticket is associated with selected account

								if (!database->tickets[i].ticketStatus) //condition to check if ticket is closed
									appendTicketRecord(&database->tickets[i], fp);

								database->tickets[i].ticketNum = 0; //setting account related tickets to safe, empty state
								database->tickets[i].mssgNum = 0; //setting mssgNum counter to 0 to help with logic in rest of code

							}

						}

						//safely closing file:
						fflush(fp);
						fclose(fp);
						fp = NULL;

					} else {
						puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

					}

					fp = fopen("accounts_arc.txt", "a"); //re-assigning 'fp' the address of 'accounts_arc.txt' and opening the file in appending mode

					if (fp != NULL) {

						appendAccountRecord(&database->accounts[indexNum], fp);
						database->accounts[indexNum].accountNum = 0; //setting account to safe, empty state

						//safely closing file:
						fflush(fp);
						fclose(fp);
						fp = NULL;

						printf("\n*** Account Removed! ***\n\n");						

					} else {
						puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

					}
					
				} else {
					printf("\n*** No changes made! ***\n\n");

				}

			}

			pauseExecution(); 
			break;

		case 4:
			displayAllAccountSummaryRecords(database->accounts, database->ACCOUNT_MAX_SIZE);
			break;

		case 5:
			displayAllAccountDetailRecords(database->accounts, database->ACCOUNT_MAX_SIZE);
			break;

		case 6:
			newTicketMenu(database);
			break;

		case 7:
			statusFilteredTicketMenu(database, 1); //filters all tickets and displays active ones, respresented by the 2nd argument, 1
			break;

		case 8:
			statusFilteredTicketMenu(database, 0); //filters all tickets and displays closed ones, respresented by the 2nd argument, 0
			break;

		case 9:
			ticketIndex = findTicketIndexNum(1, database->tickets, 1, database->TICKET_MAX_SIZE); //look for index of user entered ticket number
			putchar('\n');

			if (ticketIndex == -1) {
				printf("ERROR: Invalid ticket number\n\n");
				pauseExecution();

			} else {
				manageTicketMenu(&database->tickets[ticketIndex], account);

			}

			break;

		case 10:
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			confirmSelection = getCharOption("YN");
			putchar('\n');

			if (confirmSelection == 'Y') {

				FILE* fp = fopen("tickets_arc.txt", "a"); //assigning 'fp' the address of 'tickets_arc.txt' and opening the file in appending mode

				if (fp != NULL) {

					for (i = 0, ticketSaved = 0; i < database->TICKET_MAX_SIZE; i++) {

						if (!database->tickets[i].ticketStatus) { //condition to check if ticket is closed

							ticketSaved += appendTicketRecord(&database->tickets[i], fp);
							database->tickets[i].ticketNum = 0; //setting closed ticket index to safe, empty state
							database->tickets[i].mssgNum = 0; //setting mssgNum counter to 0 to help with logic in rest of code

						}

					}

					//safely closing file:
					fflush(fp);
					fclose(fp);
					fp = NULL;

					printf("*** %d tickets archived ***\n\n", ticketSaved);

				} else {
					puts("ERROR: UNABLE TO ACCESS FILE!!!\n");

				}

			} else {
				printf("\n*** No changes made! ***\n\n");

			}

			pauseExecution();
			break;

		case 11:
			accSaved = calcArchivedAccountStats(); //counts number of account entries in account archive
			printf("There are %d account(s) currently archived.\n\n", accSaved);
			pauseExecution();
			break;

		case 12:
			ticketSaved = calcArchivedTicketsStats(&mssgSaved); //counts number of tickets total number of messages for all those tickets in ticket archive
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", ticketSaved, mssgSaved);
			pauseExecution();
			break;

		case 0:
			printf("Saving session modifications...\n");

			//overwrites the current account data to permanent storage
			accSaved = writeAccountRecords(database->accounts, database->ACCOUNT_MAX_SIZE); //returns the number of account records saved from system to storage when logging out
			printf("   %d account saved.\n", accSaved);

			//overwrites the current ticket data to permanent storage
			ticketSaved = writeTicketsRecords(database->tickets, database->TICKET_MAX_SIZE); //returns the number of tickets saved from system to storage when logging out
			printf("   %d tickets saved.\n", ticketSaved);
						
			flag = 1; //set to 1 to exit loop and 'logout'
			printf("### LOGGED OUT ###\n\n");
			break;

		}

	} while (!flag);

}

//8. To search and retrieve index number for the matching account number entered
int findAccountIndexbyAccNum(int accNum, const struct Account* accDatabase, int maxElmnt, int prompt) {

	int i, indexMatch = -1;

	if (prompt) {
		printf("Enter your account#: ");
		accNum = getPositiveInteger();

	}

	for (i = 0; i < maxElmnt && indexMatch == -1; i++) { //searches entire accounts array until index for matching account number is found

		if (accNum == accDatabase[i].accountNum) { //checks for matching account number to the one being searched
			indexMatch = i;

		}

	}

	return indexMatch;
}

//9. Displays summary of all account records
void displayAllAccountSummaryRecords(const struct Account* accDatabase, int maxElmnt) {

	int i;

	displayAccountSummaryHeader();

	for (i = 0; i < maxElmnt; i++) {

		if (accDatabase[i].accountNum != 0)
			displayAccountSummaryRecord(&accDatabase[i]);

	}

	putchar('\n');

	pauseExecution();

}

//10. Displays detailed list of all account records
void displayAllAccountDetailRecords(const struct Account* accDatabase, int maxElmnt) {

	int i;

	displayAccountDetailHeader();


	for (i = 0; i < maxElmnt; i++) {

		if (accDatabase[i].accountNum != 0)
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

//12. Displays working menu for customer accounts
void menuCustomer(struct Ticket* ticketDatabase, const struct Account* account, const int ticketMaxSize) {

	int menuSelection, ticketIndex, flag = 0, ticketSaved;

	do {

		printf("CUSTOMER: %s (%d)\n", account->userLogin.displayName, account->accountNum);

		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");

		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 9);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			displayAccountDetailHeader();
			displayAccountDetailRecord(account);
			putchar('\n');
			pauseExecution();
			break;

		case 2:
			ticketIndex = findTicketIndexNum(0, ticketDatabase, 0, ticketMaxSize); //returns index of an empty ticket element in tickets array

			if (ticketIndex == -1) { //checks to see if empty ticket element does not exist and system is full
				printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");

			} else {
				createTicket(ticketDatabase, account, ticketIndex, ticketMaxSize); //creates new ticket
				printf("*** New ticket created! ***\n\n");

			}

			pauseExecution();
			break;

		case 3:
			ticketIndex = findTicketIndexNum(1, ticketDatabase, 1, ticketMaxSize); //look for index of user entered ticket number
			putchar('\n');

			if (ticketDatabase[ticketIndex].accountNum == account->accountNum && ticketDatabase[ticketIndex].ticketStatus) {
				modifyTicketMenu(&ticketDatabase[ticketIndex], account);
				pauseExecution();

			} else if (ticketDatabase[ticketIndex].accountNum != account->accountNum) {
				printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
				pauseExecution();

			} else {
				printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
				pauseExecution();

			}

			break;

		case 4:
			customerTicketlist(ticketDatabase, account, ticketMaxSize);
			break;

		case 0:
			printf("Saving session modifications...\n");

			//overwrites the current ticket data to permanent storage
			ticketSaved = writeTicketsRecords(ticketDatabase, ticketMaxSize); //returns the number of tickets saved from system to storage when logging out
			printf("   %d tickets saved.\n", ticketSaved);

			flag = 1; //set to 1 to exit loop and log out
			printf("### LOGGED OUT ###\n\n");			
			break;

		}

	} while (!flag);
}

//13. Finds index number of array that holds the specified ticket number
int findTicketIndexNum(int ticketNum, const struct Ticket* ticketDatabase, int prompt, const int ticketMaxSize) {

	int i, ticketIndex = -1;

	if (prompt == 1) {
		printf("Enter ticket number: ");
		ticketNum = getPositiveInteger();

	}

	for (i = 0; i < ticketMaxSize; i++) { //searches entire tickets array until index for matching ticket number is found

		if (ticketNum == ticketDatabase[i].ticketNum) { //checks if ticket number at index matches the one being searched for
			ticketIndex = i;

		}

	}

	return ticketIndex;
}

//14. Displays the messages for a specified ticket number
void ticketMessages(const int* ticketIndex, const struct Ticket* ticketDatabase) {

	int i, flag = 0;

	//displaying header
	printf("================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticketDatabase[*ticketIndex].ticketNum, ticketDatabase[*ticketIndex].ticketStatus ? "ACTIVE" : "CLOSED", ticketDatabase[*ticketIndex].subjectLine);
	printf("================================================================================\n");

	for (i = 0; i < NUM_MSSG_MAX && !flag; i++) {

		if (ticketDatabase[*ticketIndex].message[i].accountType != 0) { //checks if message exists at current index
			printf("%s (%s):\n   %s\n\n", ticketDatabase[*ticketIndex].message[i].accountType == AGENT_IDENTIFIER ? "AGENT" : "CUSTOMER", ticketDatabase[*ticketIndex].message[i].displayName, ticketDatabase[*ticketIndex].message[i].mssgDetail); //displays a single individual message

			if ((i + 1) % 5 == 0) //checks if 5th message has been displayed to pause execution
				pauseExecution();

		} else {
			flag = 1; //if no message exists at current index then set flag to stop the loop

			if (i % 5 != 0) //end of messages reached and thus, check to see if this is the 5th message if not we need to pause execution since it wasn't paused in the previous condition
				pauseExecution();

		}

	}

}

//15.  Lists logged on customer's account related tickets 
void customerTicketlist(const struct Ticket* ticketDatabase, const struct Account* account, const int ticketMaxSize) {

	int i, ticketNum, ticketIndex = -1, flag = 0;

	do {

		printf("------ ------ ------------------------------ --------\n");
		printf("Ticket Status Subject                        Messages\n");
		printf("------ ------ ------------------------------ --------\n");

		for (i = 0; i < ticketMaxSize; i++) {

			if (account->accountNum == ticketDatabase[i].accountNum && ticketDatabase[i].ticketNum != 0) //checks each ticket to see if it exists and is associated with an account (through account number)
				printf("%06d %-6s %-30s %5d\n", ticketDatabase[i].ticketNum, ticketDatabase[i].ticketStatus ? "ACTIVE" : "CLOSED", ticketDatabase[i].subjectLine, ticketDatabase[i].mssgNum); //displays individual ticket record

		}

		printf("------ ------ ------------------------------ --------\n\n");

		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		ticketNum = getZeroPositive();
		putchar('\n');

		if (ticketNum == 0) {
			flag = 1;

		} else {
			ticketIndex = findTicketIndexNum(ticketNum, ticketDatabase, 0, ticketMaxSize);

			if (ticketIndex == -1 || account->accountNum != ticketDatabase[ticketIndex].accountNum) {
				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				pauseExecution();

			} else {
				ticketMessages(&ticketIndex, ticketDatabase);

			}

		}

	} while (!flag);

}

//16. Lists currently active tickets through agent menu
void statusFilteredTicketMenu(const struct AccountTicketingData* database, const int status) {

	int i, ticketNum, ticketIndex = -1, flag = 0;

	do {

		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");

		for (i = 0; i < database->TICKET_MAX_SIZE; i++) {

			if (database->tickets[i].ticketStatus == status && database->tickets[i].ticketNum != 0) //checks the status of each ticket and if it exists
				printf("%06d %5d %-15s %-6s %-30s %5d\n", database->tickets[i].ticketNum, database->tickets[i].accountNum, database->tickets[i].message->displayName, database->tickets[i].ticketStatus ? "ACTIVE" : "CLOSED", database->tickets[i].subjectLine, database->tickets[i].mssgNum); //displays individual ticket record

		}

		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");

		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		ticketNum = getZeroPositive();
		putchar('\n');

		if (ticketNum == 0) {
			flag = 1;

		} else {
			ticketIndex = findTicketIndexNum(ticketNum, database->tickets, 0, database->TICKET_MAX_SIZE);

			if (ticketIndex == -1) {
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			} else if (database->tickets[ticketIndex].ticketStatus == status) {
				ticketMessages(&ticketIndex, database->tickets);

			}

		}

	} while (!flag);

}

//17. Lists newly created tickets through agent menu
void newTicketMenu(const struct AccountTicketingData* database) {

	int i, ticketNum, ticketIndex = -1, flag = 0;

	do {

		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");

		for (i = 0; i < database->TICKET_MAX_SIZE; i++) {

			if (database->tickets[i].ticketStatus == 1 && database->tickets[i].message[1].accountType == 0 && database->tickets[i].ticketNum != 0) //checks if each ticket exists adn its message array's 2nd element; if it has no message, it is new
				printf("%06d %5d %-15s %-6s %-30s %5d\n", database->tickets[i].ticketNum, database->tickets[i].accountNum, database->tickets[i].message->displayName, database->tickets[i].ticketStatus ? "ACTIVE" : "CLOSED", database->tickets[i].subjectLine, database->tickets[i].mssgNum); //displays individual ticket record

		}

		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");

		printf("Enter the ticket number to view the messages or\n0 to return to previous menu: ");
		ticketNum = getZeroPositive();
		putchar('\n');

		if (ticketNum == 0) {
			flag = 1;

		} else {
			ticketIndex = findTicketIndexNum(ticketNum, database->tickets, 0, database->TICKET_MAX_SIZE);

			if (ticketIndex == -1) {
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			} else if (database->tickets[ticketIndex].ticketStatus == 1 && database->tickets[i].message[1].accountType == 0) {
				ticketMessages(&ticketIndex, database->tickets);

			}

		}

	} while (!flag);

}

//5. Entry point to application logic
void applicationStartup(struct AccountTicketingData* database) {

	int exit = 0;

	do {

		exit = menuLogin(database->accounts, database->ACCOUNT_MAX_SIZE);

		//depending on the logged on account's account type customer or agent menu will be displayed
		if (database->accounts[exit].accountType == 'C' && exit > -1) {
			menuCustomer(database->tickets, &database->accounts[exit], database->TICKET_MAX_SIZE);

		} else if (database->accounts[exit].accountType == 'A' && exit > -1) {
			menuAgent(database, &database->accounts[exit]);

		}

	} while (exit != -1);

	printf("==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");

}





