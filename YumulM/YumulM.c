/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Yumul, Mark Isaiah I., DLSU ID# 12208817
*********************************************************************************************************/

/* Header Libraries */
#include <stdio.h>
#include <string.h>
#include <conio.h> /* For the password input, from https://www.scaler.com/topics/getch-in-c/ */ 
#include <stdlib.h> /* For the clearing of console, from https://www.grepper.com/answers/183836/clear+screen+c */
#include <time.h> /* For the randomizer function, from https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm */
#define MAX 50
#define MAX_PLAYERS 100

/* Typedef Declarations */
typedef char str20[21];
typedef char str30[31];
typedef char str50[51];
typedef char str150[151];

/* Structure Declarations */
struct quizRecord {
	str20 topic;
	int questionNum;
	str150 question;
	str30 choiceOne;
	str30 choiceTwo;
	str30 choiceThree;
	str30 answer;
};

struct playerDetails{
	int playerNum;
	str20 playerName;
	int playerScore;
};

/* Function Prototypes */
void mainMenu(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
int inputPassword(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void manageDataFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void addRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void editRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void deleteRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void loopDeleteRecord(struct quizRecord quizData[], int *numRecords, int pickedRecord);
int importData(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void exportData(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void quizGameFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
int latestQuestionNumber(struct quizRecord quizData[], int *numRecords, char topicChosen[]);
void playFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);
void viewScores(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords,int *currentNumPlayers, int *flagScoreFile);
void exitGameFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile);

/* 	mainMenu will contain the options the user has when opening the program at first
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: User must type the whole keyword completely
*/
void 
mainMenu(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str50 mainMenuCommand = {'\0'}; //To clear contents of string
	char enterKey;
	
	/* First instance of asking for command */
	printf("Welcome to Quiz Game! Kindly enter a command:\n");
	printf("Available commands are Manage data (for admin), Play (for players), or Exit (the program): "); 
	scanf("%[^\n]s", mainMenuCommand);
	scanf("%c", &enterKey);
	
	if ((strcmp(mainMenuCommand, "manage data") == 0) || (strcmp(mainMenuCommand, "Manage data") == 0))
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if ((strcmp(mainMenuCommand, "Play") == 0) || (strcmp(mainMenuCommand, "play") == 0))
	{
		printf("\n");
		quizGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if ((strcmp(mainMenuCommand, "Exit") == 0) || (strcmp(mainMenuCommand, "exit") == 0))
	{
		printf("Program will now be exited. Kindly Press any key to exit. ");
	}
	else 
	{	
		/* Second instance of asking for command in case of invalid first input */
		do
		{
			printf("Invalid command. Kindly enter a valid command: ");
			scanf("%[^\n]s", mainMenuCommand);
			scanf("%c", &enterKey);
			
			if (strcmp(mainMenuCommand, "Manage data") == 0)
			{
				printf("\n");
				manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
			else if (strcmp(mainMenuCommand, "Play") == 0)
			{
				printf("\n");
				quizGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
			else if (strcmp(mainMenuCommand, "Exit") == 0)
			{
				printf("\nProgram will now be exited. Kindly Press any key to exit. ");
			}
		} while (strcmp(mainMenuCommand, "Manage data") != 0 && strcmp(mainMenuCommand, "Play") != 0 && strcmp(mainMenuCommand, "Exit") != 0);
	}
}

/*	inputPassword returns the key to access the manage data function
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	@return 1 if password matches the input, else return 0
	Pre-condition: User must select option Manage Data from mainMenu
*/
int 
inputPassword(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str50 password = {'\0'}; //To clear contents of string
	char character;
	int index = 0;
	int result = 0;
	
	/* First instance of asking password */
	printf("Enter Password: ");
	
	while ((character = getch()) != 13)
	{
		password[index] = character;
		printf("*");
		index++;
	}
	
	/* If initial input is not the password */
	if (strcmp(password, "Swift") != 0)
	{
		do
		{
			index = 0; //Return to first element of array and replace
			
			printf("\nKindly enter the password again or go back to main menu: ");	
			
			while ((character = getch()) != 13)
			{
				password[index] = character;
				printf("*");
				index++;
			}
			
			if (strcmp(password, "main menu") == 0 || strcmp(password, "Main menu") == 0 || strcmp(password, "Main Menu") == 0)
			{
				printf("\n");
				mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
		} while (strcmp(password, "Swift") != 0 && (strcmp(password, "main menu") != 0 || strcmp(password, "Main menu") != 0 || strcmp(password, "Main Menu") != 0));
	}
	
	if (strcmp(password, "Swift") == 0)
		result = 1;
	
	password[index] = '\0'; //Add a null character at the end of the string
	
	return result;
}

/*	manageDataFunc will contain the options for the admin to modify the records stored within the quiz game
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Precondition: User must type in the complete keyword in order to progress
*/
void
manageDataFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str30 command;
	char enterKey;
	
	/* First instance of asking for admin command */
	if (inputPassword(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile) == 1)
	{
		printf("\nWelcome admin! Kindly enter a command:\n");
		printf("Available commands are: Add record, Edit record, Delete record, Import data, Export data, or main menu:");
		scanf("%[^\n]s", command);
		scanf("%c", &enterKey);
		
		if ((strcmp(command, "Add record") == 0) || (strcmp(command, "add record") == 0))
		{
			printf("\n");
			addRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else if ((strcmp(command, "Edit record") == 0) || (strcmp(command, "edit record") == 0))
		{
			printf("\n");
			editRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else if ((strcmp(command, "Delete record") == 0) || (strcmp(command, "delete record") == 0))
		{
			printf("\n");
			deleteRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else if ((strcmp(command, "Import data") == 0) || (strcmp(command, "import data") == 0))
		{
			printf("\n");
			importData(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else if ((strcmp(command, "Export data") == 0) || (strcmp(command, "export data") == 0))
		{
			printf("\n");
			exportData(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else if (strcmp(command, "Main menu") == 0 || (strcmp(command, "main menu") == 0))
		{
			system("cls");
			mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else 
		{
			/* Second instance of asking for admin command if first input is invalid */
			do
			{
				printf("Invalid option. Kindly enter a valid command or return to main menu:");
				scanf("%[^\n]s", command);
				scanf("%c", &enterKey);
				
				if ((strcmp(command, "Add record") == 0) || (strcmp(command, "add record") == 0))
				{
					printf("\n");
					addRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if ((strcmp(command, "Edit record") == 0) || (strcmp(command, "edit record") == 0))
				{
					printf("\n");
					editRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if ((strcmp(command, "Delete record") == 0) || (strcmp(command, "delete record") == 0))
				{
					printf("\n");
					deleteRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if ((strcmp(command, "Import data") == 0) || (strcmp(command, "import data") == 0))
				{
					printf("\n");
					importData(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if ((strcmp(command, "Export data") == 0) || (strcmp(command, "export data") == 0))
				{
					printf("\n");
					exportData(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if (strcmp(command, "Main menu") == 0 || (strcmp(command, "main menu") == 0))
				{
					system("cls");
					mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
			} while ((strcmp(command, "Add record") != 0) && (strcmp(command, "Edit record") != 0) && (strcmp(command, "Delete record") != 0)
			&& (strcmp(command, "Import data") != 0) && (strcmp(command, "Export data") != 0) && (strcmp(command, "Main menu") != 0) && (strcmp(command, "main menu") != 0) && 
			(strcmp(command, "add record") != 0) && (strcmp(command, "edit record") != 0) && (strcmp(command, "delete record") != 0) && (strcmp(command, "import data") != 0) &&
			(strcmp(command, "export data") != 0));			
		}
	}
}

/*	addRecord will contain the process of how to add a record manuallyby inputting each part of the struct quizRecord quizData
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Records must not reach MAX in order to utilize this function
*/
void 
addRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	int i, j;
	str150 tempQuestion;
	str30 tempAnswer;
	int result = 1;
	int latestQuestionNum = 0;
	char enterKey;
	
	if (*numRecords == MAX)
	{
		printf("Records is full. Kindly delete a record before adding a record.\n");
		printf("Program will now return to manage data screen.");	
		
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	printf("Enter a question or go back to manage data: ");
	scanf("%[^\n]s\n", tempQuestion);
	scanf("%c", &enterKey);
	
	if ((strcmp(tempQuestion, "manage data") == 0) || (strcmp(tempQuestion, "Manage data") == 0) || (strcmp(tempQuestion, "Manage Data") == 0))
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	printf("Enter the answer to the question or go back to manage data: ");
	scanf("%[^\n]s\n", tempAnswer);
	scanf("%c", &enterKey);

	if ((strcmp(tempAnswer, "manage data") == 0) || (strcmp(tempAnswer, "Manage data") == 0) || (strcmp(tempAnswer, "Manage Data") == 0))
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}	
	
	for (i = 0; i < MAX && result != 0; i++)
	{
		if (strcmp(quizData[i].question, tempQuestion) == 0 && strcmp(quizData[i].answer, tempAnswer) == 0)
		{
			printf("The added question and answer is already listed. Program will now go back to manage data screen.");
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			result = 0;
		}	
	}
	
	if (result == 1)
	{
		strcpy(quizData[*numRecords].question, tempQuestion);
		strcpy(quizData[*numRecords].answer, tempAnswer);
		
		printf("Enter the topic of the question or go back to manage data: ");
		scanf("%[^\n]s", quizData[*numRecords].topic);
		scanf("%c", &enterKey);
		
		if ((strcmp(quizData[*numRecords].topic, "manage data") == 0) || (strcmp(quizData[*numRecords].topic, "Manage data") == 0))
		{
			strcpy(quizData[*numRecords].topic, "");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		
		printf("Enter the first choice or go back to manage data: ");
		scanf("%[^\n]s", quizData[*numRecords].choiceOne);
		scanf("%c", &enterKey);
		
		if ((strcmp(quizData[*numRecords].choiceOne, "manage data") == 0) || (strcmp(quizData[*numRecords].choiceOne, "Manage data") == 0))
		{
			strcpy(quizData[*numRecords].choiceOne, "");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		
		printf("Enter the second choice or go back to manage data: ");
		scanf("%[^\n]s", quizData[*numRecords].choiceTwo);
		scanf("%c", &enterKey);
		
		if ((strcmp(quizData[*numRecords].choiceTwo, "manage data") == 0) || (strcmp(quizData[*numRecords].choiceTwo, "Manage data") == 0))
		{
			strcpy(quizData[*numRecords].choiceTwo, "");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		
		printf("Enter the third choice or go back to manage data: ");
		scanf("%[^\n]s", quizData[*numRecords].choiceThree);
		scanf("%c", &enterKey);
		
		if ((strcmp(quizData[*numRecords].choiceThree, "manage data") == 0) || (strcmp(quizData[*numRecords].choiceThree, "Manage data") == 0))
		{
			strcpy(quizData[*numRecords].choiceThree, "");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		
		/* Automatically assigning question number */
		for (j = 0; j < *numRecords; j++)
		{
			if (strcmp(quizData[j].topic, quizData[*numRecords].topic) == 0) //Isolated all records with same topic
			{
				latestQuestionNum = quizData[j].questionNum; //Increment every time it sees same topic including the new record
			}
		}
		
		latestQuestionNum = latestQuestionNum + 1; //Add one for the new question number for added record
		
		quizData[*numRecords].questionNum = latestQuestionNum; 
		
		*numRecords = *numRecords + 1;
		
		printf("Record successfully added, program will now return to manage data. ");
		printf("Number of records after adding: %d\n", *numRecords);
		
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
}

/*	displayUniqueTopics displays each topic in the array of topic only once
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param *numRecords - the current number of records the program currently has
	Pre-condition: Must have elements stored in struct quizRecord quizData
*/
void 
displayUniqueTopics(struct quizRecord quizData[], int *numRecords)
{
	int ctr;
	int a, b;
	
	printf("AVAILABLE TOPICS: ");
	
	for (a = 0; a < *numRecords; a++)
	{
		ctr = 0;
		for (b = a + 1; b < *numRecords && ctr == 0; b++)
		{
			if (strcmp(quizData[a].topic, quizData[b].topic) == 0)
			{
				ctr++;
			}
		}
		
		if (ctr == 0)
		{
			printf("%s ", quizData[a].topic);
		}
	}
}

/* editRecord allows the admin to modify a part of the existing records stored in the struct quizRecord quizData
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to have at least one record in order to access this function
*/
void 
editRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str20 topicChosen;
	str30 edit;
	str50 newChange;
	char enterKey;
	int k, l, m;
	int questionNumChosen;
	int key;
	int editAgain;
	
	int oldQuestionNum;
	str20 oldTopic;
	
	if (*numRecords == 0)
	{
		printf("No records currently stored. Program will return to manage data function. \n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	displayUniqueTopics(quizData, numRecords);
	
	printf("\nKindly enter a topic to narrow down the search or go back to manage data: ");
	scanf("%s", topicChosen);
	scanf("%c", &enterKey);
	
	if ((strcmp(topicChosen, "manage data") == 0) || (strcmp(topicChosen, "Manage data") == 0) || (strcmp(topicChosen, "Manage data") == 0))
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	printf("\nThe questions from these topic are: \n");
	
	/* To print the questions under that topic */
	for (k = 0; k < *numRecords; k++)
	{
		if (strcmp(topicChosen, quizData[k].topic) == 0)
		{		
			printf("%d - %s\n", quizData[k].questionNum, quizData[k].question);
		}
	}
	
	printf("\n");
	printf("Kindly enter the question number you wish to edit: ");
	scanf("%d", &questionNumChosen);
	
	for (l = 0; l < *numRecords; l++)
	{
		if (quizData[l].questionNum == questionNumChosen && (strcmp(quizData[l].topic, topicChosen) == 0))
		{
			key = l;
		}
	}
	
	printf("\nCurrent record chosen: \n");
	printf("Topic: %s\n", quizData[key].topic);
	printf("Question: %s\n", quizData[key].question);
	printf("Choice 1: %s\n", quizData[key].choiceOne);
	printf("Choice 2: %s\n", quizData[key].choiceTwo);
	printf("Choice 3: %s\n", quizData[key].choiceThree);
	printf("Answer: %s\n", quizData[key].answer);
	
	printf("Kindly select which field (topic, question, choice1, choice2, choice3, or answer) to edit or go back to manage data: ");
	scanf("%s[^\n]", edit);
	scanf("%c", &enterKey);
	
	if ((strcmp(edit, "manage data") == 0) || (strcmp(edit, "Manage data") == 0))
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if ((strcmp("topic", edit) == 0) || (strcmp("Topic", edit) == 0))
	{
		printf("Kindly enter the new topic or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else 
		{
			strcpy(oldTopic, quizData[key].topic);
			oldQuestionNum = quizData[key].questionNum;
			
			quizData[key].questionNum = latestQuestionNumber(quizData, numRecords, newChange); //Update new topic
			strcpy(quizData[key].topic, newChange);
			
			for (m = 0; m < *numRecords; m++)
			{
				if (strcmp(oldTopic, quizData[m].topic) == 0 && quizData[m].questionNum > oldQuestionNum)
				{
					quizData[m].questionNum = quizData[m].questionNum - 1;
				}
			}
		}
	}
	else if (strcmp("question", edit) == 0)
	{
		printf("Kindly enter the new question or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else
		{
			strcpy(quizData[key].question, newChange);
		}
	}
	else if (strcmp("choice1", edit) == 0)
	{
		printf("Kindly enter the new choice1 or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else
		{
			strcpy(quizData[key].choiceOne, newChange);
		}
	}
	else if (strcmp("choice2", edit) == 0)
	{
		printf("Kindly enter the new choice2 or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else
		{
			strcpy(quizData[key].choiceTwo, newChange);
		}
	}
	else if (strcmp("choice3", edit) == 0)
	{
		printf("Kindly enter the new choice 3 or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else
		{
			strcpy(quizData[key].choiceThree, newChange);
		}
	}
	else if (strcmp("answer", edit) == 0)
	{
		printf("Kindly enter the new answer or go back to manage data: ");
		scanf("%s[^\n]", newChange);
		
		if ((strcmp(newChange, "manage data") == 0) || (strcmp(newChange, "Manage data") == 0))
		{
			printf("\n");
			manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		else
		{
			strcpy(quizData[key].answer, newChange);
		}
	}
	else 
	{
		printf("Invalid input. Program will now go to manage data screen.\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	printf("Edited record successfully. Would you like to edit another record? Press 1 for yes and any other number to return to manage data screen: ");
	scanf("%d", &editAgain);
	
	if (editAgain == 1)
	{
		printf("\n");
		editRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else 
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
}

/* deleteRecord allows the admin to delete an existing record stored in the struct quizRecord quizData
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to have at least one record in order to access this function
*/
void 
deleteRecord(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	int i, j;
	str50 chosenTopic;
	int stopper = 0;
	int chosenNumber;
	int confirmationNum;
	int secondChoice;
	char enterKey;
	
	if (*numRecords == 0)
	{
		printf("No records stored. Program will return to manage data screen.\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	displayUniqueTopics(quizData, numRecords);
	
	printf("\nKindly select from which topic to delete a record or go back to manage data: ");
	scanf("%s[^\n]", chosenTopic);
	
	if (strcmp(chosenTopic, "manage data") == 0)
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	printf("Question Number - Question\n");
	
	for (i = 0; i < *numRecords; i++)
	{
		if (strcmp(quizData[i].topic, chosenTopic) == 0)
		{
			printf("%d - %-20s\n", quizData[i].questionNum, quizData[i].question);
		}
	}
	
	printf("Enter the question number within that topic to delete or enter ""0"" to go back to manage data: ");
	scanf("%d", &chosenNumber);
	
	if (chosenNumber == 0)
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else 
	{
		for (j = 0; j < *numRecords && stopper == 0; j++)
		{
			if ((strcmp(quizData[j].topic, chosenTopic) == 0) && (chosenNumber == quizData[j].questionNum))
			{
				printf("Record chosen: %d - %s", quizData[j].questionNum, quizData[j].question);
				printf("\nConfirmation: Do you want to delete this record? Enter 1 for yes and any other number for no to return to manage data func: ");
				scanf("%d", &confirmationNum);
				scanf("%c", &enterKey);
				
				if (confirmationNum != 1 && stopper == 0)
				{
					printf("\n");
					manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else if (confirmationNum == 1 && stopper == 0)
				{
					if ((strcmp(chosenTopic, quizData[j].topic) == 0) && (chosenNumber == quizData[j].questionNum))
					{
						loopDeleteRecord(quizData, numRecords, j); //Function to delete the chosen record and loop suceeding records
					}
					stopper = 1;
					*numRecords = *numRecords - 1;
					printf("Current number of records: %d", *numRecords);
				}
			}
		}
	}
	
	printf("\n");
	printf("Do you wish to delete another record? Enter 1 for yes and any other number to go back to manage data: ");
	scanf("%d", &secondChoice);
	
	if (secondChoice == 1)
	{
		printf("\n");
		deleteRecord(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
}

/* loopDeletRecord is responsible for assigning the succeeding records of the deleted record to a new index 
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param *numRecords - the current number of records the program currently has
	@param pickedRecord - the index of the exact record chosen in deleteRecord()
	Pre-condition: Must need to have a valid record in order to access this function
*/
void 
loopDeleteRecord(struct quizRecord quizData[], int *numRecords, int pickedRecord)
{
	int i;
	int origPickedRecord = pickedRecord;
	
	for (i = pickedRecord; i < *numRecords; i++)
	{
		if ((strcmp(quizData[pickedRecord].topic, quizData[i].topic) == 0) && (strcmp(quizData[origPickedRecord].topic, quizData[i].topic) == 0))
		{
			strcpy(quizData[pickedRecord].topic, quizData[i].topic);
			quizData[pickedRecord].questionNum = quizData[i].questionNum - 1;
			strcpy(quizData[pickedRecord].question, quizData[i].question);
			strcpy(quizData[pickedRecord].choiceOne, quizData[i].choiceOne);
			strcpy(quizData[pickedRecord].choiceTwo, quizData[i].choiceTwo);
			strcpy(quizData[pickedRecord].choiceThree, quizData[i].choiceThree);
			strcpy(quizData[pickedRecord].answer, quizData[i].answer);
			pickedRecord = i;
		}
		else if (i < *numRecords && i != *numRecords)
		{
			strcpy(quizData[pickedRecord].topic, quizData[i].topic);
			quizData[pickedRecord].questionNum = quizData[i].questionNum;
			strcpy(quizData[pickedRecord].question, quizData[i].question);
			strcpy(quizData[pickedRecord].choiceOne, quizData[i].choiceOne);
			strcpy(quizData[pickedRecord].choiceTwo, quizData[i].choiceTwo);
			strcpy(quizData[pickedRecord].choiceThree, quizData[i].choiceThree);
			strcpy(quizData[pickedRecord].answer, quizData[i].answer);
			pickedRecord = i;
		}
	}
}

/* importData allows the admin to read the contents of any file and store it into struct quizRecord quizData
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to be a valid file to successfully read values
*/
int 
importData(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str30 fileName;
	str30 fileName2;
	str20 readTopic;
	FILE *fp1;
	FILE *fp2;
	char enterKey;
	int scanResult;
	
	/* First time asking for file */
	printf("Kindly enter the filename to load or go back to manage data: ");
	scanf("%[^\n]s", fileName);
	scanf("%c", &enterKey);
	
	fp1 = fopen(fileName, "r");
	
	if (fp1) //File exists
	{	
		while (fscanf(fp1, "%20[^\n]", quizData[*numRecords].topic) != EOF)
		{
			strcpy(readTopic, quizData[*numRecords].topic);
			while ((scanResult = fscanf(fp1, "%d %150[^\n] %30[^\n] %30[^\n] %30[^\n] %30[^\n]", &quizData[*numRecords].questionNum, 
            quizData[*numRecords].question, quizData[*numRecords].choiceOne, quizData[*numRecords].choiceTwo, 
			quizData[*numRecords].choiceThree, quizData[*numRecords].answer)) == 6) 
			{
				quizData[*numRecords].questionNum = latestQuestionNumber(quizData, numRecords, readTopic) + 1;
				*numRecords = *numRecords + 1;
			}
		}
		
		fclose(fp1);
		printf("Number of records after importing: %d\n", *numRecords);
		printf("Import added successfully!\n");
		printf("\n");
		
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
	else if (strcmp(fileName, "manage data") == 0 || strcmp(fileName, "Manage data") == 0 || strcmp(fileName, "Manage Data") == 0)
	{
		printf("\n");
		manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if (fp1 == NULL) /* Second instance of asking for file or go back to main menu */
	{
		do
		{
			strcpy(fileName2, "\0");
			printf("File not found. Kindly enter a filename again or go back to manage data: ");
			scanf("%[^\n]s", fileName2);
			scanf("%c", &enterKey);
		
			fp2 = fopen(fileName2, "r");
		
			if (fp2)
			{
				while (fscanf(fp2, "%20[^\n]", quizData[*numRecords].topic) != EOF)
				{
					strcpy(readTopic, quizData[*numRecords].topic);
					while ((scanResult = fscanf(fp2, "%d %150[^\n] %30[^\n] %30[^\n] %30[^\n] %30[^\n]", &quizData[*numRecords].questionNum,
    		        quizData[*numRecords].question, quizData[*numRecords].choiceOne, quizData[*numRecords].choiceTwo, 
					quizData[*numRecords].choiceThree, quizData[*numRecords].answer)) == 6) 
					{
						quizData[*numRecords].questionNum = latestQuestionNumber(quizData, numRecords, readTopic) + 1;
						*numRecords = *numRecords + 1;
					}
				}
				
				fclose(fp2);
				printf("Number of records after importing: %d\n", *numRecords);
				printf("Import added successfully!\n");
				printf("\n");
				manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
			else if (strcmp(fileName2, "manage data") == 0 || strcmp(fileName2, "Manage data") == 0 || strcmp(fileName2, "Manage Data") == 0)
			{
				printf("\n");
				manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
		} while ((fp2 == NULL) && (strcmp(fileName2, "manage data") != 0 || strcmp(fileName2, "Manage data") != 0 || strcmp(fileName2, "Manage Data") != 0));
	}
	
	return *numRecords;
}

/* exportData allows the admin to store the current records into a file
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to have records stored in struct quizRecord quizData
*/
void 
exportData(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	FILE *fp;
	str30 expoFilename;
	char enterKey;
	int i;
	
	printf("Kindly enter the filename (preferably in .txt format) to export to: ");
	scanf("%[^\n]s", expoFilename); 
	scanf("%c", &enterKey);
	
	fp = fopen(expoFilename, "w");
	
	for (i = 0; i < *numRecords; i++)
	{
		fprintf(fp, "%s\n", quizData[i].topic);
		fprintf(fp, "%d\n", quizData[i].questionNum);
		fprintf(fp, "%s\n", quizData[i].question);
		fprintf(fp, "%s\n", quizData[i].choiceOne);
		fprintf(fp, "%s\n", quizData[i].choiceTwo);
		fprintf(fp, "%s\n", quizData[i].choiceThree);
		fprintf(fp, "%s\n", quizData[i].answer);
		fprintf(fp, "\n");
	}
	fclose(fp);
	
	printf("Number of records exported: %d\n", *numRecords);
	printf("Exported sucessfully!\n");
	printf("Program will now return to manage data screen.\n");
	
	manageDataFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
}

/* quizGameFunc shows the options of the quiz game itself
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Input must be the same as the one printed
*/
void 
quizGameFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str30 playCommand;
	char enterKey;
	FILE *fp1;
	int j = 0;
	int scanResult;
	
	fp1 = fopen("score.txt", "r");
	
	if (fp1 == NULL)
	{
		*currentNumPlayers = 0;
	}
	
	while ((fp1 != NULL) && (scanResult = (fscanf(fp1 ,"%20[^\n] %d\n", playerInfo[j].playerName, &playerInfo[j].playerScore) == 2)) && (*flagScoreFile == 0))
	{
		playerInfo[j].playerNum = j + 1;
		*currentNumPlayers = *currentNumPlayers + 1;
		j++;
	}
	*flagScoreFile = 1; //To stop reading the file once this function is called again
	
	fclose(fp1);
	
	printf("Welcome player! Kindly enter a command to proceed.\n");
	printf("Available commands are Play, View scores, Exit: ");
	scanf("%[^\n]s", playCommand);
	scanf("%c", &enterKey);
	
	if ((strcmp(playCommand, "Play") == 0) || (strcmp(playCommand, "play") == 0))
	{
		system("cls");
		playFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if ((strcmp(playCommand, "View scores") == 0) || (strcmp(playCommand, "view scores") == 0))
	{
		system("cls");
		viewScores(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else if ((strcmp(playCommand, "Exit") == 0) || (strcmp(playCommand, "exit") == 0))
	{
		system("cls");
		exitGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	else 
	{
		do 
		{
			printf("Invalid command. Kindly enter a valid command.\n");
			printf("Available commands are Play, View scores, Exit: ");
			scanf("%[^\n]s", playCommand);
			scanf("%c", &enterKey);
			
			if ((strcmp(playCommand, "Play") == 0) || (strcmp(playCommand, "play") == 0))
			{
				system("cls");
				playFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
			else if ((strcmp(playCommand, "View scores") == 0) || (strcmp(playCommand, "view scores") == 0))
			{
				system("cls");
				viewScores(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
			else if ((strcmp(playCommand, "Exit") == 0) || (strcmp(playCommand, "exit") == 0))
			{
				system("cls");
				exitGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
			}
		} while ((strcmp(playCommand, "Play") != 0) && (strcmp(playCommand, "play") != 0) && (strcmp(playCommand, "View scores") != 0) 
		&& (strcmp(playCommand, "view scores") != 0) && (strcmp(playCommand, "Exit") != 0) && (strcmp(playCommand, "exit") != 0)); 
	}
}


/* latestQuestionNumber searches for the last question number within a specific topic
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param tempoTopic[] - the topic chosen to be searched
	@return the last question number a topic has
	Pre-condition: Must need to have a topic chosen
*/
int
latestQuestionNumber(struct quizRecord quizData[], int *numRecords, char tempoTopic[])
{
	int latestQuestionNum = 0;
	int j;
	
	for (j = 0; j < *numRecords; j++)
	{
		if (strcmp(quizData[j].topic, tempoTopic) == 0) //Isolated all records with same topic
		{
			latestQuestionNum = quizData[j].questionNum; //Increment every time it sees same topic
		}
	}
	
	return latestQuestionNum;
}

/* randomizerFunc generates a random integer from 1 up to the last question number within a specific topic
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param tempoTopic[] - the topic to be searched
	@return a random integer from 1 up to the last question number of a topic
	Pre-condition: Must need to have at least one record in order to access this function
*/
int 
randomizerFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, char tempoTopic[])
{
	int randomNum;
	int numItems;
	
	numItems = latestQuestionNumber(quizData, numRecords, tempoTopic); //Assign result of latestQuestionNumber to numItems
	
	srand(time(NULL));
	
	randomNum = (rand() % numItems) + 1; //Generate a random item from 1 to the last number within the topic
	
	return randomNum;
}

/* playFunc is the main quiz game function, where a player can keep selecting a topic and will generate a random question from within that topic
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to have at least 1 record
*/
void 
playFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	str30 tempoAnswer;
	str20 tempoTopic;
	str20 tempoName;
	char enterKey;
	int randQuestion;
	int currentScore = 0;
	int checker;
	int flag;
	int d, e;
	
	if (*numRecords == 0)
	{
		printf("\nThere are no records currently stored. Program will now return to main menu.\n");
		mainMenu(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
	}
	
	system("cls");
	
	printf("Enter your name: ");
	scanf("%[^\n]s", tempoName);
	scanf("%c", &enterKey);
	
	playerInfo[*currentNumPlayers].playerNum = *currentNumPlayers + 1;
	
	strcpy(playerInfo[*currentNumPlayers].playerName, tempoName);
	
	playerInfo[*currentNumPlayers].playerScore = 0;
	
	system("cls");
	
	do
	{
		flag = 0;
		printf("Please choose from the list of available topics or type ""end game"" to end game:\n");
	
		/* Print all UNIQUE topics */
		displayUniqueTopics(quizData, numRecords);
	
		/* First instance of asking for topic */
		printf("\nEnter the chosen topic: ");
		scanf("%[^\n]s", tempoTopic);
		scanf("%c", &enterKey);
				
		if ((strcmp(tempoTopic, "end game") == 0) || (strcmp(tempoTopic, "End game") == 0))
		{
			printf("End game option chosen. Program will now return to quiz game menu.\n");
			
			playerInfo[*currentNumPlayers].playerScore = currentScore;
			printf("Your current score is: %d\n", playerInfo[*currentNumPlayers].playerScore);
			
			*currentNumPlayers = *currentNumPlayers + 1;
			flag = 1;
			
			quizGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
		}
		
		checker = 5;
		
		for (e = 0; e < *numRecords; e++)
		{
			if (strcmp(tempoTopic, quizData[e].topic) == 0)
			{
				checker = 1; //Validator if topic is valid
			}
		}
		
		if (checker == 1)
		{
			randQuestion = randomizerFunc(quizData, playerInfo, numRecords, tempoTopic);
		}		
	
		/* Loop until record is found */
		for (d = 0; d < *numRecords; d++)
		{
			if ((strcmp(tempoTopic, quizData[d].topic) == 0) && (quizData[d].questionNum == randQuestion))
			{
				printf("\nCurrent Score: %d", currentScore);
				printf("\nTopic: %s\n", quizData[d].topic);
				printf("Question: %s\n", quizData[d].question);
				printf("Question Number: %d\n", quizData[d].questionNum);
				printf("Choice 1: %s\n", quizData[d].choiceOne);
				printf("Choice 2: %s\n", quizData[d].choiceTwo);
				printf("Choice 3: %s\n", quizData[d].choiceThree);
			
				printf("Enter your answer EXACTLY as SHOWN in the choices or type ""end game"" to end game: ");
				scanf("%[^\n]s", tempoAnswer);
				scanf("%c", &enterKey);
			
				if (strcmp(tempoAnswer, quizData[d].answer) == 0)
				{
					printf("Congratulations! You have earned a point! ");
					currentScore++;
				}
				else if ((strcmp(tempoAnswer, "end game") == 0) || (strcmp(tempoAnswer, "end game") == 0))
				{
					system("cls");
					
					printf("\nEnd game option chosen. ");
					playerInfo[*currentNumPlayers].playerScore = currentScore;
					
					printf("Your current score is: %d\n", playerInfo[*currentNumPlayers].playerScore);
					
					*currentNumPlayers = *currentNumPlayers + 1;
					flag = 1;
					
					quizGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
				}
				else 
				{
					printf("Sorry! Answer inputted is incorrect.\n");
				}
			}
		}
		printf("\n");
	} while ((strcmp(tempoTopic, "0") != 0) && (strcmp(tempoAnswer, "0") != 0) && flag != 1);
}

/* viewScores allows the player to see the currently available scores
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: None
*/
void 
viewScores(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	int r;
	int option;
	char enterkey;
	
	printf("CURRENT PLAYER SCORES: \n");
	
	/* Displays the scores from file */
	
	printf("ROW       PLAYER NAME         SCORES");
	printf("\n");
	
	for (r = 0; r < *currentNumPlayers + 1; r++) //Add one since new records is stored in *numRecords
	{
		if (playerInfo[r].playerNum != 0)
		{
			printf("%-10d %-20s %d\n", playerInfo[r].playerNum, playerInfo[r].playerName, playerInfo[r].playerScore);	
		}
	}
	
	printf("\nPress any number to return to quiz game menu: ");
	scanf("%d%c", &option, &enterkey);
	
	quizGameFunc(quizData, playerInfo, numRecords, currentNumPlayers, flagScoreFile);
}

/* exiitGameFunc saves all the available players and scores onto a text file 
	@param struct quizRecord quizData[] - an array structure data type containing all members needed for the record
	@param struct playerDetails playerInfo[] - an array structure data type containing all members of the player
	@param *numRecords - the current number of records the program currently has
	@param *currentNumPlayers - the current number of players recorded by the program
	@param *flagScoreFile - a pointer integer used to stop the reading of the score.txt file in quizGameFunc()
	Pre-condition: Must need to have data to store onto the file
*/
void 
exitGameFunc(struct quizRecord quizData[], struct playerDetails playerInfo[], int *numRecords, int *currentNumPlayers, int *flagScoreFile)
{
	FILE *fp;
	int w;
	
	fp = fopen("score.txt", "w");
	
	for (w = 0; w < *currentNumPlayers; w++)
	{
		fprintf(fp, "%s\n", playerInfo[w].playerName);
		fprintf(fp, "%d\n", playerInfo[w].playerScore);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

int
main()
{
	//Genaral variables to be used
	int numRecords = 0;
	int currentNumPlayers = 0;
	int flagScoreFile = 0;
	struct quizRecord quizData[MAX];
	struct playerDetails playerInfo[MAX_PLAYERS];
	
	mainMenu(quizData, playerInfo, &numRecords, &currentNumPlayers, &flagScoreFile);
	
	return 0;
}
