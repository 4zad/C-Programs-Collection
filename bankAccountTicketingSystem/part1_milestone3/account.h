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
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#endif // !ACCOUNT_H_

//Macros
#define USER_CHAR_MAX 10
#define DISPLAY_CHAR_MAX 30
#define PASS_CHAR_MAX 8
#define COUNTRY_CHAR_MAX 30
#define AGENT_IDENTIFIER 'A'
#define CUSTOMER_IDENTIFIER 'C'
#define MIN_AGE 18
#define MAX_AGE 110

//Structures
struct Demographic {

	int birthYear;
	double householdIncome;
	char residenceCountry[COUNTRY_CHAR_MAX + 1];

};

struct UserLogin {
	
	char displayName[DISPLAY_CHAR_MAX + 1];
	char userName[USER_CHAR_MAX + 1];
	char userPass[PASS_CHAR_MAX + 1];

};

struct Account {

	int accountNmbr;
	char accountType;
	struct UserLogin userLogin;
	struct Demographic demographic;

};

//Function prototypes:
//1. Promts user for and recieves account data
void getAccount(struct Account* account);

//2. Promts user for and recieves user login data
void getUserLogin(struct UserLogin* userLogin);

//3. Promts user for and recieves user demographic data
void getDemographic(struct Demographic* demographic);
