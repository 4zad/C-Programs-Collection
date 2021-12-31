# BANK ACCOUNT TICKETING SYSTEM

This app was created in April 2021, as a final project in my first term in the CPA program at Seneca College.


# Instructions, given by the Prof, for each milestone are listed below:

## PART 1:

#### MILESTONE 1:
Milestone - 1 includes a unit tester (a1ms1.c). A unit tester is a program which invokes your functions, passing them known parameter values. It then compares the results returned by your functions with the correct results to determine if your functions are working correctly. The tester should be used to confirm your solution meets the specifications for each “helper” function. The helper functions should be thoroughly tested and fail-proof (100% reliable) as they will be used throughout your assignment milestones. An optional matrix submitter tester is also at your disposal so you can receive additional confirmation that your solution meets the minimum milestone requirements.

#### MILESTONE 2:
You will begin this Milestone - 2 by creating some new data types in an “account.h” header file, and the main function creates variable instances of those new types. You will prompt for user input and store the entered values to the appropriate variable members. It is expected you will call functions from the common helper library where appropriate. After data has been entered and stored, you will display the information back to the user in a tabular format (review the sample output section).

#### MILESTONE 3:
In Milestone – 3, the “account” module will be refined and expanded on to include three (3) functions which will handle user input for account related data. A new “accountTicketingUI” (user interface) module will be introduced starting with four (4) functions that will be responsible for displaying account records in a tabular format.

#### MILESTONE 4:
In Milestone - 4, you will be adding more functionality to the "account" module that will support the updating of data whereby the user can select a specific field member to change for each of the user-defined data types (Account, UserLogin, Demographic). You will expand the "accountTicketingUI" module to include a menu-driven model for navigating the application features. The application will provide an "agent" user-type a custom menu for managing customer account records.


## PART 2:

#### MILESTONE 1:
Milestone - 1 includes the main function and should not be modified (a2ms1.c). This main will do some preliminary data type testing by creating some test data using the new data types and then launch the application logic by calling the applicationStart function accordingly.

This milestone focuses on accommodating some new data types and extending/improving on data validation routines including implementing additional business logic (rules and conditions for data).

#### MILESTONE 2:
Milestone – 2 will involve refinements to be made to any appropriate code that would benefit from using the string library (string.h). In addition, the login procedure and requirements will be enhanced to include more robust authentication. This will involve the prompting of the user for their account number, login identifier, and password to be validated before being given access to the system (only three (3) attempts will be permitted and if not successful, will be returned to the login menu). Lastly, the viewing of ticket information will be added for both the customer and agent account types.

This milestone focuses on accommodating some new data types and extending/improving on data validation routines including implementing additional business logic (rules and conditions for data).

#### MILESTONE 3:
Milestone - 3 includes the main function and, like previous milestones, should not be modified (a2ms3.c). The provided main creates some test data and then launches the application logic by calling the applicationStart function.

This milestone completes the ticketing component where data input and the management of tickets is implemented. It is highly possible you will need to create a source code file (.c) for the ticket module/library to address some of the new features for this milestone.

#### MILESTONE 4:
In Milestone – 4, the last major component to be added will involve the implementation of persistent storage of the account and ticketing data. The system will require the functionality to load account and ticket information from files, save account and ticket information to files and finally archive data which will no longer be actively used in the system.


