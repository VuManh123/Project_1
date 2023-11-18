#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 1000
#define TIME_PERIOD (24 * 3600)
#define MAX_STR_LEN 50

int numSubPeriod[TIME_PERIOD];
int totalSubPeriod[TIME_PERIOD];

struct Sub {
    char uid[10]; // User 
    char pid[10]; // Problems
    int tstamp; // Time sub
    int status; // ERR or OK
    int pt; 
};

struct Sub createSub(char* uid, char* pid, int tstamp, char *status, int pt) {
    struct Sub newSub;
    strcpy(newSub.uid, uid);
    strcpy(newSub.pid, pid);
    newSub.tstamp = tstamp;
    newSub.status = strlen(status) == 2 ? 1 : 0;
    newSub.pt = pt;
    return newSub;
}

struct Node {
    struct Sub sub;
    struct Node *next;
};

struct Point {
    char uid[10];
    char pid[10];
    int pt;
};

struct NodePoint {
    struct Point pt;
    struct NodePoint *next;
};

struct Node *htable[1000];
struct NodePoint *htablePt[1000];

int hashStr(char* str) {
    int hash = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        hash = (hash * 31 + str[i]) % 1000;
    }

    return hash;
}

void initHashTable() {
    for (int i = 0; i < 1000; i++) {
        htable[i] = NULL;
    }
}

void initHashTablePt() {
    for (int i = 0; i < 1000; i++) {
        htablePt[i] = NULL;
    }
}

struct Node* createNode(struct Sub sub) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->sub = sub;
        newNode->next = NULL;
    }
    return newNode;
}

struct Node* insertNode(struct Node* head, struct Node* newNode) {
    if (newNode == NULL) {
        return head;
    }

    newNode->next = head;
    return newNode;
}

// Luu point cua nguoi dung voi problem 
struct Point createPt(char* uid, char* pid, int pt) {
    struct Point newPt;
    strcpy(newPt.uid, uid);
    strcpy(newPt.pid, pid);
    newPt.pt = pt;
    return newPt;
}

struct NodePoint* createNodePt(struct Point pt) {
    struct NodePoint* newNode = (struct NodePoint*)malloc(sizeof(struct NodePoint));
    if (newNode) {
        newNode->pt = pt;
        newNode->next = NULL;
    }
    return newNode;
}

struct NodePoint* insertNodePt(struct NodePoint* head, struct NodePoint* newNode) {
    if (newNode == NULL) {
        return head;
    }

    newNode->next = head;
    return newNode;
}

int convertToSec(const char* timeStr) {
    int hr, min, sec;
    sscanf(timeStr, "%d:%d:%d", &hr, &min, &sec);
    return hr * 3600 + min * 60 + sec;
}

int numErrOfUser(char* uid) {
    int number = 0;
    struct Node* curr = htable[hashStr(uid)];

    while (curr != NULL) {
        if (strcmp(curr->sub.uid, uid) == 0 && curr->sub.status == 0) {
            number++;
        }
        curr = curr->next;
    }
    return number;
}

int totalPtOfUser(char* uid) {
    int totalPt = 0;
    struct NodePoint* curr = htablePt[hashStr(uid)];

    while (curr != NULL) {
        if (strcmp(curr->pt.uid, uid) == 0) {
            totalPt += curr->pt.pt;
        }
        curr = curr->next;
    }

    return totalPt;
}

int numSubInPeriod(int fromTime, int toTime) {
    int number = 0;
    number = totalSubPeriod[toTime] - totalSubPeriod[fromTime] + numSubPeriod[fromTime];
    return number;
}

struct NodePoint *searchNodePt(char *uid, char *pid) {
    struct NodePoint* curr = htablePt[hashStr(uid)];

    while (curr != NULL) {
        if (strcmp(curr->pt.uid, uid) == 0 && strcmp(curr->pt.pid, pid) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    
    return curr;
}

void checkMaxPt(char *uid, char *pid, int pt) {
    struct NodePoint* curr = searchNodePt(uid, pid);

    if (curr == NULL) {
        struct Point newPt = createPt(uid, pid, pt);
        htablePt[hashStr(uid)] = insertNodePt(htablePt[hashStr(uid)], createNodePt(newPt));
        return;
    }

    if (pt > curr->pt.pt) {
        curr->pt.pt = pt;
    }
}

int main() {
    initHashTable();
    initHashTablePt();
    int totalNumSubs = 0;
    int numErrSub = 0;

    for (int i = 0; i < 24 * 3600; i++) {
        numSubPeriod[i] = 0;
        totalSubPeriod[i] = 0;
    }

    while (1) {
        char uid[10];
        if (scanf("%s", uid) == EOF) {
            break;
        }

        if (strcmp(uid, "#") == 0) {
            break;
        }

        char pid[10], timeStr[50], err[10];
        int pt;
        scanf("%s %s %s %d", pid, timeStr, err, &pt);

        int tstamp = convertToSec(timeStr);
        struct Sub newSub = createSub(uid, pid, tstamp, err, pt);
        numSubPeriod[tstamp]++;
        htable[hashStr(uid)] = insertNode(htable[hashStr(uid)], createNode(newSub));

        if (strlen(err) == 2) {
            checkMaxPt(uid, pid, pt);
        } else {
            numErrSub++;
        }
        totalNumSubs++;
    }

    for (int i = 1; i < 24 * 3600; i++) {
        totalSubPeriod[i] += totalSubPeriod[i - 1] + numSubPeriod[i];
    }
    while (1) {
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "#") == 0) {
            break;
        } else if (strcmp(command, "?total_number_submissions") == 0) {
            printf("%d\n", totalNumSubs);
        } else if (strcmp(command, "?number_error_submision") == 0) {
            printf("%d\n", numErrSub);
        } else if (strcmp(command, "?number_error_submision_of_user") == 0) {
            char uid[10];
            scanf("%s", uid);
            int numErr = numErrOfUser(uid);
            printf("%d\n", numErr);
        } else if (strcmp(command, "?total_point_of_user") == 0) {
            char uid[10];
            scanf("%s", uid);
            int totalPtUser = totalPtOfUser(uid);
            printf("%d\n", totalPtUser);
        } else if (strcmp(command, "?number_submission_period") == 0) {
            char fromTimeStr[50], toTimeStr[50];
            scanf("%s %s", fromTimeStr, toTimeStr);
            int fromTime = convertToSec(fromTimeStr);
            int toTime = convertToSec(toTimeStr);
            int numInPeriod = numSubInPeriod(fromTime, toTime);
            printf("%d\n", numInPeriod);
        }
    }   
    return 0;
}

