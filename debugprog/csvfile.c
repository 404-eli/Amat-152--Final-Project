#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_table_header() {
    printf("%-15s%-15s%-15s%-18s%-10s%-15s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay");
}

void display_table_row(char *username, char *room_number, char *room_rate, char *num_of_tenants, char *electricity, char *water, char *days_to_pay) {
    // Calculate the bill by adding electricity and water
    float bill = atof(electricity) + atof(water);

    printf("%-15s%-15s%-15s%-18s%-10.2f%-15s\n", username, room_number, room_rate, num_of_tenants, bill, days_to_pay);
}

int main() {
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Display table header
    display_table_header();

    char line[256]; // Adjust the size based on your file's maximum line length

    // Skip the first line (header)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        return 1;
    }

    // Read and display the tenant records
    while (fgets(line, sizeof(line), file) != NULL) {
        char *username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *num_of_tenants = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");

        // Display the row
        display_table_row(username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay);
    }

    fclose(file);

    return 0;
}
