#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

void searchAndModifyRecords();

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

int main() {
    searchAndModifyRecords();
    return 0;
}

void searchAndModifyRecords() {
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
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
        return;
    }

    // Search for the record
    int record_found = 0;
    FILE *tempFile = fopen("temp_records.txt", "w");

    fprintf(tempFile, "%s", line);  // Write the header to the temp file

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
            // Display the found record along with total_payment
            printf("%-15s%-15s%-15s%-18s%-10s%-10s%-20s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay", "Total Payment");

            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-18s%-10.2f%-15s%-20.2f\n", record_username, room_number, room_rate, num_of_tenants, bill, days_to_pay, total_payment);
            record_found = 1;

            // Get new electricity and water bill values from the user
            float new_electricity, new_water;
            printf("\nEnter new electricity bill: ");
            scanf("%f", &new_electricity);
            printf("Enter new water bill: ");
            scanf("%f", &new_water);

            // Append the modified record to the temp file
            fprintf(tempFile, "%s,%s,%s,%s,%.2f,%.2f,%s,%.2f\n", record_username, room_number, room_rate, num_of_tenants, new_electricity, new_water, days_to_pay, total_payment);
        } else {
            // Write the unchanged record to the temp file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%.2f\n", record_username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay, total_payment);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!record_found) {
        printf("Record not found.\n");
        remove("temp_records.txt");  // Remove the temporary file if record not found
    }
    else{
    // Remove the original file and rename the temporary file to the original file
    remove("tenant_records.txt");
    rename("temp_records.txt", "tenant_records.txt");
    }
}
