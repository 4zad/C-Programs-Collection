/*
	==================================================
	Assignment #2 (Milestone-3):
	==================================================
	Name   : Muhammad Ahmed
	ID     : 146 908 207
	Email  : mahmed224@myseneca.ca
	Section: NCC
*/

//Safeguard
#ifndef TICKET_H_
#define TICKET_H_

//Macros
#define MSSG_CHAR_MAX 150
#define NUM_MSSG_MAX 20
#define MAX_LOGIN_ATTEMPT 3
#define DISPLAY_CHAR_MAX 30

//Structures
struct Message {

	char accountType;
	char displayName[DISPLAY_CHAR_MAX + 1];
	char mssgDetail[MSSG_CHAR_MAX + 1];

};

struct Ticket {

	int ticketNum;
	int accountNum;
	int ticketStatus;
	char subjectLine[DISPLAY_CHAR_MAX + 1];
	int mssgNum;
	struct Message message[NUM_MSSG_MAX];

};

//Function prototypes:
//1. Prompts user for and receives data to create a new ticket
void createTicket(struct Ticket ticketDatabase[], const struct Account* account, int ticketIndex, const int ticketMaxSize);

//2. Displays working menu to customer users with options to modify one of their own tickets 
void modifyTicketMenu(struct Ticket* ticket, const struct Account* account);

//3. Displays working menu to agent users with options to manage an individual ticket
void manageTicketMenu(struct Ticket* ticket, const struct Account* account);

//4. Writes all existing, non-empty tickets to 'tickets.txt' database/storage file
int writeTicketsRecords(const struct Ticket* ticketDatabase, const int ticketMaxSize);

//5. Writes a single line of ticket data onto a file based on the writing mode used in the file address parameter recieved
int appendTicketRecord(const struct Ticket* ticketDatabase, FILE* fp);

//6. Calculates the number of tickets and messages that are saved in the tickets archive file "tickets_arc.txt"
int calcArchivedTicketsStats(int* mssgArchived);

//7. Load all tickets onto the system from 'tickets.txt' file
int loadTickets(struct Ticket* ticketDatabase, const int ticketMaxSize);

//Safeguard
#endif // !TICKET_H_




