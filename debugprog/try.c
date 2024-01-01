#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

void nextMonth();
void AddNextMonth();
void trim_whitespace(char *str);

int main() {
    AddNextMonth();

    return 0;
}

void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}


void AddNextMonth() {
    char month[10], year[5];
    char fileName[50];

    FILE *file = fopen("tenant_records.txt", "r");
    FILE *newFile, *nameContainerFile;

    if (file == NULL) {
        perror("\n\nError opening the file.\n");
        printf("\nAny key to continue");
        getch();
    } else {
        // Get input for the month
        system("cls");
        // displayMessage();
        printf("\nEnter the month: ");
        scanf("%s", month);
        toUpperCase(month);
        printf("Enter year: ");
        scanf("%s", year);

        // Construct the file name with the format "monthyear.txt"
        snprintf(fileName, sizeof(fileName), "%s%s.txt", month, year);

        // Open a new file for writing
        newFile = fopen(fileName, "w");
        if (newFile == NULL) {
            perror("Error creating new file");
        }

        // Open the name container file for appending
        nameContainerFile = fopen("name_container.txt", "a");
        if (nameContainerFile == NULL) {
            perror("Error opening name container file");
            exit(EXIT_FAILURE);
        }

        char line[256];

        // Skip the first line (header)
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            return;
        }

        // Write the header to the new file
        fprintf(newFile, "%s", line);

        // Iterate through all records in the file
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

            // Display the record details
            printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);

            // Get new electricity and water bill values from the user
            float new_electricity, new_water;
            int new_daystopay;
            printf("\nEnter new electricity bill for %s: ", record_username);
            scanf("%f", &new_electricity);
            printf("Enter new water bill for %s: ", record_username);
            scanf("%f", &new_water);
            printf("Enter how many days %s would pay: ", record_username);
            scanf("%d", &new_daystopay);

            float new_bill = new_electricity + new_water;
            float new_total_payment = new_bill + (atof(room_rate) * new_daystopay);

            // Append the modified record to the new file
            fprintf(newFile, "%s,%s,%s,%.2f,%.2f,%d,%.2f\n", record_username, room_number, room_rate, new_electricity, new_water, new_daystopay, new_total_payment);

            // Write the new file name to the name container file
            fprintf(nameContainerFile, "%s\n", fileName);
        }

        printf("\nNew file '%s' created successfully.\n", fileName);

        // Close the files
        fclose(file);
        fclose(newFile);
        fclose(nameContainerFile);
    }
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