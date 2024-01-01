#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_FILENAME_LEN 100//search
#define MAX_USERNAME_LEN 50//search
#define MAX_LINE_LEN 1000//search

int searchFile(); //new executed func sa switch
void printAvailableFiles();
void searchByUsername(const char *filename, const char *username);
void searchrecords();
int searchMonthly();
void trim_whitespace(char *str);
void toUpperCase(char *str);

int main() {
    searchFile();
    return 0;
}

int searchFile() {
    int choice;

    do {
        system("cls");
        // displayMessage();
        printf("\nChoose an option:\n");
        printf("1. Search Tenant Records File\n");
        printf("2. Search Monthly Records File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchrecords();//FOR MAIN RECORDS
                break;
            case 2:
                searchMonthly();//FOR MONTHLY RECORDS
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    return 0;
}

void searchrecords() {
    int record_found = 0, i;

    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        getch();
    }
    else{
        char username_search[256];

        // Get input for search
        // Get input for search
        system("cls");
        // displayMessage();
        printf("\n\n\t\tTenant Database\n\n");
        printf("\nEnter username: ");
        scanf("%s", username_search);
        toUpperCase(username_search);

        // Skip the first line (header)
        char line[256];
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            return;
        }

        printf("\n\n%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
        for (i = 0; i < 90; i++)printf("=");
        printf("\n");

        while (fgets(line, sizeof(line), file) != NULL) {
            char *record_username = strtok(line, ",");
            char *room_number = strtok(NULL, ",");
            char *room_rate = strtok(NULL, ",");
            char *electricity = strtok(NULL, ",");
            char *water = strtok(NULL, ",");
            char *days_to_pay = strtok(NULL, ",");
            float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float

            // Trim whitespaces from the found record values
            trim_whitespace(record_username);

            // Compare with the provided username
            if (strcmp(record_username, username_search) == 0) {
                // Display the found record in a single line

                float bill = atof(electricity) + atof(water);
                printf("%-15s%-15s%-15s%-10.2f%-15s%8.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
                record_found = 1;
                break;
            }
        }
            if (!record_found) {
            printf("\nRecord not found.\n");
        }
        for (i = 0; i < 90; i++)printf("=");
    }

    fclose(file);
    printf("\n\nPress any key to continue.");
    getch();
}

int searchMonthly() {
    char month[10];
    char year[5];
    char filename[MAX_FILENAME_LEN];
    char username[MAX_USERNAME_LEN];

    system("cls");
    // displayMessage();
    printAvailableFiles();
    
    printf("\nEnter month: ");
    scanf("%s", month);
    toUpperCase(month);
    printf("Enter year: ");
    scanf("%s", year);

    snprintf(filename, sizeof(filename), "%s%s.txt", month, year);
    
    system("cls");
    // displayMessage();
    printf("\n\t\tSearching in %s %s...\n\n", month, year);
    printf("Enter the username to search for: ");
    scanf("%s", username);
    toUpperCase(username);

    searchByUsername(filename, username);

    return 0;
}

void searchByUsername(const char *filename, const char *username) {
    int i, record_found = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
    }
    else{
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        return;
    }
    printf("\n\n");
    printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
    for (i = 0; i < 90; i++) printf("=");
    printf("\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);
        // Compare with the provided username
        if (strcmp(record_username, username) == 0) {
            // Display the found record in a single line
        
            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%8.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
            record_found = 1;
            break;
        }
    }
        if (!record_found) {
            printf("Username not found in %s\n", filename);
        }
        for (i = 0; i < 90; i++)printf("=");
    }
    fclose(file);
    printf("\n\nPress any key to continue.");
    getch();
}

void printAvailableFiles() {
    FILE *fileContainer = fopen("name_container.txt", "r");

    if (fileContainer == NULL) {
        perror("Error opening name_container.txt");
        exit(EXIT_FAILURE);
    }

    printf("Available files:\n");
    char filename[MAX_FILENAME_LEN];

    while (fgets(filename, MAX_FILENAME_LEN, fileContainer) != NULL) {
        // Remove newline character from the end
        filename[strcspn(filename, "\n")] = '\0';
        printf("%s\n", filename);
    }

    fclose(fileContainer);
}

void trim_whitespace(char *str) {
    int start = 0, end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) {
        start++;
    }

    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    int i;
    for (i = start; i <= end; i++) {
        str[i - start] = str[i];
    }

    str[i - start] = '\0';
}

void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}