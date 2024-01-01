#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void modifyRecord();
void trim_whitespace(char *str);

int main() {
    modifyRecord();
    return 0;
}

void modifyRecord() {
    FILE *file = fopen("tenant_records.txt", "r");
    FILE *tempFile = fopen("temp_records.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening the file(s).\n");
        return;
    }

    char username_search[256];

    // Get input for search
    printf("Enter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    // Skip the first line (header)
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    fprintf(tempFile, "%s", line);  // Write the header to the temp file

    // Search for the record
    int record_found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *num_of_tenants = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        float total_payment = atof(strtok(NULL, ","));  // Retrieve total_payment as a float

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username_search) == 0) {
            // Display the found record
            printf("Original Information:\n");
            printf("%-15s%-15s%-15s%-18s%-10s%-10s%-20s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay", "Total Payment");
            printf("%-15s%-15s%-15s%-18s%-10.2f%-15s%-20.2f\n", record_username, room_number, room_rate, num_of_tenants, atof(electricity) + atof(water), days_to_pay, total_payment);

            // Get new information from the user for modification
            printf("\nEnter new room number: ");
            fgets(room_number, sizeof(room_number), stdin);
            room_number[strcspn(room_number, "\n")] = '\0';  // Remove the newline character

            printf("Enter new room rate: ");
            fgets(room_rate, sizeof(room_rate), stdin);
            room_rate[strcspn(room_rate, "\n")] = '\0';  // Remove the newline character

            printf("Enter new number of tenants: ");
            fgets(num_of_tenants, sizeof(num_of_tenants), stdin);
            num_of_tenants[strcspn(num_of_tenants, "\n")] = '\0';  // Remove the newline character

            printf("Enter new electricity bill: ");
            fgets(electricity, sizeof(electricity), stdin);
            electricity[strcspn(electricity, "\n")] = '\0';  // Remove the newline character

            printf("Enter new water bill: ");
            fgets(water, sizeof(water), stdin);
            water[strcspn(water, "\n")] = '\0';  // Remove the newline character

            printf("Enter new days to pay: ");
            fgets(days_to_pay, sizeof(days_to_pay), stdin);
            days_to_pay[strcspn(days_to_pay, "\n")] = '\0';  // Remove the newline character

            printf("Enter new total payment: ");
            scanf("%f", &total_payment);
        }

        // Write the line as is to the temporary file
        fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%.2f\n", record_username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay, total_payment);
    }

    fclose(file);
    fclose(tempFile);

    if (!record_found) {
        printf("Record not found.\n");
    } else {
        // Remove the original file and rename the temporary file to the original file
        remove("tenant_records.txt");
        rename("temp_records.txt", "tenant_records.txt");
        printf("Record modified successfully.\n");
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
