#include <stdio.h>
#include <string.h>
#include <conio.h> /* For the password input https://www.scaler.com/topics/getch-in-c/ */ 
#include <stdlib.h> /* For the clearing of console https://www.grepper.com/answers/183836/clear+screen+c */
#include <time.h> /* For the randomizer function https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm*/
#define MAX 50
#define MAX_PLAYERS 100

typedef char str20[21];
typedef char str30[31];
typedef char str50[51];
typedef char str150[151];

struct quizRecord {
	str20 topic;
	int questionNum;
	str150 question;
	str30 choice_one;
	str30 choice_two;
	str30 choice_three;
	str30 answer;
};

struct playerDetails{
	int playerNum;
	str20 playerName;
	int playerScore;
};

void 
addRecord(struct quizRecord quiz_records[], int *numRecords, int latestQuestionNum)
{
	int i, j;
	str150 tempQuestion;
	str30 tempAnswer;
	int result = 1;
	char enterKey;
	
	if (*numRecords == MAX)
	{
		printf("Records is full. Kindly delete a record before adding a function.\n");
		printf("Program will now return to manage data screen.");	
		
		//manageDataFunc(&numRecords);
		printf("stub");
	}
	
	printf("Enter a question or go back to manage data: ");
	scanf("%[^\n]s\n", tempQuestion);
	scanf("%c", &enterKey);
	
	if (strcmp(tempQuestion, "manage data") == 0)
	{
		//manageDataFunc(&numRecords);
			printf("stub");
	}
	
	printf("Enter the answer to the question or go back to manage data: ");
	scanf("%[^\n]s\n", tempAnswer);
	scanf("%c", &enterKey);

	if (strcmp(tempAnswer, "manage data") == 0)
	{
		//manageDataFunc(&numRecords);
			printf("stub");
	}	
	
	for (i = 0; i < MAX && result != 0; i++)
	{
		if (strcmp(quiz_records[i].question, tempQuestion) == 0 && strcmp(quiz_records[i].answer, tempAnswer) == 0)
		{
			printf("The added question and answer is already listed. Program will now go back to manage data screen.");
			//manageDataFunc(&numRecords);
			result = 0;
		}	
	}
	
	if (result == 1)
	{
		strcpy(quiz_records[*numRecords].question, tempQuestion);
		strcpy(quiz_records[*numRecords].answer, tempAnswer);
		
		printf("Enter the topic of the question: ");
		scanf("%[^\n]s", quiz_records[*numRecords].topic);
		scanf("%c", &enterKey);
		
		printf("Enter the first choice: ");
		scanf("%[^\n]s", quiz_records[*numRecords].choice_one);
		scanf("%c", &enterKey);
		
		printf("Enter the second choice: ");
		scanf("%[^\n]s", quiz_records[*numRecords].choice_two);
		scanf("%c", &enterKey);
		
		printf("Enter the third choice: ");
		scanf("%[^\n]s", quiz_records[*numRecords].choice_three);
		scanf("%c", &enterKey);
		
		latestQuestionNum = 1; //First record of a topic
		
		/* Automatically assigning question number */
		for (j = 0; j <= *numRecords; j++)
		{
			if (strcmp(quiz_records[j].topic, quiz_records[*numRecords].topic) == 0) //Isolated all records with same topic
			{
				latestQuestionNum++; //Increment every time it sees same topic including the new record
			}
		}
		quiz_records[*numRecords].questionNum = latestQuestionNum; //Add one for the new question number including added record
		
		*numRecords = *numRecords + 1;
		
		//manageDataFunc(&numRecords);
		printf("stub");
	}
	printf("%d", *numRecords);
}

int main()
{
	int numRecords = 0;
	struct quizRecord quiz_records[MAX];
	int latestQuestionNum = 0;
	
	addRecord(quiz_records, &numRecords, latestQuestionNum);
	
	printf("\n%d", numRecords);
		
	return 0;
}
