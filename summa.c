#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
    char *val;  // To store a sentence
    struct node *next;
} *undo = NULL, *redo = NULL, *undoTail = NULL;

int cnt = 0;

// Helper functions
void append(struct node **head, struct node **tail, const char *str) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->val = strdup(str);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

char *pop(struct node **head) {
    if (*head == NULL) return NULL;

    char *val = (*head)->val;
    struct node *temp = *head;
    *head = (*head)->next;
    free(temp);

    return val;
}

void writeText(const char *str) {
    append(&undo, &undoTail, str);
    cnt++;
    printf("Text \"%s\" written successfully!\n", str);
}

void undoAction() {
    if (undo == NULL) {
        printf("Nothing to undo.\n");
        return;
    }

    if (undo == undoTail) {
        append(&redo, &redo, undo->val);
        free(undo->val);
        free(undo);
        undo = undoTail = NULL;
    } else {
        struct node *current = undo;
        while (current->next != undoTail) {
            current = current->next;
        }

        append(&redo, &redo, undoTail->val);
        free(undoTail->val);
        free(undoTail);
        undoTail = current;
        undoTail->next = NULL;
    }

    cnt--;
    printf("Undo completed.\n");
}

void redoAction() {
    if (redo == NULL) {
        printf("Nothing to redo.\n");
        return;
    }

    struct node *nodeToRedo = redo;
    redo = redo->next;

    append(&undo, &undoTail, nodeToRedo->val);

    free(nodeToRedo->val);
    free(nodeToRedo);
    cnt++;
    printf("Redo completed.\n");
}

void readContent() {
    if (undo == NULL) {
        printf("No content to display.\n");
        return;
    }

    printf("Current content:\n");
    struct node *current = undo;
    while (current != NULL) {
        printf("%s", current->val);
        if (current->next != NULL) printf(" ");
        current = current->next;
    }
    printf("\n");
}

void saveToFile(const char *filename) {
    if (undo == NULL) {
        printf("No content to save.\n");
        return;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for saving.\n");
        return;
    }

    struct node *current = undo;
    while (current != NULL) {
        fputs(current->val, file);
        fputc('\n', file);
        current = current->next;
    }

    fclose(file);
    printf("Content saved to file '%s'.\n", filename);
}

void showMenu() {
    printf("\n-------- TEXT EDITOR MENU --------\n");
    printf("1. Write text\n");
    printf("2. Undo last action\n");
    printf("3. Redo last action\n");
    printf("4. Read content\n");
    printf("5. Save to file\n");
    printf("6. Exit\n");
    printf("----------------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char input[1000], filename[100];

    printf("Welcome to the Text Editor!\n");

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter text to write: ");
                getchar();  // Clear the newline from the input buffer
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                writeText(input);
                break;
            case 2:
                undoAction();
                break;
            case 3:
                redoAction();
                break;
            case 4:
                readContent();
                break;
            case 5:
                printf("Enter filename to save content: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 6:
                printf("Exiting the text editor. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}