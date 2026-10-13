/*
FILE            :   Assignment1.c
PROJECT         :   SENG1050_A01
PROGRAMMER      :   Unchan Jeon
FIRST VERSION   :   2026-10-12
DESCRIPTION     :
	The functions in this file are used to get flight information from user input and display it after sorting by fare and destination. Additionally, user can update flight fares.
	Managed via Git repository.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct FlightInfo {
	char *destination;
	char *date;
	float fare;
};

typedef struct FlightNode {
	struct FlightInfo flight;
	struct FlightNode* prev;
	struct FlightNode* next;
};


//	Function prototypes
void printList(struct FlightNode* head);
void freeList(struct FlightNode* head);
struct FlightNode* createNewNode(char* destination, char* date, float fare);
struct FlightNode* findFlight(struct FlightNode *head, char *destination, char *date);
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail);
void insertByDestination(struct FlightNode **head, struct FlightNode **tail, char *destination, char *date, float fare);
void insertByFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);


//	Declaration of functions

//  FUNCTION        :   createNewNode
//  DESCRIPTION     :
//      This function creates new node to insert flight information into the sorted list.
//  PARAMETERS      :
//      char*	destination
//		char*	date
//		float	fare
//  RETURNS         :
//      struct FlightNode* newNode
struct FlightNode* createNewNode(char* destination, char* date, float fare)
{
	struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));

	if (newNode == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newNode->flight.destination = (char*)malloc(strlen(destination) + 1);
	newNode->flight.date = (char*)malloc(strlen(date) + 1);
	
	if (newNode->flight.destination == NULL || newNode->flight.date == NULL)
	{
		exit(EXIT_FAILURE);
	}

	strcpy(newNode->flight.destination, destination);
	strcpy(newNode->flight.date, date);
	newNode->flight.fare = fare;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

//  FUNCTION        :   findFlight
//  DESCRIPTION     :
//      This function find flight information if it is in the list.
//  PARAMETERS      :
//      struct FlightNode*	head
//		char*				destination
//		char*				date
//  RETURNS         :
//      current (If flight information found) / NULL (If not found)
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date)
{
	struct FlightNode* current = head;
	while (current != NULL)
	{
		if (strcmp(current->flight.destination, destination) == 0 && strcmp(current->flight.date, date) == 0)
		{
			return current;
		}

		current = current->next;
	}

	return NULL;
}

//  FUNCTION        :   deleteNode
//  DESCRIPTION     :
//      This function deletes flight information before updating fare
//  PARAMETERS      :
//      struct FlightNode*	node
//		struct FlightNode**	head
//		struct FlightNode** tail
//  RETURNS         :
//      NONE
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail)
{
	if (node == NULL)
	{
		return;
	}

	if (node == *head)
	{
		*head = node->next;
	}
	if (node == *tail)
	{
		*tail = node->prev;
	}

	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}

	free(node->flight.destination);
	free(node->flight.date);
	free(node);
}

//  FUNCTION        :   insertByDestination
//  DESCRIPTION     :
//      This function inserts flight information to the list sorted by destination.
//  PARAMETERS      :
//      struct FlightNode** head
//		struct FlightNode** tail
//		char*	destination
//		char*	date
//		float	fare
//  RETURNS         :
//      NONE
void insertByDestination(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare)
{
	struct FlightNode* newNode = createNewNode(destination, date, fare);

	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		return;
	}

	struct FlightNode* current = *head;

	while (current != NULL && strcmp(current->flight.destination, newNode->flight.destination) <= 0)
	{
		current = current->next;
	}

	if (current == *head)
	{
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
	else if (current == NULL)
	{
		newNode->prev = *tail;
		(*tail)->next = newNode;
		*tail = newNode;
	}
	else
	{
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

//  FUNCTION        :   insertByFare
//  DESCRIPTION     :
//      This function inserts flight information to the list sorted by fare.
//  PARAMETERS      :
//      struct FlightNode** head
//		struct FlightNode** tail
//		char*	destination
//		char*	date
//		float	fare
//  RETURNS         :
//      NONE
void insertByFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare)
{
	struct FlightNode* newNode = createNewNode(destination, date, fare);

	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		return;
	}

	struct FlightNode* current = *head;

	while (current != NULL && current->flight.fare <= newNode->flight.fare)
	{
		current = current->next;
	}

	if (current == *head)
	{
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
	else if (current == NULL)
	{
		newNode->prev = *tail;
		(*tail)->next = newNode;
		*tail = newNode;
	}
	else
	{
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

//  FUNCTION        :   printList
//  DESCRIPTION     :
//      This function displays formatted flight information list.
//  PARAMETERS      :
//      struct FlightNode* head
//  RETURNS         :
//      NONE
void printList(struct FlightNode* head)
{
	struct FlightNode* current = head;
	while (current != NULL) 
	{
		printf("%-15s%-10s%f\n", current->flight.destination, current->flight.date, current->flight.fare);

		current = current->next;
	}
}

//  FUNCTION        :   freeList
//  DESCRIPTION     :
//      This function frees list before exit program
//  PARAMETERS      :
//      struct FlightNode* head
//  RETURNS         :
//      NONE
void freeList(struct FlightNode* head)
{
	struct FlightNode* current = head;
	struct FlightNode* temp;

	while (current != NULL)
	{
		temp = current->next;
		free(current->flight.destination);
		free(current->flight.date);
		free(current);
		current = temp;
	}
}

//	Main program starts here
int main(void)
{
	struct FlightNode* fareHead = NULL;
	struct FlightNode* fareTail = NULL;
	struct FlightNode* destinationHead = NULL;
	struct FlightNode* destinationTail = NULL;
	float fareInput;

	char destinationBuffer[100];
	char dateBuffer[100];

	//	Flight information input loop
	while (1)
	{
		//	Get flight destination from user input, and exit if user input is null.
		if (fgets(destinationBuffer, sizeof(destinationBuffer), stdin) == NULL)
		{
			break;
		}

		//	Find new line character and replace it to '\0'
		int i = 0;
		while (destinationBuffer[i] != '\0')
		{
			if (destinationBuffer[i] == '\n')
			{
				destinationBuffer[i] = '\0';
				break;
			}
			i++;
		}

		//	If user enters ".", break the loop
		if (strcmp(destinationBuffer, ".") == 0)
		{
			break;
		}

		//	Get flight date from user input, and exit if user input is null.
		if (fgets(dateBuffer, sizeof(dateBuffer), stdin) == NULL)
		{
			break;
		}

		//	Find new line character and replace it to '\0'
		int j = 0;
		while (dateBuffer[j] != '\0')
		{
			if (dateBuffer[j] == '\n')
			{
				dateBuffer[j] = '\0';
				break;
			}
			j++;
		}

		//	If user enters ".", break the loop.
		if (strcmp(dateBuffer, ".") == 0)
		{
			break;
		}

		//	Get flight fare from user input, and exit if user input is not float value.
		if (scanf("%f", &fareInput) != 1)
		{
			break;
		}

		//	Clean buffer
		while (getchar() != '\n');

		//	Insert flight information into the list sorted by destination.
		insertByDestination(&destinationHead, &destinationTail, destinationBuffer, dateBuffer, fareInput);
		//	Insert flight information into the list sorted by fare.
		insertByFare(&fareHead, &fareTail, destinationBuffer, dateBuffer, fareInput);

	}

	//	Display the list sorted by fare.
	printList(fareHead);
	//	Display the list sorted by destination.
	printList(destinationHead);


	char findDestination[100];
	char findDate[100];

	//	Get flight information user want to update the fare.
	if (fgets(findDestination, sizeof(findDestination), stdin) != NULL && fgets(findDate, sizeof(findDate), stdin) != NULL)
	{
		//	Find new line character from destination input and replace it to '\0'
		int k = 0;
		while (findDestination[k] != '\0')
		{
			if (findDestination[k] == '\n')
			{
				findDestination[k] = '\0';
				break;
			}
			k++;
		}
		//	Find new line character from date input and replace it to '\0'
		int l = 0;
		while (findDate[l] != '\0')
		{
			if (findDate[l] == '\n')
			{
				findDate[l] = '\0';
				break;
			}
			l++;
		}

		//	Find flight information in the list
		struct FlightNode* matchNode = findFlight(destinationHead, findDestination, findDate);

		//	If flight information is matched
		if (matchNode != NULL)
		{
			float oldFare = matchNode->flight.fare;
			float newFare;

			//	Display current fare
			printf("Current fare: %f\n", oldFare);
			
			//	Check new fare from user input is float value
			if (scanf("%f", &newFare) == 1)
			{
				//	If new fare is same with the original fare, inform user
				if (newFare == oldFare)
				{
					printf("Fare is unchanged.\n");
				}
				//	If new fare is different from the original fare, update fare
				else
				{
					matchNode->flight.fare = newFare;

					struct FlightNode* fareNodeUpdate = findFlight(fareHead, findDestination, findDate);
					if (fareNodeUpdate != NULL)
					{
						//	Delete node with original fare
						deleteNode(fareNodeUpdate, &fareHead, &fareTail);
						//	Insert node with new fare into sorted lists.
						insertByFare(&fareHead, &fareTail, findDestination, findDate, newFare);
					}
				}
			}
			//	Clean buffer
			while (getchar() != '\n');
		}
		//	If flight information is not matched, inform user
		else 
		{
			printf("There is not an exact match.\n");
		}

	}

	//	Display the list sorted by fare.
	printList(fareHead);
	//	Display the list sorted by destination.
	printList(destinationHead);


	//	Free lists
	freeList(fareHead);
	freeList(destinationHead);

	return 0;
}