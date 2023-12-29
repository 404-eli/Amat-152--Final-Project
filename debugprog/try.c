#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS 1000
#define MAX_LINE_LENGTH 256

typedef struct {
    char username[256];
    char room_number[256];
    char room_rate[256];
    char num_of_tenants[256];
    char electricity[256];
    char water[256];
    char days_to_pay[256];
    float total_payment;
} TenantRecord;

void payment();
void trim_whitespace(char *str);
void readRecords(FILE *file, TenantRecord records[], int *numRecords);
void writeRecords(FILE *file, TenantRecord records[], int numRecords);

int main() {
    payment();
    return 0;
}

void payment() {
    FILE *file = fopen("tenant_records.txt", "r+");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    TenantRecord records[MAX_RECORDS];
    int numRecords = 0;

    char username_search[256];

    // Get input for search
    printf("Enter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    // Read records from the file into memory
    readRecords(file, records, &numRecords);

    // Search for the record
    int record_found = 0;

    // Find the record to update
    for (int i = 0; i < numRecords; i++) {
        if (strcmp(records[i].username, username_search) == 0) {
            // Display the found record along with total_payment
            printf("%-15s%-15s%-15s%-18s%-10s%-10s%-20s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay", "Total Payment");

            float bill = atof(records[i].electricity) + atof(records[i].water);
            printf("%-15s%-15s%-15s%-18s%-10.2f%-15s%-20.2f\n", records[i].username, records[i].room_number, records[i].room_rate, records[i].num_of_tenants, bill, records[i].days_to_pay, records[i].total_payment);
            record_found = 1;

            // Get payment input from the user
            float payment_amount;
            printf("\nEnter payment amount: ");
            scanf("%f", &payment_amount);

            // Deduct payment_amount from total_payment
            records[i].total_payment -= payment_amount;

            // Update the total_payment in the file
            fseek(file, 0, SEEK_SET);
            writeRecords(file, records, numRecords);

            break;
        }
    }

    if (!record_found) {
        printf("Record not found.\n");
    }

    fclose(file);
}

void readRecords(FILE *file, TenantRecord records[], int *numRecords) {
    char line[MAX_LINE_LENGTH];

    // Skip the header
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if fgets successfully reads a line
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f",
               records[*numRecords].username,
               records[*numRecords].room_number,
               records[*numRecords].room_rate,
               records[*numRecords].num_of_tenants,
               records[*numRecords].electricity,
               records[*numRecords].water,
               records[*numRecords].days_to_pay,
               &records[*numRecords].total_payment);

        // Trim whitespaces from the found record values
        trim_whitespace(records[*numRecords].username);

        (*numRecords)++;
    }
}

void writeRecords(FILE *file, TenantRecord records[], int numRecords) {
    fprintf(file, "%-5s,%-5s,%-5s,%-5s,%-5s,%-5s,%-5s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay", "Total Payment");

    for (int i = 0; i < numRecords; i++) {
        float bill = atof(records[i].electricity) + atof(records[i].water);
        fprintf(file, "%-5s,%-5s,%-5s,%-5s,%-5.2f,%-5s,%-5.2f\n", records[i].username, records[i].room_number, records[i].room_rate, records[i].num_of_tenants, bill, records[i].days_to_pay, records[i].total_payment);
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
