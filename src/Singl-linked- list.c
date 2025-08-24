#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Submission {
    int studentID;
    char title[50];
    char date[15];
    char status[15];
    struct Submission *next;
} Submission;

Submission *head = NULL;

Submission* createNode(int id, char *title, char *date, char *status) {
    Submission *newNode = (Submission*) malloc(sizeof(Submission));
    newNode->studentID = id;
    strcpy(newNode->title, title);
    strcpy(newNode->date, date);
    strcpy(newNode->status, status);
    newNode->next = NULL;
    return newNode;
}

void insertSubmission(int id, char *title, char *date, char *status) {
    Submission *newNode = createNode(id, title, date, status);
    if (head == NULL) {
        head = newNode;
    } else {
        Submission *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("Submission added successfully.\n");
}

void updateStatus(int id, char *title, char *newStatus) {
    Submission *temp = head;
    while (temp != NULL) {
        if (temp->studentID == id && strcmp(temp->title, title) == 0) {
            strcpy(temp->status, newStatus);
            printf("Status updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Submission not found.\n");
}

void searchByID(int id) {
    Submission *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->studentID == id) {
            printf("\nStudent ID: %d\nTitle: %s\nDate: %s\nStatus: %s\n",
                   temp->studentID, temp->title, temp->date, temp->status);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) printf("No submission found for Student ID %d\n", id);
}

void displayAll() {
    if (head == NULL) {
        printf("No submissions available.\n");
        return;
    }
    Submission *temp = head;
    printf("\n===== All Submissions =====\n");
    while (temp != NULL) {
        printf("Student ID: %d | Title: %s | Date: %s | Status: %s\n",
               temp->studentID, temp->title, temp->date, temp->status);
        temp = temp->next;
    }
    printf("===========================\n");
}

int main() {
    int choice, id;
    char title[50], date[15], status[15];

    while (1) {
        printf("\n--- Student Assignment Submission Tracker ---\n");
        printf("1. Add new submission\n");
        printf("2. Update submission status\n");
        printf("3. Search by Student ID\n");
        printf("4. Display all submissions\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Assignment Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter Submission Date (dd-mm-yyyy): ");
                scanf("%s", date);
                printf("Enter Status (Submitted/Pending): ");
                scanf("%s", status);
                insertSubmission(id, title, date, status);
                break;
            case 2:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter Assignment Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter New Status (Submitted/Pending): ");
                scanf("%s", status);
                updateStatus(id, title, status);
                break;
            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                searchByID(id);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
