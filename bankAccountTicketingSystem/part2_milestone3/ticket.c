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
#include <string.h>

#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"

//Function definitions:
//1. Prompts user for and receives data to create a new ticket
void createTicket(struct AccountTicketingData* database, const struct Account* account, int ticketIndex) {

	int i, highestTicketNmbr = 0, mssgNmbrTemp;

	for (i = 0; i < database->TICKET_MAX_SIZE; i++) {

		if (highestTicketNmbr < database->tickets[i].ticketNmbr) {
			highestTicketNmbr = database->tickets[i].ticketNmbr;

		}

	}

	database->tickets[ticketIndex].ticketNmbr = highestTicketNmbr + 1;
	database->tickets[ticketIndex].accountNmbr = account->accountNmbr;
	database->tickets[ticketIndex].ticketStatus = 1;

	printf("New Ticket (Ticket#:%06d)\n", database->tickets[ticketIndex].ticketNmbr);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (%d chars. maximum): ", DISPLAY_CHAR_MAX);

	getCString(database->tickets[ticketIndex].subjectLine, 1, DISPLAY_CHAR_MAX);
	putchar('\n');

	printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to\nsubmit:\n", MSSG_CHAR_MAX);

	mssgNmbrTemp = database->tickets[ticketIndex].mssgNmbr++;

	getCString(database->tickets[ticketIndex].message[mssgNmbrTemp].mssgDetail, 1, MSSG_CHAR_MAX);
	putchar('\n');

	database->tickets[ticketIndex].message[mssgNmbrTemp].accountType = account->accountType;
	strcpy(database->tickets[ticketIndex].message[mssgNmbrTemp].displayName, account->userLogin.displayName);

}

//2. Displays working menu to customer users with options to modify one of their own tickets 
void modifyTicketMenu(struct Ticket* ticket, const struct Account* account) {

	int menuSelection, confirmSelection, mssgNmbr, flag = 0;

	do {

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticketNmbr);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->ticketStatus ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticket->subjectLine);
		printf("----------------------------------------\n");

		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 3);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", DISPLAY_CHAR_MAX);
			getCString(ticket->subjectLine, 1, DISPLAY_CHAR_MAX);
			putchar('\n');
			break;

		case 2:
			mssgNmbr = ticket->mssgNmbr;

			if (mssgNmbr < NMBR_MSSG_MAX) {
				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to\nsubmit:\n", MSSG_CHAR_MAX);
				getCString(ticket->message[mssgNmbr].mssgDetail, 1, MSSG_CHAR_MAX);
				putchar('\n');

				ticket->message[mssgNmbr].accountType = account->accountType;
				strcpy(ticket->message[mssgNmbr].displayName, account->userLogin.displayName);
				ticket->mssgNmbr++;

			} else {
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");

			}

			break;

		case 3:
			mssgNmbr = ticket->mssgNmbr;

			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			confirmSelection = getCharOption("YN");
			putchar('\n');

			if (confirmSelection == 'Y') {
				printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");
				putchar('\n');

				if (confirmSelection == 'Y' && mssgNmbr < NMBR_MSSG_MAX) {
					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to\nsubmit:\n", MSSG_CHAR_MAX);
					getCString(ticket->message[mssgNmbr].mssgDetail, 1, MSSG_CHAR_MAX);
					putchar('\n');

					ticket->message[mssgNmbr].accountType = account->accountType;
					strcpy(ticket->message[mssgNmbr].displayName, account->userLogin.displayName);
					ticket->mssgNmbr++;

				}

				ticket->ticketStatus = 0;
				printf("*** Ticket closed! ***\n\n");
				flag = 1;

			}

			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//3. Displays working menu to agent users with options to manage an individual ticket
void manageTicketMenu(struct Ticket* ticket, const struct Account* account) {

	int menuSelection, confirmSelection, mssgNmbr, flag = 0;

	do {

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticketNmbr);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->ticketStatus ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticket->subjectLine);
		printf("Acct#   : %d\n", ticket->accountNmbr);
		printf("Customer: %s\n", ticket->message[0].displayName);
		printf("----------------------------------------\n");

		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");

		printf("Selection: ");
		menuSelection = getIntFromRange(0, 3);
		putchar('\n');

		switch (menuSelection) {

		case 1:
			mssgNmbr = ticket->mssgNmbr;

			if (mssgNmbr < NMBR_MSSG_MAX && ticket->ticketStatus) {
				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to\nsubmit:\n", MSSG_CHAR_MAX);
				getCString(ticket->message[mssgNmbr].mssgDetail, 1, MSSG_CHAR_MAX);
				putchar('\n');

				ticket->message[mssgNmbr].accountType = account->accountType;
				strcpy(ticket->message[mssgNmbr].displayName, account->userLogin.displayName);
				ticket->mssgNmbr++;

			} else if (!(ticket->ticketStatus)) {
				printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");

			} else {
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");

			}

			break;

		case 2:
			mssgNmbr = ticket->mssgNmbr;

			if (ticket->ticketStatus) {

				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");
				putchar('\n');

				if (confirmSelection == 'Y') {
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					confirmSelection = getCharOption("YN");
					putchar('\n');

					if (confirmSelection == 'Y' && mssgNmbr < NMBR_MSSG_MAX) {
						printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to\nsubmit:\n", MSSG_CHAR_MAX);
						getCString(ticket->message[mssgNmbr].mssgDetail, 1, MSSG_CHAR_MAX);
						putchar('\n');

						ticket->message[mssgNmbr].accountType = account->accountType;
						strcpy(ticket->message[mssgNmbr].displayName, account->userLogin.displayName);
						ticket->mssgNmbr++;

					}

					ticket->ticketStatus = 0;
					printf("*** Ticket closed! ***\n\n");

				}

			} else if (!(ticket->ticketStatus)) {
				printf("ERROR: Ticket is already closed!\n\n");

			}

			break;

		case 3:
			if (!(ticket->ticketStatus)) {

				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");
				putchar('\n');
				
				if (confirmSelection == 'Y') {
					ticket->ticketStatus = 1;
					printf("*** Ticket re-opened! ***\n\n");

				}
				
			} else if (ticket->ticketStatus) {
				printf("ERROR: Ticket is already active!\n\n");

			}

			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}



