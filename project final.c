#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>

// Function prototypes
void login();
void adminPanel();
void studentPanel();
void vote();
void enterCredentials();
void enterCandidates();
void printResults();
void clearVotes();
void updateCandidateFile();

// Structure to hold candidate information
typedef struct Candidate {
    char name[50];
    int votes;
} Candidate;

// Structure to hold user credentials
typedef struct User {
    char username[50];
    char password[50];
    bool hasVoted; // Flag to indicate whether the user has voted or not
} User;

// Global variables
Candidate candidates[10];
int numCandidates = 0;
User students[100];
int numStudents = 0;

int main() {
    // Load candidates from file
    FILE *candidatesFile = fopen("candidates.txt", "r");
    if (candidatesFile == NULL) {
        printf("Error opening candidates file.\n");
        return 1; // Exiting
    }
    while (fscanf(candidatesFile, "%s %d", candidates[numCandidates].name, &candidates[numCandidates].votes) != EOF) {
        numCandidates++;
    }
    fclose(candidatesFile);

    // Load student credentials from file
    FILE *studentsFile = fopen("students.txt", "r");
    if (studentsFile == NULL) {
        printf("Error opening students file.\n");
        return 1;
    }
    while (fscanf(studentsFile, "%s %s %d", students[numStudents].username, students[numStudents].password, &students[numStudents].hasVoted) != EOF) {
        numStudents++;
    }
    fclose(studentsFile);


    login();

    return 0;
}

void login() {
    // Login logic

    char username[50];
    char password[50];

    while(1){
    printf("\t**************************\n\n");
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    printf("\n\t**************************\n\n");

    // Check if admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        adminPanel();
        return;
    }

    // Check if student
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(username, students[i].username) == 0 && strcmp(password, students[i].password) == 0) {
            if (students[i].hasVoted) {
                printf("You have already voted.\n");
                break; // added a break here to go back to login loop it will print invalid username or password then go back to enter your username
            } else {
                studentPanel(username);
            }
            return;
        }
    }
    printf("Invalid username or password\n");
    //invoke this if u want to clear screen after already voted or invalid and go back to login
    printf("Wait for 2 secs....\n");
    sleep(2);
    system("cls");

 }
}

void adminPanel() {
    // Admin panel logic
    //changed print statements
    int choice;
    while(1){
    printf("-----------------------------------------------------\n");
    printf("Admin Panel\n");
    printf("1. Enter Student Credentials\n");
    printf("2. Enter Candidate's credentials\n");
    printf("3. Set all vote status to default\n");
    printf("4. print results\n");
    printf("5. Clear Votes \n");
    printf("6. MainMenu\n");
    printf("7. Exit\n");
    printf("Enter your choice (1-7): ");
    scanf("%d", &choice);
    printf("\n-----------------------------------------------------\n");

    switch (choice) {
        case 1:
            enterCredentials();
            break;

        case 2:
            enterCandidates();
            break;

        case 3://try changing to append for fixing rewrite bug
            for (int i = 0; i < numStudents; i++) {
              students[i].hasVoted = false;
            }
            FILE *studentsFile = fopen("students.txt", "w");
            for(int i = 0; i < numStudents; i++){
                fprintf(studentsFile, "\n%s %s %d", students[i].username, students[i].password, students[i].hasVoted);//\n changed from last to first
            }
            fclose(studentsFile);
            break;

        case 4:
            printResults();
            break;

        case 5:
            clearVotes();
            break;
        case 6: login();
        case 7:
                exit(0);
        default:
            printf("Invalid choice, please Enter choice from 1 to 7\n");
    }
    //break;
   }
   return;
}

void studentPanel(const char *username) {
    printf("Candidates:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    vote(username); //vote function call passing username
}

void vote(const char *username) {
    int choice;
    printf("Enter the number of the candidate you want to vote for: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > numCandidates) {
        printf("Invalid choice\n");
        return;
    }

    // Updating vote count for the chosen candidate
    candidates[choice - 1].votes++;

    // Setting hasVoted flag for the student to true
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(username, students[i].username) == 0) {
            students[i].hasVoted = true;
            break;
        }
    }

    // Update candidate file
    updateCandidateFile();
    FILE *studentsFile = fopen("students.txt", "w");
    for(int i = 0; i<numStudents; i++){//added \n below just now
        fprintf(studentsFile, "%s %s %d\n", students[i].username, students[i].password, students[i].hasVoted);
    }
    fclose(studentsFile);

    Beep(750, 800);

    printf("Thank you for voting!\n");
    sleep(5);
    system("cls");
    login();
}

void updateCandidateFile() {
    FILE *candidatesFile = fopen("candidates.txt", "w");
    if (candidatesFile == NULL) {
        printf("Error opening candidates file for writing.\n");
        return;
    }

    // Write the updated vote counts for each candidate
    for (int i = 0; i < numCandidates; i++) {
        fprintf(candidatesFile, "%s %d\n", candidates[i].name, candidates[i].votes);
    }

    fclose(candidatesFile);
}

void enterCredentials() {
    // Enter credentials logic remains unchanged
    char ch;
    FILE *studentsFile = fopen("students.txt", "a");
    do{
        int i = 0;
        students[i].hasVoted = false;
        printf("Enter the student credentials\n");
        printf("Enter the student ID: ");
        scanf("%s", students[i].username);
        printf("\nEnter the password: ");
        scanf("%s", students[i].password);
        fprintf(studentsFile, "\n%s %s", students[i].username, students[i].password);
        printf("Do you want to enter another student's details?(y/n)\n");
        scanf(" %c", &ch);
        i++;
        }while(ch == 'y' || ch == 'Y');
        fclose(studentsFile);
        adminPanel();
}

void enterCandidates() {
    // Edit candidates logic remains unchanged
    char ch;
    FILE *candidatesFile = fopen("candidates.txt", "a");//changed from w
    do{
        int i = 0;
        candidates[i].votes = false;
        //printf("Enter the candidate credentials\n");
        printf("Enter the candidate name: ");
        scanf("%s", candidates[i].name);
        fprintf(candidatesFile, "%s %d\n", candidates[i].name, candidates[i].votes);
        printf("Do you want to enter another candidate's details?(y/n)\n");
        scanf(" %c", &ch);
        i++;
        }while(ch == 'y' || ch == 'Y');
        fclose(candidatesFile);
        adminPanel();
}

void printResults() {
    // Print results logic
    printf("\n\t********************\n");
    printf("\nResults are: \n");
    printf("candidate\tvotes\n");
    FILE *candidatesFile = fopen("candidates.txt","r");
    for(int i=0;i<numCandidates;i++){
        //fgets(details,50,fptr);
        fscanf(candidatesFile,"%s %d",candidates[i].name,&candidates[i].votes);
        printf("%s\t\t%d\n", candidates[i].name, candidates[i].votes);
    }
    fclose(candidatesFile);
    printf("\n\t********************\n");
    printf("\n"); //for giving space in console
    adminPanel();
}

void clearVotes() {
    for(int i = 0; i<numCandidates; i++){
        candidates[i].votes = 0;
    }
    FILE *candidatesFile = fopen("candidates.txt", "w");
    for(int i= 0; i<numCandidates; i++){
        fprintf(candidatesFile, "%s %d\n", candidates[i].name, candidates[i].votes);
    }
    fclose(candidatesFile);
    printf("\n");//to give space in console
    adminPanel();
}
