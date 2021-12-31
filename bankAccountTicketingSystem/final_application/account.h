/*
	==================================================
	Assignment #2 (Milestone-1):
	==================================================
	Name   : Muhammad Ahmed
	ID     : 146 908 207
	Email  : mahmed224@myseneca.ca
	Section: NCC
*/

//Safeguard
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

//User Libraries
#include "accountTicketingUI.h"

//Macros
#define USER_CHAR_MAX 10
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

	int accountNum;
	char accountType;
	struct UserLogin userLogin;
	struct Demographic demographic;

};

//Function prototypes:
//1. Promts user for and recieves account data
void getAccount(struct AccountTicketingData* database, int indexNmbr);

//2. Promts user for and recieves user login data
void getUserLogin(struct UserLogin* userLogin);

//3. Promts user for and recieves user demographic data
void getDemographic(struct Demographic* demographic);

//4. Displays working menu to update all information
void updateAccount(struct Account* account);

//5. Displays working menu to update user login information
void updateUserLogin(struct UserLogin* userLogin);

//6. Displays working menu to update demographic information
void updateDemographic(struct Demographic* demographic);

//7. Writes all existing, non-empty accounts to 'accounts.txt' database/storage file
int writeAccountRecords(const struct Account* accDatabase, const int accountMaxSize);

//8. Writes a single line of account data onto a file based on the writing mode used in the file address parameter recieved
int appendAccountRecord(const struct Account* accDatabase, FILE* fp);

//9. Calculates the number of account records that are saved in the accounts archive file "accounts_arc.txt"
int calcArchivedAccountStats(void);

//10. Load all account records onto the system from 'accounts.txt' file
int loadAccounts(struct Account* accDatabase, const int accountMaxSize);

//Safeguard
#endif // !ACCOUNT_H_


