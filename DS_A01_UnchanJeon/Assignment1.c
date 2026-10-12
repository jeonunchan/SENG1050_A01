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
		printf("Error: No Memory");
		exit(EXIT_FAILURE);
	}

	newNode->flight.destination = (char*)malloc(strlen(destination) + 1);
	newNode->flight.date = (char*)malloc(strlen(date) + 1);

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
		*head == node->next;
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

	while (current != NULL && strcmp(current->flight.destination, newNode->flight.destination) < 0)
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

	while (1)
	{
		// input data loop
	}

	printList(fareHead);
	printList(destinationHead);

	// search and update(delete and create) process

	printList(fareHead);
	printList(destinationHead);

	freeList(fareHead);
	freeList(destinationHead);

	return 0;
}