#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void login();
void adminPanel();
void studentPanel();
void vote();
void enterCredentials();
void editCandidates();
void printResults();
void clearVotes();

// Structure to hold candidate information
typedef struct Candidate {
    char name[50];
    int votes;
} Candidate;

// Structure to hold user credentials
typedef struct User {
    char username[50];
    char password[50];
} User;

// Global variables
Candidate candidates[10]; // Assuming maximum of 10 candidates
int numCandidates = 0;
User students[100]; // Assuming maximum of 100 students
int numStudents = 0;

int main() {
    int i;
    // Load candidates from file
    FILE *file1, *file2;
    file1 = fopen("Candidates.txt", "r");
    for(i=0;i<10;i++){
        fscanf(file1, "%s %d", candidates[i].username, candidates[i].votes);
    }
    fclose(file1);
    // Load student credentials from file
    file2 = fopen("students.txt", "r");
    for(i=0;i<100;i++){
        fscanf(file2, "%s %s", students[i].username, students[i].password);
    }
    fclose(file2);

    login();

    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Welcome to the Voting System\n");
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Check if admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        adminPanel();
        return;
    }

    // Check if student
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(username, students[i].username) == 0 && strcmp(password, students[i].password) == 0) {
            studentPanel();
            return;
        }
    }

    printf("Invalid username or password\n");
}

void adminPanel() {
    int choice;
    printf("Admin Panel\n");
    printf("1. Enter Student Credentials\n");
    printf("2. Edit Candidates\n");
    printf("3. Print Voting Results\n");
    printf("4. Clear Votes\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            enterCredentials();
            break;
        case 2:
            editCandidates();
            break;
        case 3:
            printResults();
            break;
        case 4:
            clearVotes();
            break;
        default:
            printf("Invalid choice\n");
    }
}

void studentPanel() {
    // Display candidates
    // Allow voting
    // Update vote counts
    vote();
}

void vote() {
    // Implement the voting process

}

void enterCredentials() {
    // Implement entering student credentials
}

void editCandidates() {
    // Implement editing candidate names
}

void printResults() {
    // Implement printing voting results
}

void clearVotes() {
    // Implement clearing all votes
}
