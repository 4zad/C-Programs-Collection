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

//Safeguard
#ifndef TICKET_H_
#define TICKET_H_

//User Libraries
#include "account.h"

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



//Safeguard
#endif // !TICKET_H_
