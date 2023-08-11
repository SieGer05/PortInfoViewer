#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int portNumber;
    char name[50];
    char type[50];
    char description[100];
    char category[50];
} PortInfo;

typedef struct Node {
    PortInfo portInfo;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(PortInfo portInfo);
Node* insertNode(Node* root, PortInfo portInfo);
PortInfo* searchPort(Node* root, int portNumber);
void freeTree(Node* root);
void printHeader();
void printLine(char c, int number);

int main() {
    Node* root = NULL;
    FILE* file = fopen("ports.txt", "r");

    if (file == NULL) {
        perror("\nERROR! FAILED TO OPEN FILE!");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        PortInfo portInfo;
        // Parse the input line and populate the PortInfo structure
        sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &portInfo.portNumber,
               portInfo.name,
               portInfo.type,
               portInfo.description,
               portInfo.category);
        // Insert the port information into the binary search tree
        root = insertNode(root, portInfo);
    }

    fclose(file);

    char choice;
    int userInput;
    do {
        system("cls");
	//For Linux machine Uncheck system("clear").
	//system("clear");
        printHeader();
        printf("\n-> PLEASE ENTER A PORT NUMBER.> ");
        scanf("%d", &userInput);

        PortInfo* foundPort = searchPort(root, userInput);
        if (foundPort) {
            printf("\n   #FOUND INFORMATION:\n");
            printf("- PORT NUMBER: %d\n", foundPort->portNumber);
            printf("- NAME: %s\n", foundPort->name);
            printf("- TYPE: %s\n", foundPort->type);
            printf("- DESCRIPTION: %s\n", foundPort->description);
            printf("- CATEGORY: %s\n", foundPort->category);
        } else {
            printf("PORT NOT FOUND!\n");
            // Exit the loop if the port is not found
            //exit(1);
        }
        printf("\nTo continue, enter (Y). To exit, enter (N).> ");
        scanf(" %c", &choice);
    } while (choice != 'N' && choice != 'n');

    // Free the memory allocated for the binary search tree
    freeTree(root);
    system("pause");
    return 0;
}

// Create a new node for the binary search tree
Node* createNode(PortInfo portInfo) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("\nERROR! MEMORY ALLOCATION FAILED!");
        exit(1);
    }
    newNode->portInfo = portInfo;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a node into the binary search tree
Node* insertNode(Node* root, PortInfo portInfo) {
    if (root == NULL) {
        return createNode(portInfo);
    }

    if (portInfo.portNumber < root->portInfo.portNumber) {
        root->left = insertNode(root->left, portInfo);
    } else if (portInfo.portNumber > root->portInfo.portNumber) {
        root->right = insertNode(root->right, portInfo);
    }

    return root;
}

// Search for a port in the binary search tree
PortInfo* searchPort(Node* root, int portNumber) {
    if (root == NULL || root->portInfo.portNumber == portNumber) {
        return root == NULL ? NULL : &(root->portInfo);
    }

    if (portNumber < root->portInfo.portNumber) {
        return searchPort(root->left, portNumber);
    } else {
        return searchPort(root->right, portNumber);
    }
}

// Free the memory allocated for the binary search tree
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Print the header of the program
void printHeader() {
    printf("\033[32m");
    printLine('-', 52);
    printf("  _____   _    ______    _____    ______    ____  \n");
    printf(" / ____| (_)  |  ____|  / ____|  |  ____|  |  _ \\ \n");
    printf("| (___   | |  | |__    | |  __   | |__  |  |_) |\n");
    printf(" \\___ \\  | |  |  __|   | | |_ |  |  __|    |  _ < \n");
    printf(" ____) | |_|  | |____  | |__| |  | |____   | | \\ \\\n");
    printf("|_____/  (_)  |______|  \\_____|  |______|  |_|  \\_\\ \n");
    printf("\033[0m");

    printf("\033[31m");
    printf("                                         version 1.0\n");
    printf("\033[0m");
    printf("\033[32m");
    printLine('-', 52);
    printf("\033[0m");
}

// Print a line of characters
void printLine(char c, int number) {
    printf("+");
    for (int i = 0; i < number; i++)
        printf("%c", c);
    printf("+\n");
}
