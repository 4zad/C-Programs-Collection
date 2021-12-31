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

//Safeguard
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#endif // !ACCOUNT_TICKETING_UI_H_

//Function prototypes:
//1. Displays header for summary of account details
void displayAccountSummaryHeader(void);

//2. Displays header for detailed display of account information
void displayAccountDetailHeader(void);

//3. Displays data summary of account details
void displayAccountSummaryRecord(const struct Account* account);

//4. Displays detailed display of account information
void displayAccountDetailRecord(const struct Account* account);


