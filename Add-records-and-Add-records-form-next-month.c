#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Tenant Details
struct Tenant {
    char username[50];
    char roomNumber[7];
    int roomRate;
    int numOfTenants;
    float waterBill;
    float electricityBill;
    int daysToPay;
};

// Function to write the header to a file
void writeHeader(FILE *file, const char *header) {
    fprintf(file, "%s\n", header);
}

// Function to add a record for a tenant
void addTenantRecord(struct Tenant *tenant) {
    printf("Enter tenant details:\n");

    printf("First Name (Username): ");
    scanf("%s", tenant->username);

    // Admin inputs the room number
    printf("Room Number: ");
    scanf("%s", &tenant->roomNumber);

    printf("Room Rate (by day): ");
    scanf("%d", &tenant->roomRate);

    printf("Number of Tenants in the room: ");
    scanf("%d", &tenant->numOfTenants);

    printf("Water Bill: ");
    scanf("%f", &tenant->waterBill);

    printf("Electricity Bill: ");
    scanf("%f", &tenant->electricityBill);

    printf("Number of Days to Pay: ");
    scanf("%d", &tenant->daysToPay);

    // Write the tenant information to file.txt
    FILE *file = fopen("tenant_records.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Check if the file is empty before writing the header
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        writeHeader(file, "| Username | RoomNumber | RoomRate | NumOfTenants | WaterBill | ElectricityBill | DaysToPay |");
    }

    fprintf(file, "| %-8s | %-11s | %-8d | %-13d | %-8.2f | %-15.2f | %-9d |\n",
            tenant->username, tenant->roomNumber, tenant->roomRate,
            tenant->numOfTenants, tenant->waterBill, tenant->electricityBill, tenant->daysToPay);

    fclose(file);
}

// Function to add a record for the next month
void addNextMonthRecord(struct Tenant *tenant) {
    int validate;

    printf("Add record for next month? (1 for yes, 2 for no): ");
    scanf("%d", &validate);

    if (validate == 1) {
        printf("Room Rate for Next Month (by day): ");
        scanf("%d", &tenant->roomRate);

        printf("Number of Days to Pay for Next Month: ");
        scanf("%d", &tenant->daysToPay);

        // Write the next month's information to txt.file
        FILE *file = fopen("next_month_records.txt", "a");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        // Check if the file is empty before writing the header
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            writeHeader(file, "| Username | RoomRate | DaysToPay |");
        }

        fprintf(file, "| %-8s | %-8d | %-9d |\n", tenant->username, tenant->roomRate, tenant->daysToPay);

        fclose(file);
    }
}

int main() {
    struct Tenant tenant;

    // Sample usage
    addTenantRecord(&tenant);
    addNextMonthRecord(&tenant);

    return 0;
}

/*
Fix:
- Add csv file type
- float type variable for days to pay and format the number to 2 decimal places only

*/