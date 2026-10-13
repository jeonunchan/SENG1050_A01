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



void printList(struct FlightNode* head);
void freeList(struct FlightNode* head);
struct FlightNode* createNewNode(char* destination, char* date, float fare);
struct FlightNode* findFlight(struct FlightNode *head, char *destination, char *date);
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail);
void insertByDestination(struct FlightNode **head, struct FlightNode **tail, char *destination, char *date, float fare);
void insertByFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);



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

void printList(struct FlightNode* head)
{
	struct FlightNode* current = head;
	while (current != NULL) 
	{
		printf("%-15s%-10s%f\n", current->flight.destination, current->flight.date, current->flight.fare);

		current = current->next;
	}
}

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

int main(void)
{
	struct FlightNode* fareHead = NULL;
	struct FlightNode* fareTail = NULL;
	struct FlightNode* destinationHead = NULL;
	struct FlightNode* destinationTail = NULL;
	float fareInput;

	char destinationBuffer[100];
	char dateBuffer[100];


	while (1)
	{
		if (fgets(destinationBuffer, sizeof(destinationBuffer), stdin) == NULL)
		{
			break;
		}

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

		if (strcmp(destinationBuffer, ".") == 0)
		{
			break;
		}


		if (fgets(dateBuffer, sizeof(dateBuffer), stdin) == NULL)
		{
			break;
		}

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

		if (strcmp(dateBuffer, ".") == 0)
		{
			break;
		}


		if (scanf("%f", &fareInput) != 1)
		{
			break;
		}

		while (getchar() != '\n');

		insertByDestination(&destinationHead, &destinationTail, destinationBuffer, dateBuffer, fareInput);
		insertByFare(&fareHead, &fareTail, destinationBuffer, dateBuffer, fareInput);

	}

	printList(fareHead);
	printList(destinationHead);


	char findDestination[100];
	char findDate[100];

	if (fgets(findDestination, sizeof(findDestination), stdin) != NULL && fgets(findDate, sizeof(findDate), stdin) != NULL)
	{
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

		struct FlightNode* matchNode = findFlight(destinationHead, findDestination, findDate);

		if (matchNode != NULL)
		{
			float oldFare = matchNode->flight.fare;
			float newFare;

			printf("Current fare: %f\n", oldFare);
			if (scanf("%f", &newFare) == 1)
			{
				if (newFare == oldFare)
				{
					printf("Fare is unchanged.\n");
				}
				else
				{
					matchNode->flight.fare = newFare;

					struct FlightNode* fareNodeUpdate = findFlight(fareHead, findDestination, findDate);
					if (fareNodeUpdate != NULL)
					{
						deleteNode(fareNodeUpdate, &fareHead, &fareTail);
						insertByFare(&fareHead, &fareTail, findDestination, findDate, newFare);
					}
				}
			}
			while (getchar() != '\n');
		}
		else 
		{
			printf("There is not an exact match.\n");
		}

	}

	printList(fareHead);
	printList(destinationHead);

	freeList(fareHead);
	freeList(destinationHead);

	return 0;
}