#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void display_table_header() {
    printf("%-15s%-15s%-15s%-18s%-10s%-10s%-15s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bills", "Days to Pay");
}

void display_table_row(char *username, char *room_number, char *room_rate, char *num_of_tenants, char *electricity, char *water, char *days_to_pay) {
    
    // Calculate the bill by adding electricity and water
    float bill = atof(electricity) + atof(water);

    printf("%-15s%-15s%-15s%-18s%-10.2f%-15s\n", username, room_number, room_rate, num_of_tenants, bill, days_to_pay);
}

// Trim leading and trailing whitespaces from a string
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

int search_record(char *username, FILE *file) {
    char line[256];

    // Skip the first line (header)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        return 1;
    }

    // Search for the record
    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *num_of_tenants = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username) == 0) {
            // Display the found record in a single line
            display_table_header();
            display_table_row(record_username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay);
            return 0;
        }
    }

    printf("Record not found.\n");
    return 1;
}

int main() {
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    char username_search[256];

    // Get input for search
    printf("Enter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    // Perform the search
    search_record(username_search, file);

    fclose(file);

    return 0;
}
