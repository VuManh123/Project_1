#include <stdio.h>
#include <string.h>
#define MAX_PERSONS 10001

struct FamilyTree {
    char child[MAX_PERSONS][50];
    char parent[MAX_PERSONS][50];
    int numDescendants[MAX_PERSONS];
    int generation[MAX_PERSONS];
    int numPersons;
};

void initFamilyTree(struct FamilyTree* tree) {
    for (int i = 0; i < MAX_PERSONS; i++) {
        tree->numDescendants[i] = 0;
        tree->generation[i] = -1;
    }
    tree->numPersons = 0;
}

void addPerson(struct FamilyTree* tree, const char* child, const char* parent) {
    strcpy(tree->child[tree->numPersons], child);
    strcpy(tree->parent[tree->numPersons], parent);
    tree->numPersons++;
}

int getDescendants(struct FamilyTree* tree, const char* name) {
    int totalDescendants = 0;
    for (int i = 0; i < tree->numPersons; i++) {
        if (strcmp(tree->parent[i], name) == 0) {
            totalDescendants += 1 + getDescendants(tree, tree->child[i]);
        }
    }
    tree->numDescendants[tree->numPersons] = totalDescendants;
    return totalDescendants;
}

int getGenerations(struct FamilyTree* tree, const char* name) {
    int maxGeneration = 0;
    for (int i = 0; i < tree->numPersons; i++) {
        if (strcmp(tree->parent[i], name) == 0) {
            int generation = 1 + getGenerations(tree, tree->child[i]);
            maxGeneration = (generation > maxGeneration) ? generation : maxGeneration;
        }
    }
    tree->generation[tree->numPersons] = maxGeneration;
    return maxGeneration;
}

int main() {
    struct FamilyTree tree;
    initFamilyTree(&tree);

    char input[50];
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "***") == 0) {
            break;
        }
        char parent[50];
        scanf("%s", parent);
        addPerson(&tree, input, parent);
    }

    while (1) {
        scanf("%s", input);
        if (strcmp(input, "***") == 0) {
            break;
        }
        char name[50];
        scanf("%s", name);
        if (strcmp(input, "descendants") == 0) {
            int descendants = getDescendants(&tree, name);
            printf("%d\n", descendants);
        } else if (strcmp(input, "generation") == 0) {
            int generations = getGenerations(&tree, name);
            printf("%d\n", generations);
        }
    }

    return 0;
}
