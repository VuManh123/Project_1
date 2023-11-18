#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000
#define MAX_CITIZENS 1500000

int birthCount[MAX_CITIZENS]; // So luong sinh  
int cumulativeBirthCount[MAX_CITIZENS]; // Tong so luong sinh

struct PersonInfo {
    char code[8];
    int dob;
    char father[8];
    char mother[8];
    int aliveStatus;
    char regionCode[8];
};

struct LinkedListNode {
    struct PersonInfo person;
    struct LinkedListNode *next;
};

struct LinkedListNode *head[HASH_SIZE];

// Function prototypes
int convertDateStrToInt(const char *dateStr);
void initializeHashTable();
int hashString(const char *str);
struct LinkedListNode *createNode(struct PersonInfo person);
struct LinkedListNode *insertNode(struct LinkedListNode *node, struct LinkedListNode *newNode);
int countPeopleBornOnDate(char *date);
int findMaxAncestorDepth(char *code);
int countPeopleBornBetweenDates(char *date1, char *date2);
struct LinkedListNode *findPersonNode(char *code);

// Function to create a new PersonInfo
struct PersonInfo initializePerson(char *code, int dob, char *father, char *mother) {
    struct PersonInfo newPerson;
    strcpy(newPerson.code, code);
    newPerson.dob = dob;
    strcpy(newPerson.father, father);
    strcpy(newPerson.mother, mother);
    return newPerson;
}

// Function to convert a date string to an integer representation
int convertDateStrToInt(const char *dateStr) {
    int year, month, day;
    sscanf(dateStr, "%d-%d-%d", &year, &month, &day);
    return year * 365 + month * 30 + day;
}

// Initialize the hash table
void initializeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        head[i] = NULL;
    }
}

// Hash function for strings
int hashString(const char *str) {
    int hash = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        hash = (hash * 31 + str[i]) % HASH_SIZE;
    }

    return hash;
}

// Create a new node with the given PersonInfo
struct LinkedListNode *createNode(struct PersonInfo person) {
    struct LinkedListNode *newNode = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode));
    if (newNode) {
        newNode->person = person;
        newNode->next = NULL;
    }
    return newNode;
}

// Insert a new node into the linked list
struct LinkedListNode *insertNode(struct LinkedListNode *node, struct LinkedListNode *newNode) {
    if (newNode == NULL) {
        return node;
    }

    newNode->next = node;
    return newNode;
}

// Count the number of people born on a given date
int countPeopleBornOnDate(char *date) {
    return birthCount[convertDateStrToInt(date)];
}

// Find the depth of the most alive ancestor for a given person code
int findMaxAncestorDepth(char *code) {
    struct LinkedListNode *current = head[hashString(code)];
    int maxDepth = 0;

    while (current) {
        if (strcmp(code, current->person.code) == 0) {
            int fatherDepth = -1;
            int motherDepth = -1;

            if (strcmp(current->person.father, "0000000") != 0) {
                fatherDepth = findMaxAncestorDepth(current->person.father) + 1;
            }

            if (strcmp(current->person.mother, "0000000") != 0) {
                motherDepth = findMaxAncestorDepth(current->person.mother) + 1;
            }

            int ancestorDepth = (fatherDepth > motherDepth) ? fatherDepth : motherDepth;

            if (ancestorDepth > maxDepth) {
                maxDepth = ancestorDepth;
            }
        }
        current = current->next;
    }

    return maxDepth;
}

// Count the number of people born between two dates
int countPeopleBornBetweenDates(char *date1, char *date2) {
    int count = cumulativeBirthCount[convertDateStrToInt(date2)] - cumulativeBirthCount[convertDateStrToInt(date1)] +
                birthCount[convertDateStrToInt(date1)];
    return count;
}

// Search for a person with the given code in the hash table
struct LinkedListNode *findPersonNode(char *code) {
    struct LinkedListNode *current = head[hashString(code)];

    if (current == NULL) {
        return NULL;
    }

    if (strcmp(current->person.code, "0000000") == 0) {
        return NULL;
    }

    while (current != NULL) {
        if (strcmp(current->person.code, code) == 0 || strcmp(current->person.father, code) == 0 ||
            strcmp(current->person.mother, code) == 0) {
            return current;
        }
        current = current->next;
    }

    return current;
}

int main() {
    initializeHashTable();
    int totalPeople = 0;
    int maxUnrelatedCount = 0;

    for (int i = 0; i < MAX_CITIZENS; i++) {
        birthCount[i] = 0;
        cumulativeBirthCount[i] = 0;
    }

    while (1) {
        char code[10];
        if (scanf("%s", code) == EOF || strcmp(code, "*") == 0) {
            break;
        }

        char dob[15], father[10], mother[10], aliveStatus, regionCode[10];

        scanf("%s %s %s %c %s", dob, father, mother, &aliveStatus, regionCode);

        int date = convertDateStrToInt(dob);
        struct PersonInfo newPerson = initializePerson(code, date, father, mother);

        struct LinkedListNode *fatherNode = findPersonNode(father);
        struct LinkedListNode *motherNode = findPersonNode(mother);
        struct LinkedListNode *node = findPersonNode(code);

        if (fatherNode == NULL && motherNode == NULL && node == NULL) {
            maxUnrelatedCount++;
        }

        head[hashString(code)] = insertNode(head[hashString(code)], createNode(newPerson));
        birthCount[date]++;
        totalPeople++;
    }

    for (int i = 1; i < MAX_CITIZENS; i++) {
        cumulativeBirthCount[i] += cumulativeBirthCount[i - 1] + birthCount[i];
    }

    while (1) {
        char command[100];
        if (scanf("%s", command) == EOF || strcmp(command, "***") == 0) {
            break;
        } else if (strcmp(command, "NUMBER_PEOPLE") == 0) {
            printf("%d\n", totalPeople);
        } else if (strcmp(command, "NUMBER_PEOPLE_BORN_AT") == 0) {
            char date[15];
            scanf("%s", date);
            int number = countPeopleBornOnDate(date);
            printf("%d\n", number);
        } else if (strcmp(command, "MOST_ALIVE_ANCESTOR") == 0) {
            char code[10];
            scanf("%s", code);
            int maxAlive = findMaxAncestorDepth(code);
            printf("%d\n", maxAlive);
            continue;
        } else if (strcmp(command, "NUMBER_PEOPLE_BORN_BETWEEN") == 0) {
            char fromDateStr[50], toDateStr[50];
            scanf("%s %s", fromDateStr, toDateStr);
            int number = countPeopleBornBetweenDates(fromDateStr, toDateStr);
            printf("%d\n", number);
        } else if (strcmp(command, "MAX_UNRELATED_PEOPLE") == 0) {
            printf("%d\n", maxUnrelatedCount > totalPeople / 2 ? maxUnrelatedCount : totalPeople - maxUnrelatedCount);
        }
    }

    return 0;
}

