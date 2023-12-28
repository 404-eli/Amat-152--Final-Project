#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    FILE *record = fopen("tenant_records.txt", "r");

    if (record == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("%-15s%-15s%-15s%-18s%-10s%-15s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay");

    char line[256]; // Adjust the size based on your file's maximum line length

    // Skip the first line (header)
    if (fgets(line, sizeof(line), record) == NULL) {
        printf("Error reading the header.\n");
        fclose(record);
        return 1;
    }

    // Read and display the tenant records
    while (fgets(line, sizeof(line), record) != NULL) {
        char *username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *num_of_tenants = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");

    float bill = atof(electricity) + atof(water);

    printf("%-15s%-15s%-15s%-18s%-10.2f%-15s\n", username, room_number, room_rate, num_of_tenants, bill, days_to_pay);
    }

    fclose(record);
    getch();
}