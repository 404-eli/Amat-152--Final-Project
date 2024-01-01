#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void addTenantRecord();
void trim_whitespace(char *str);

int main() {
    addTenantRecord();
    return 0;
}

void addTenantRecord() {
    FILE *record;
    record = fopen("tenant_records1.txt", "a+");
    if (record == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    system("cls");
    // Assuming you have a structure defined for 'tenant'
    // You can replace it with your actual structure definition
    struct Tenant {
        char username[256];
        char roomNumber[256];
        int roomRate;
        float waterBill;
        float electricityBill;
        int daysToPay;
    } tenant;

    // Get input for username and check for existing username
    do {
        printf("Enter Username: ");
        scanf("%s", tenant.username);

        // Convert username to uppercase
        for (int i = 0; tenant.username[i]; i++) {
            tenant.username[i] = toupper(tenant.username[i]);
        }

        // Check if the username already exists
        if (isUsernameExists(tenant.username)) {
            printf("Username already exists. Please enter a different username.\n");
        }
    } while (isUsernameExists(tenant.username));

    // Get input for other fields
    printf("Enter Room Number: ");
    scanf("%s", tenant.roomNumber);

    // Convert room number to uppercase
    for (int i = 0; tenant.roomNumber[i]; i++) {
        tenant.roomNumber[i] = toupper(tenant.roomNumber[i]);
    }

    printf("Enter Room Rate: ");
    scanf("%d", &tenant.roomRate);

    printf("Enter Water Bill: ");
    scanf("%f", &tenant.waterBill);

    printf("Enter Electriity Bill: ");
    scanf("%f", &tenant.electricityBill);


    while (1) {
        printf("Enter Number of Days to Pay: ");
        int result = scanf("%d", &tenant.daysToPay);

        if (result == 1) {
            // Successful integer input
            break;
        } else {
            // Clear the input buffer
            while (getchar() != '\n');

            // Prompt user for valid input
            printf("Invalid input. Please enter a valid integer.\n");
        }
    }
    

    // Calculate total_payment by multiplying room_rate and days_to_pay, then adding electricity and water
    float total_payment = tenant.roomRate * tenant.daysToPay + tenant.waterBill + tenant.electricityBill;

    fseek(record, 0, SEEK_END);
    if (ftell(record) == 0) {
        writeHeader(record, "Username, Room Number, Room Rate, Num Of Tenants, Water Bill, Electricity Bill, Days to Pay, Total Payment");
    }

    // Append the record with the new total_payment column
    fprintf(record, "%s, %s, %d, %.2f, %.2f, %d, %.2f\n",
            tenant.username, tenant.roomNumber, tenant.roomRate, tenant.waterBill, tenant.electricityBill, tenant.daysToPay, total_payment);

    fflush(stdin);
    printf("\n1 record successfully added");
    printf("\n Press any key to exit: ");
    getch();
    system("cls");
    fclose(record);
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


int isUsernameExists(const char *username) {
    FILE *file = fopen("tenant_records1.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0; // Return 0 assuming the file doesn't exist or there was an error
    }

    // Skip the first line (header)
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0; // Return 0 if there is an error reading the header
    }

    // Search for the username in the records
    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username) == 0) {
            fclose(file);
            return 1; // Return 1 if the username already exists
        }
    }

    fclose(file);
    return 0; // Return 0 if the username does not exist
}

void writeHeader(FILE *record, const char *header) {
    fprintf(record, "%s\n", header);
}