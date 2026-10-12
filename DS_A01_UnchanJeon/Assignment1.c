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
void insertByDestination();
void insertByFare();


int main(void)
{



	return 0;
}