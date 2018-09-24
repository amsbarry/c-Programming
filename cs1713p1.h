/**********************************************************************
cs1713p1.h
Purpose:
    Defines typedefs for
        User - includes user ID, user full name, email address,
               phone number, user login name, make and model of car
               average miles per gallon, average price per gallon,
               and number of fillups.
    Defines constants for
        boolean values
        error messages
        program return codes
    Prototypes
Notes:
    
**********************************************************************/

/**** typedefs ****/

// User information
typedef struct
{
    char        szUserId[7];            // 6 character User ID
    char        szEmailAddr[31];        // User's email address
    char        szLoginName[13];        // User's login name
    char        szPhone[14];            // User contact phone number (999)999-9999
    char        szFullName[21];         // User first and last name
    char        szMake[11];             // Vehicle make
    char        szModel[11];            // Vehicle model
    double      dAvgMPG;                // average miles per gallon
    double      dAvgPPG;                // average price per gallon
    int         iNumFillups;            // number of fillups in average
} User;

/**** constants ****/
// Maximum sizes 
#define MAX_LINE_SIZE 100

// boolean
#define FALSE           0
#define TRUE            1

/*  Error Messages */
#define ERR_MISSING_SWITCH      "missing switch "
#define ERR_EXPECTED_SWITCH     "expected switch, found "
#define ERR_MISSING_ARGUMENT    "missing argument for "
#define ERR_USER_FILENAME       "invalid User file name "
#define ERR_USER_ID_DATA        "invalid User vehicle data "
#define ERR_USER_CONTACT_DATA   "invalid User contact data "

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     1      // invalid command line syntax
#define USAGE_ONLY                  2      // show usage only
#define ERROR_PROCESSING            3

/* prototypes */

/* functions you must code  */
void getUsers(void);

/* helper functions */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);
