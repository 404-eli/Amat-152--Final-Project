#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

#define ADMIN_PASSWORD "admin123"

void displpayMessage();//done
void menu();//done
void writeHeader(FILE *record, const char *header);//allowed
//tenant panel functions
void tenantPanel();
//can be found on both 
void logIn();//partially done
void logOut();//done
//admin panel functions
void adminPanel();//done
void addTenantRecord();//done
void addNextMonthRecord();
void deleterecords();
void searchrecords();//done
void trim_whitespace(char *str);//remove later
void listrecords();//done
void payment();
void modifyrecords();
void addBill();
void tryAgain();//done

int main(){
    int num;

    displpayMessage();
    menu();

    return 0;
}

void displpayMessage(){
    printf("\n\n**************************************************************");
	printf("\n\t------WELCOME TO SILVA PAYMENT SYSTEM------");
	printf("\n****************************************************************\n\n");
}

void menu(){
    int choice;

    while (1)
    {
        system("cls");
        displpayMessage();
        printf("\n\n A : Admin Panel\n T : Tenant Panel\n E : Exit\nChoice: ");
        choice = getche();
        choice = toupper(choice);
        switch (choice)
        {
        case 'A':
            logIn();
            break;
        case 'T':
            logIn();
            break;
        case 'E':
            printf("\n\nThank you for using our service!");
            exit(0);
            break;
        default:
            printf("\n\nIncorrect Input");
            printf("\nAny key to continue");
            getch();
            system("cls");
            break;
        }
    }
}

void adminPanel(){
    int choice;

	while (1)
	{
        system("cls");
        displpayMessage();
		printf("\n Enter\n A : Add new Records.\n L : List of records\n N : Add next month record");
		printf("\n B : Add Water & Electricty Bill\n M : Modify records.\n P : Payment");
		printf("\n S : Searching records.");
		printf("\n D : Delete records.\n O : Log out\nChoice: ");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();
                break;
			case 'A':
				addTenantRecord();
                break;
			case 'L':
				listrecords();
                break;
			case 'M':
				// modifyrecords();
                break;
			case 'N':
				// addNextMonthRecord();
                break;
			case 'S':
				searchrecords();
                break;
            case 'B':   
                // addBill();
                break;
			case 'D':
				// deleterecords();
                break;
			case 'O':
                system("cls");
                logOut();
				break;
			default:
				printf("\n\nIncorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}

void tenantPanel(){
        int choice;

    while (1)
    {
        system("cls");
        displpayMessage();
        printf(" B : See Balance\n O : Log out\nChoice: ");
        choice = getche();
        choice = toupper(choice);
        switch (choice)
        {
        case 'B':
            printf("Undergoing!");
            system("cls");
            menu();
            break;
        case 'O':
            system("cls");
            logOut();
            break;
        default:
            printf("\n\nIncorrect Input");
            printf("\nAny key to continue");
            getch();
            break;
        }
    }
}

void addTenantRecord() {
    FILE *record;
    record = fopen("tenant_records.txt", "a+");
    if (record == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    system("cls");
    displpayMessage();
    printf("Enter Username: ");
    scanf("%s", &tenant.username);

    printf("Enter Room Number: ");
    scanf("%s", &tenant.roomNumber);

    printf("Enter Room Rate: ");
    scanf("%d", &tenant.roomRate);

    printf("Enter Number of Tenants: ");
    scanf("%d", &tenant.numOfTenants);

    printf("Enter Water Bill: ");
    scanf("%f", &tenant.waterBill);

    printf("Enter Electriity Bill: ");
    scanf("%f", &tenant.electricityBill);

    printf("Enter Number of Days to Pay: ");
    scanf("%d", &tenant.daysToPay);

    // Calculate total_payment by multiplying room_rate and days_to_pay, then adding electricity and water
    float total_payment = tenant.roomRate * tenant.daysToPay + tenant.waterBill + tenant.electricityBill;

    fseek(record, 0, SEEK_END);
    if (ftell(record) == 0) {
        writeHeader(record, "Username, Room Number, Room Rate, Num Of Tenants, Water Bill, Electricity Bill, Days to Pay, Total Payment");
    }

    // Append the record with the new total_payment column
    fprintf(record, "%s, %s, %d, %d, %.2f, %.2f, %d, %.2f\n",
            tenant.username, tenant.roomNumber, tenant.roomRate,
            tenant.numOfTenants, tenant.waterBill, tenant.electricityBill, tenant.daysToPay, total_payment);

    fflush(stdin);
    printf("\n1 record successfully added");
    printf("\n Press any key to exit: ");
    getch();
    system("cls");
    fclose(record);
}

void listrecords() {
    FILE *record = fopen("tenant_records.txt", "r");
    int i;

    if (record == NULL) {
        printf("Error opening the file.\n");
        return;
    }
// 
    system("cls");
    printf("\n%-15s%-15s%-15s%-18s%-10s%-15s%-15s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bill", "Days to Pay", "Total Payment");
    for (i = 0; i < 95; i++) {
        printf("-");
    }
    printf("\n");

    char line[256]; // Adjust the size based on your file's maximum line length

    // Skip the first line (header)
    if (fgets(line, sizeof(line), record) == NULL) {
        printf("Error reading the header.\n");
        fclose(record);
        return;
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
        char *total_payment = strtok(NULL, "\n"); // Adjust to read until the end of the line

        float bill = atof(electricity) + atof(water);

        printf("%-15s%-15s%-15s%-18s%-10.2f%-15s%-15s\n", username, room_number, room_rate, num_of_tenants, bill, days_to_pay, total_payment);
    }

    for (i = 0; i < 95; i++) {
        printf("-");
    }

    fclose(record);
    getch();
}


void logIn(){
    char admin_val[] = "admin";
    char username_user[] = "user", username_in[10];

    char user_pass[] = "22f5";
    char password_in[10]; 
    system("cls");

    while (1)
    {
        displpayMessage();
        printf("Enter username: ");
        scanf("%s", &username_in);
        printf("Enter password: ");
        scanf("%s", &password_in);

        if (strcmp(admin_val, username_in) == 0)
        {
            if (strcmp(ADMIN_PASSWORD, password_in) == 0)
            {
                adminPanel();
            }
            else{
                tryAgain();
            }//optimize
        }

        else if (strcmp(username_user, username_in) == 0)
        {
            if (strcmp(user_pass, password_in) == 0)
            {
                tenantPanel();
            }
            else{
                tryAgain();
            }
        }

        else{
            tryAgain();
        }
    }
}

void logOut(){
    system("cls");
    printf("Logged out!");
    menu();
    system("cls");
}

void tryAgain(){
    int choice;

    while (1)
    {
        system("cls");
        displpayMessage();
        printf("Invalid Log-in information. Try again?\n[Y] Yes\n[N] No\nChoice: ");
        choice = getche();
        choice = toupper(choice);
        switch (choice)
        {
        case 'Y':
            logIn();
            break;
        case 'N':
            system("cls");
            menu();
            break;
        default:
            printf("\n\nInvalid input!\nPress any key to continue!\n");
            getch();
            break;
        }
    }
}

void searchrecords() {
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
    }

    char username_search[256];

    // Get input for search
    system("cls");
    displpayMessage();
    printf("Enter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    // Skip the first line (header)
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
    }

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

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username_search) == 0) {
            // Display the found record in a single line
        printf("%-15s%-15s%-15s%-18s%-10s%-10s\n", "Username", "Room Number", "Room Rate", "Num of Tenants", "Bills", "Days to Pay");
        
        float bill = atof(electricity) + atof(water);
        printf("%-15s%-15s%-15s%-18s%-10.2f%-15s\n", record_username, room_number, room_rate, num_of_tenants, bill, days_to_pay);
            record_found = 1;
            break;
        }
    }

    if (!record_found) {
        printf("Record not found.\n");
    }

    fclose(file);
    printf("\nEnter any key to continue.");
    getch();
}

void payment(){
    FILE *file = fopen("tenant_records.txt", "r+");

    if (file == NULL) {
        printf("Error opening the file.\n");
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
    }

    // Search for the record
    int record_found = 0;
    long int position = ftell(file); // Record the position before the loop

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

            // Get payment input from the user
            float payment_amount;
            printf("\nEnter payment amount: ");
            scanf("%f", &payment_amount);

            // Deduct payment_amount from total_payment
            total_payment -= payment_amount;
            // printf("Remaining balance after payment: %.2f\n", total_payment);

            // Move the file pointer to the position before the loop
            fseek(file, position, SEEK_SET);

            // Update the total_payment in the file
            fprintf(file, "%s, %s, %s, %s, %s, %s, %s, %.2f\n",
                    record_username, room_number, room_rate, num_of_tenants, electricity, water, days_to_pay, total_payment);

            break;
        }

        // Record the position after each line read
        position = ftell(file);
    }

    if (!record_found) {
        printf("Record not found.\n");
    }

    fclose(file);
}


//additional functions

void writeHeader(FILE *record, const char *header) {
    fprintf(record, "%s\n", header);
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