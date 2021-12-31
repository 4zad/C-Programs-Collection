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
void createTicket(struct Ticket ticketDatabase[], const struct Account* account, int ticketIndex, const int ticketMaxSize) {

	int i, highestTicketNum = 0, mssgNumTemp;

	//looks for the highest current existing ticket number
	for (i = 0; i < ticketMaxSize; i++) {

		if (highestTicketNum < ticketDatabase[i].ticketNum) {
			highestTicketNum = ticketDatabase[i].ticketNum;

		}

	}

	ticketDatabase[ticketIndex].ticketNum = highestTicketNum + 1; //assigns (highest ticket number + 1) to new ticket
	ticketDatabase[ticketIndex].accountNum = account->accountNum;
	ticketDatabase[ticketIndex].ticketStatus = 1;

	printf("New Ticket (Ticket#:%06d)\n", ticketDatabase[ticketIndex].ticketNum);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (%d chars. maximum): ", DISPLAY_CHAR_MAX);

	getCString(ticketDatabase[ticketIndex].subjectLine, 1, DISPLAY_CHAR_MAX);
	putchar('\n');

	printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MSSG_CHAR_MAX);

	ticketDatabase[ticketIndex].mssgNum = 0; //set to 0 just to be safe and ensure the message counter logic works
	mssgNumTemp = ticketDatabase[ticketIndex].mssgNum++; //message counter logic: increment message number by one every time a message is written

	getCString(ticketDatabase[ticketIndex].message[mssgNumTemp].mssgDetail, 1, MSSG_CHAR_MAX);
	putchar('\n');

	ticketDatabase[ticketIndex].message[mssgNumTemp].accountType = account->accountType;
	strcpy(ticketDatabase[ticketIndex].message[mssgNumTemp].displayName, account->userLogin.displayName);

}

//2. Displays working menu to customer users with options to modify one of their own tickets 
void modifyTicketMenu(struct Ticket* ticket, const struct Account* account) {

	int menuSelection, confirmSelection, mssgNum, flag = 0;

	do {

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticketNum);
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
			mssgNum = ticket->mssgNum; //local 'mssgNum' variable to shorten and make easier to read the code when inserting the message number as index in code

			if (mssgNum < NUM_MSSG_MAX && ticket->ticketStatus) { //check to see if max number of messages allowed has not been reached and that the ticket is active (closed tickets can not be accessed but this condition is placed just in case)
				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MSSG_CHAR_MAX);
				getCString(ticket->message[mssgNum].mssgDetail, 1, MSSG_CHAR_MAX);
				putchar('\n');

				ticket->message[mssgNum].accountType = account->accountType;
				strcpy(ticket->message[mssgNum].displayName, account->userLogin.displayName);
				ticket->mssgNum++; //message counter logic: increment message number by one every time a message is written

			} else {
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");

			}

			break;

		case 3:
			mssgNum = ticket->mssgNum; //local 'mssgNum' variable to shorten and make easier to read the code when inserting the message number as index in code

			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			confirmSelection = getCharOption("YN");
			putchar('\n');

			if (confirmSelection == 'Y') {

				if (mssgNum < NUM_MSSG_MAX) { //check to see if max number of messages has not been reached and thus, more may be written
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					confirmSelection = getCharOption("YN");
					putchar('\n');

					if (confirmSelection == 'Y') {
						printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MSSG_CHAR_MAX);
						getCString(ticket->message[mssgNum].mssgDetail, 1, MSSG_CHAR_MAX);
						putchar('\n');

						ticket->message[mssgNum].accountType = account->accountType;
						strcpy(ticket->message[mssgNum].displayName, account->userLogin.displayName);
						ticket->mssgNum++; //message counter logic: increment message number by one every time a message is written

					}

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

	int menuSelection, confirmSelection, mssgNum, flag = 0;

	do {

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticketNum);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->ticketStatus ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", ticket->subjectLine);
		printf("Acct#   : %d\n", ticket->accountNum);
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
			mssgNum = ticket->mssgNum; //local 'mssgNum' variable to shorten and make easier to read the code when inserting the message number as index in code

			if (mssgNum < NUM_MSSG_MAX && ticket->ticketStatus) { //check to see if max number of messages allowed has not been reached and that the ticket is active
				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MSSG_CHAR_MAX);
				getCString(ticket->message[mssgNum].mssgDetail, 1, MSSG_CHAR_MAX);
				putchar('\n');

				ticket->message[mssgNum].accountType = account->accountType;
				strcpy(ticket->message[mssgNum].displayName, account->userLogin.displayName);
				ticket->mssgNum++; //message counter logic: increment message number by one every time a message is written

			} else if (!(ticket->ticketStatus)) {
				printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");

			} else {
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");

			}

			break;

		case 2:
			mssgNum = ticket->mssgNum; //local 'mssgNum' variable to shorten and make easier to read the code when inserting the message number as index in code

			if (ticket->ticketStatus) {

				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");
				putchar('\n');

				if (confirmSelection == 'Y') {

					if (mssgNum < NUM_MSSG_MAX) { //check to see if max number of messages has not been reached and thus, more may be written
						printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
						confirmSelection = getCharOption("YN");
						putchar('\n');

						if (confirmSelection == 'Y') {
							printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", MSSG_CHAR_MAX);
							getCString(ticket->message[mssgNum].mssgDetail, 1, MSSG_CHAR_MAX);
							putchar('\n');

							ticket->message[mssgNum].accountType = account->accountType;
							strcpy(ticket->message[mssgNum].displayName, account->userLogin.displayName);
							ticket->mssgNum++; //message counter logic: increment message number by one every time a message is written

						}

					}

					ticket->ticketStatus = 0;
					printf("*** Ticket closed! ***\n\n");

				}

			} else if (!(ticket->ticketStatus)) {
				printf("ERROR: Ticket is already closed!\n\n");

			}

			break;

		case 3:
			if (!(ticket->ticketStatus)) { //if ticket is closed

				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				confirmSelection = getCharOption("YN");
				putchar('\n');
				
				if (confirmSelection == 'Y') {
					ticket->ticketStatus = 1;
					printf("*** Ticket re-opened! ***\n\n");

				}
				
			} else if (ticket->ticketStatus) { //if ticket is active
				printf("ERROR: Ticket is already active!\n\n");

			}

			break;

		case 0:
			flag = 1;
			break;

		}

	} while (!flag);

}

//4. Writes all existing, non-empty tickets to 'tickets.txt' database/storage file
int writeTicketsRecords(const struct Ticket* ticketDatabase, const int ticketMaxSize) {

	int i, ticketRecCount = 0;

	FILE* fp = fopen("tickets.txt", "w");

	if (fp != NULL) {

		for (i = 0; i < ticketMaxSize; i++) {
			
			ticketRecCount += appendTicketRecord(&ticketDatabase[i], fp);

		}

		//safely closing file:
		fflush(fp); 
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //warning message to notify that no address to file received and thus, data cannot be written

	}


	return ticketRecCount;
}

//5. Writes a single line of ticket data onto a file based on the writing mode used in the file address parameter recieved
int appendTicketRecord(const struct Ticket* ticketDatabase, FILE* fp) {

	int i, bytesPrinted = 0;

	if (fp != NULL) {
	
		if (ticketDatabase->ticketNum > 0) { //ensures only tickets that have not been deleted and exist are written to file

			bytesPrinted = fprintf(fp, "%d|%d|%d|%s|%d|", 
							ticketDatabase->ticketNum, 
							ticketDatabase->accountNum, 
							ticketDatabase->ticketStatus, 
							ticketDatabase->subjectLine,
							ticketDatabase->mssgNum);

			if (bytesPrinted > 0) {

				for (i = 0; bytesPrinted > 0 && i < ticketDatabase->mssgNum; i++) {

					bytesPrinted = fprintf(fp, "%c|%s|%s|", 
									ticketDatabase->message[i].accountType, 
									ticketDatabase->message[i].displayName, 
									ticketDatabase->message[i].mssgDetail);

				}

			}

			bytesPrinted = fputc('\n', fp);

		}

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //warning message to notify that no address to file received and thus, data cannot be written

	}

	return bytesPrinted > 0 ? 1 : 0;
}

//6. Calculates the number of tickets and messages that are saved in the tickets archive file "tickets_arc.txt"
int calcArchivedTicketsStats(int* mssgArchived) {

	int i, ticketRecCount = 0, fieldCount = 0, numMssgArchived = 0;
	struct Ticket ticketArchive = { 0 };

	FILE* fp = fopen("tickets_arc.txt", "r"); //reading data from 'tickets_arc.txt'

	if (fp != NULL) {

		do {

			fieldCount = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
				&ticketArchive.ticketNum,
				&ticketArchive.accountNum,
				&ticketArchive.ticketStatus,
				ticketArchive.subjectLine,
				&ticketArchive.mssgNum);

			if (fieldCount == 5) {

				if (ticketArchive.mssgNum > 0) {

					for (i = 0, fieldCount = 3; fieldCount == 3 && i < ticketArchive.mssgNum; i++) {

						fieldCount = fscanf(fp, "%c|%30[^|]|%150[^|]|",
							&ticketArchive.message[i].accountType,
							ticketArchive.message[i].displayName,
							ticketArchive.message[i].mssgDetail);

					}

					numMssgArchived += i; //adds the number of messages that were read in each line/record to the total

				}

				while (fgetc(fp) != '\n'); //discards any remaining chararacters on the line, until and including '\n'
				ticketRecCount++; //increments counter which keeps count of total records read so far

			}

		} while (!feof(fp));

		//safely closing file:
		fflush(fp);
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //warning message to notify that no address to file received and thus, data cannot be read

	}

	if (mssgArchived != NULL)
		*mssgArchived = numMssgArchived;

	return ticketRecCount;
}


//7. Load all tickets onto the system from 'tickets.txt' file
int loadTickets(struct Ticket* ticketDatabase, const int ticketMaxSize) {

	int i, ticketRecCount = 0, fieldCount = 0;

	FILE* fp = fopen("tickets.txt", "r"); //reading data from 'tickets.txt'

	if (fp != NULL) {

		do {

			fieldCount = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
						&ticketDatabase[ticketRecCount].ticketNum,
						&ticketDatabase[ticketRecCount].accountNum,
						&ticketDatabase[ticketRecCount].ticketStatus,
						ticketDatabase[ticketRecCount].subjectLine,
						&ticketDatabase[ticketRecCount].mssgNum);

			if (fieldCount == 5) {

				if (ticketDatabase[ticketRecCount].mssgNum > 0) {

					for (i = 0, fieldCount = 3; fieldCount == 3 && i < ticketDatabase[ticketRecCount].mssgNum; i++) {

						fieldCount = fscanf(fp, "%c|%30[^|]|%150[^|]|",
									&ticketDatabase[ticketRecCount].message[i].accountType,
									ticketDatabase[ticketRecCount].message[i].displayName,
									ticketDatabase[ticketRecCount].message[i].mssgDetail);

					}

				}

				while (fgetc(fp) != '\n'); //discards any remaining chararacters on the line, until and including '\n'
				ticketRecCount++; //increments counter to be used to read values to next index and keeps count of total records loaded into system so far

			}

		} while (!feof(fp) && ticketRecCount < ticketMaxSize);

		//safely closing file:
		fflush(fp);
		fclose(fp);
		fp = NULL;

	} else {
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n"); //warning message to notify that no address to file received and thus, data cannot be read

	}

	return ticketRecCount;
}





