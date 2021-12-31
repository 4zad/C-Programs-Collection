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

//Safeguard
#ifndef TICKET_H_
#define TICKET_H_

//Macros
#define MSSG_CHAR_MAX 150
#define NMBR_MSSG_MAX 20
#define MAX_LOGIN_ATTEMPT 3
#define DISPLAY_CHAR_MAX 30

//Structures
struct Message {

	char accountType;
	char displayName[DISPLAY_CHAR_MAX + 1];
	char mssgDetail[MSSG_CHAR_MAX + 1];

};

struct Ticket {

	int ticketNmbr;
	int accountNmbr;
	int ticketStatus;
	char subjectLine[DISPLAY_CHAR_MAX + 1];
	int mssgNmbr;
	struct Message message[NMBR_MSSG_MAX];

};

//Function prototypes:
//1. Prompts user for and receives data to create a new ticket
void createTicket(struct AccountTicketingData* database, const struct Account* account, int ticketIndex);

//2. Displays working menu to customer users with options to modify one of their own tickets 
void modifyTicketMenu(struct Ticket* ticket, const struct Account* account);

//3. Displays working menu to agent users with options to manage an individual ticket
void manageTicketMenu(struct Ticket* ticket, const struct Account* account);

//Safeguard
#endif // !TICKET_H_


