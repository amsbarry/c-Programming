/**********************************************************************
p1elo931.c  by Barry, Amadou
(change the previous line for your abc123 ID and your name)
Purpose:
	This program reads user data and displays that information in a
 human readable format.
Command Line Arguments:
	p1  -u  usersFileName
Input:
	Stream input file which contains many users. There are two
	different lines of data for each user:
	- User Vehicle Information:
		o One line per user (separated by commas)
			szMake  szModel  dMpg  dPpg  iNumFillups
			10s      10s     lf    lf    d
	- User Contact Information:
		o One line per user (separated by commas)
			szUserId  szEmail  szFullName  szPhone  szLoginName
			6s        30s      20s         13s      12s
		o Use caution when trying to convert szFullName.
		  Although it is a maximum of 20 characters, it may
		  contain spaces; therefore, you cannot simply use %20s.

Results:
	Print the list of users as shown below.

  UserID  Make       Model       AvgMPG  AvgPPG
	 Name             Phone           login        email
  TOY078  Toyota     Corolla      33.33    3.04
	 Marty Falsex Jr. (210)555-7878   mfsex        mfx@furnrow.net
  CHV042  Chevrolet  Cruze        34.34    5.23
	 Klye Lorson      (210)555-4242   klorson      klorson@gnassi.org
  TOY018  Toyota     Yaris        35.35    4.84
	 Khloe Bush       (210)555-1818   kbush        shrubbery@gibbs.edu
  FRD002  Ford       Focus        34.34    2.86
	 Nail Keshighski  (210)555-0202   nhighski     nhighski@pencilke.net
  CHV048  Chevrolet  Sonic        28.28    2.53
	 Johnny Jipsom    (210)555-4848   jjipsom      jjipsom@jhendricks.org
  FRD017  Ford       Fiesta       34.43    4.22
	 Stenny Rickman   (210)555-1717   srickman     srickman@fenway.xyz


Returns:
	0  normal
	1 invalid command line syntax
	2 show usage only
	3 error during processing, see stderr for more information
Notes:
	p1 -?  will provide the usage information.  In some shells,
				you will have to type reserve -\?

**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#define ERR_INVALID_INVENTORY_DATA  "invalid inventory file data"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p1.h"
FILE *pFileUsers;               // stream Input for User data - Global variable

void processCommandSwitches(int argc, char *argv[], char **ppszUserFileName);

int main(int argc, char *argv[])
{
	char *pszUserFileName = NULL;

	// Process the command switches
	processCommandSwitches(argc, argv, &pszUserFileName);

	// open the Users stream data file
	if (pszUserFileName == NULL)
		exitError(ERR_MISSING_SWITCH, "-t");

	pFileUsers = fopen(pszUserFileName, "r");
	if (pFileUsers == NULL)
		exitError(ERR_USER_FILENAME, pszUserFileName);

	// get the Users Data
	getUsers();

	fclose(pFileUsers);
	printf("\n");    // included so that you can put a breakpoint on this line
	return 0;
}

/****** you need to document and code this function *****/
/*
o One line per user (separated by spaces)
            szMake  szModel  dAvgMPG  dAvgPPG  iNumFillups  
            10s     10s      lf       lf       d
    - User Contact Information:
        o One line per user (separated by commas)
            szUserId  szEmail szFullName  szPhone  szLoginName
            6s        30s     20s         13s      12s

*/
/***********************
This fuction reads input from a file strea and prints it out to a formatted standard output
Usage: 
	./p1 -u p1UserData.txt prints output to screen
	./p1 -u p1UserData.txt > p1UserDataOutput.txt prints out output to the text file p1UserDataOutput.txt
************************/
void getUsers(void)
{
	char szInptBuffer[100];
	int iScanfCnt;
	int iUserCnt = 0;
	char *pszUserResult;
	User user;
	// Print headings for the output
	printf("%6s \t%4s \t%5s \t%6s \t%6s\n","UserID","Make","Model","AvgMPG","AvgPPG");
	printf("\t%4s \t\t%5s \t\t%5s \t\t%5s\n","Name","Phone","login","email");
	
		
	// Read user data until reach EOF
		while (fgets(szInptBuffer, 100, pFileUsers) != NULL)
		{
			iScanfCnt = sscanf(szInptBuffer, "%10s %10s %4lf %4lf\n"
				,user.szMake     
				,user.szModel    
				,&user.dAvgMPG        
				,&user.dAvgPPG);
			if (iScanfCnt < 2)
				exit(0);
			printf("%10s \t%10s \t%.2lf \t%.2lf\n"
				,user.szMake    
				,user.szModel     
				,user.dAvgMPG    
				,user.dAvgPPG);
			iScanfCnt = sscanf(szInptBuffer, "%6[^,] %30[^ ] %20[^,] %13[^,] %12[^,]\n"
				,user.szUserId    
				,user.szEmailAddr
				,user.szFullName
				,user.szPhone    
				,user.szLoginName);
			if (iScanfCnt < 2)
				exit(0);
				printf("\t\t%6 \t\t%-30s \t\t%20s \t\t%13s \t\t%12s\n"
				,user.szUserId     
				,user.szEmailAddr    
				,user.szFullName        
				,user.szPhone        
				,user.szLoginName);
	//Counter to continu reading until EOF
			iUserCnt++;
			
		}

}

/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszUserFileName)
Purpose:
	Checks the syntax of command line arguments and returns the filenames.
	If any switches are unknown, it exits with an error.
Parameters:
	I   int argc                    Count of command line arguments
	I   char *argv[]                Array of command line arguments
	O   char **ppszUserFileName     User file name
Notes:
	If a -? switch is passed, the usage is printed and the program exits
	with USAGE_ONLY.
	If a syntax error is encountered (e.g., unknown switch), the program
	prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszUserFileName)
{
	int i;
	// Examine each command argument (except argument 0 which is the executable name)
	for (i = 1; i < argc; i++)
	{
		// check for a switch
		if (argv[i][0] != '-')
			exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
		// determine which switch it is
		switch (argv[i][1])
		{
		case 'u':                   // User File Name
			if (++i >= argc)
				exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
			else
				*ppszUserFileName = argv[i];
			break;
		case '?':
			exitUsage(USAGE_ONLY, "", "");
			break;
		default:
			exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
		}
	}
}

/******************** exitError *****************************
	void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
	Prints an error message and diagnostic to stderr.  Exits with
	ERROR_PROCESSING.
Parameters:
	I char *pszMessage              error message to print
	I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
	This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
	fprintf(stderr, "Error: %s %s\n"
		, pszMessage
		, pszDiagnosticInfo);
	exit(ERROR_PROCESSING);
}

/******************** exitUsage *****************************
	void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
	If this is an argument error (iArg >= 0), it prints a formatted message
	showing which argument was in error, the specified message, and
	supplemental diagnostic information.  It also shows the usage. It exits
	with ERR_COMMAND_LINE_SYNTAX.

	If this is just asking for usage (iArg will be -1), the usage is shown.
	It exits with USAGE_ONLY.
Parameters:
	I int iArg                      command argument subscript
	I char *pszMessage              error message to print
	I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
	This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
	if (iArg != 2)
		fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
			, iArg
			, pszMessage
			, pszDiagnosticInfo);
	fprintf(stderr, "p1 -u userFileName\n");
	if (iArg != 2)
		exit(1);
	else
		exit(2);
}
