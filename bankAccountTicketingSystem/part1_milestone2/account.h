/*
	==================================================
	Assignment #1 (Milestone-2):
	==================================================
	Name   : Muhammad Ahmed
	ID     : 146 908 207
	Email  : mahmed224@myseneca.ca
	Section: NCC
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//Macros
#define USER_CHAR_MAX 10
#define DISPLAY_CHAR_MAX 30
#define PASS_CHAR_MAX 8
#define COUNTRY_CHAR_MAX 30

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

};


