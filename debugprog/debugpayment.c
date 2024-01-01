#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_FILE_NAME 100
#define MAX_LINE_LEN 1000
#define MAX_FILENAME_LEN 100

void displayMessage();
void payment();
void trim_whitespace(char *str);
void printAvailableFiles();
void toUpperCase(char *str);
int payment_search();

int main() {
    payment_search();
    return 0;
}
int payment_search(){
    int choice;

    do {
        system("cls");
        displayMessage();
        printf("\nChoose an option:\n");
        printf("1. Payment for month\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                payment();//FOR MAIN RECORDS
                break;
            case 2:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 2);

    return 0;
}

void payment() {
    char userFile[MAX_FILE_NAME];
    char username_search[256];
    char line[256];
    char month[15];
    char year[6];
    int i, record_found = 0;

    FILE *file, *tempFile;

    tempFile = fopen("temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp_records.txt for writing");
        return;
    }
    else{
        system("cls");
        displayMessage();
        printAvailableFiles();
        printf("\nEnter the month: ");
        scanf("%s", month);
        toUpperCase(month);
        printf("Enter year: ");
        scanf("%s", year);

        // Construct the file name with the format "monthyear.txt"
        snprintf(userFile, sizeof(userFile), "%s%s.txt", month, year);

        file = fopen(userFile, "r");
        if (file == NULL) {
            perror("Error opening the file");
            fclose(tempFile);
            return;
        }

        // Get input for search
        system("cls");
        displayMessage();
        printf("Searching in %s %s.....\n", month, year);
        printf("Enter username: ");
        scanf("%s", username_search);
        toUpperCase(username_search);

        // Skip the first line (header)
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            fclose(tempFile); 
            return;
        }

        fprintf(tempFile, "%s", line);  // Write the header to the temp file

        printf("\n%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
        for (i = 0; i < 90; i++)printf("=");

        while (fgets(line, sizeof(line), file) != NULL) {
            char *record_username = strtok(line, ",");
            char *room_number = strtok(NULL, ",");
            char *room_rate = strtok(NULL, ",");
            char *electricity = strtok(NULL, ",");
            char *water = strtok(NULL, ",");
            char *days_to_pay = strtok(NULL, ",");
            float total_payment = atof(strtok(NULL, "\n"));

            // Trim whitespaces from the found record values
            trim_whitespace(record_username);

            // Compare with the provided username
            if (strcmp(record_username, username_search) == 0) {
                // Display the found record along with total_payment

                float bill = atof(electricity) + atof(water);
                printf("\n%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
                for (i = 0; i < 90; i++)printf("=");
                printf("\n");
                record_found = 1;

                // Get payment input from the user
                float payment_amount;
                printf("\nEnter payment amount: ");
                scanf("%f", &payment_amount);

                // Deduct payment_amount from total_payment
                total_payment -= payment_amount;
            }

            // Write the line as is to the temporary file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%.2f\n", record_username, room_number, room_rate, electricity, water, days_to_pay, total_payment);
        }

        fclose(file);
        fclose(tempFile);

        if (!record_found) {
            printf("Record not found.\n");
            remove("temp_records.txt");
            getch();
        } else {
            // Remove the original file and rename the temporary file to the original file
            remove(userFile);
            rename("temp_records.txt", userFile);
        }
    }
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
        filename[strcspn(filename, "\n")] = '\0';
        printf("%s\n", filename);
    }

    fclose(fileContainer);
}

void displayMessage() {
    printf("\n\n================================================================");
    printf("\n\t------WELCOME TO SILVA PAYMENT SYSTEM------");
    printf("\n==================================================================\n\n");
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