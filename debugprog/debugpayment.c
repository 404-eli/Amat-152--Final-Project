#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void payment();
void trim_whitespace(char *str);

int main() {
    payment();
    return 0;
}

void payment() {
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
    char c;
    while ((c = fgetc(file)) != '\n' && c != EOF) {
        fputc(c, tempFile);
    }
    fputc('\n', tempFile);

    // Search for the record
    int record_found = 0;

    while (fgets(username_search, sizeof(username_search), file) != NULL) {
        char *record_username = strtok(username_search, ",");
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

            // Get payment input from the user
            float payment_amount;
            printf("\nEnter payment amount: ");
            scanf("%f", &payment_amount);

            // Deduct payment_amount from total_payment
            total_payment -= payment_amount;

            // Update the total_payment in the temporary file
            fprintf(tempFile, "%s, %s, %s, %s, %s, %s, %s, %.2f\n",
                    record_username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay, total_payment);
        } else {
            // Copy the line as is to the temporary file
            fprintf(tempFile, "%s", username_search);
        }
    }

    if (!record_found) {
        printf("Record not found.\n");
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file to the original file
    remove("tenant_records.txt");
    rename("temp_records.txt", "tenant_records.txt");
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
