#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

#define ADMIN_PASSWORD "admin123"
#define MAX_LINE_LENGTH 100 //deleting records

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
void searchrecords();//done
void trim_whitespace(char *str);//remove later
void listrecords();//done
void payment();
void modifyrecords();
void addBill();
void tryAgain();//done

//deleterecord funcs
void getInputWithoutExtension(char *input, size_t size, const char *prompt);
void getInput(char *input, size_t size, const char *prompt, const char *fileExtensions);
void removeDataFromFile(const char *inputFile, const char *outputFile, const char *dataToRemove);
void deleterecords();


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
                addBill();
                break;
			case 'D':
				deleterecords();
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

<<<<<<< Updated upstream
//DELETING RECORDS---------------------------------------------------------------------------------------------------------


// Function to get input without extension
void getInputWithoutExtension(char *input, size_t size, const char *prompt) {
    printf("%s: ", prompt);
    fgets(input, size, stdin);

    // Remove newline character if present
    char *newline = strchr(input, '\n');
    if (newline) {
        *newline = '\0';
    }
}

// Function to get input with valid file extension
void getInput(char *input, size_t size, const char *prompt, const char *fileExtensions) {
    do {
        getInputWithoutExtension(input, size, prompt);

        // Check if the input has a valid extension
        char *dot = strrchr(input, '.');
        if (dot && strchr(fileExtensions, *dot)) {
            break;
        } else {
            printf("Invalid file extension. Please enter a valid file name with %s extension.\n", fileExtensions);
        }
    } while (1);
}

// Function to remove data from a file based on a specified condition
void removeDataFromFile(const char *inputFile, const char *outputFile, const char *dataToRemove) {
    FILE *originalFile, *tempFile;
    char line[MAX_LINE_LENGTH];

    // Open the original file for reading
    originalFile = fopen(inputFile, "r");
    if (originalFile == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Open a temporary file for writing
    tempFile = fopen("temp_file.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(originalFile);
        exit(EXIT_FAILURE);
    }

    // Read each line from the original file
    while (fgets(line, sizeof(line), originalFile) != NULL) {
        // Check if the line contains data to be removed
        if (strstr(line, dataToRemove) == NULL) {
            // If not, write the line to the temporary file
            fputs(line, tempFile);
        }
    }

    // Close both files
    fclose(originalFile);
    fclose(tempFile);

    // Delete the original file
    if (remove(inputFile) != 0) {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file name
    if (rename("temp_file.txt", outputFile) != 0) {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }

    printf("Data removed successfully.\n");
}

// Function to handle the deletion of records
void deleterecords() {
    char inputFile[MAX_LINE_LENGTH];
    char outputFile[MAX_LINE_LENGTH];
    char dataToRemove[MAX_LINE_LENGTH];
    char password[20];
    int counter = 0;

    // Get input for file names and data to remove
    getInput(inputFile, sizeof(inputFile), "\n Enter the input file name", ".txt or .csv");
    getInput(outputFile, sizeof(outputFile), "Enter the output file name", ".txt or .csv");
    getInputWithoutExtension(dataToRemove, sizeof(dataToRemove), "Enter the data to remove");

    // Prompt for admin password with limited attempts
    do {
        printf("Please enter the admin password: ");
        scanf("%19s", password);

        if (strcmp(password, "admin123") == 0) {
            // Call the function to remove data from the file
            removeDataFromFile(inputFile, outputFile, dataToRemove);
        } else {
            printf("Invalid Password! \n");
            counter++;
        }
    } while (strcmp(password, "admin123") != 0 && counter < 5);

    if (counter >= 5) {
        printf("Maximum attempts reached!\n");
=======
void addBill(){
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char username_search[256];

    // Get input for search
    system("cls");
    printf("\nEnter username: ");
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

            float new_bill = new_electricity + new_water;
            float total_payment = new_bill + (atoi(room_rate) * atoi(days_to_pay));
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
>>>>>>> Stashed changes
    }
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
<<<<<<< Updated upstream
=======


//Analysis: remove water bill and electricity bill merge it to total payment column
//Do not display how many tenants in each room
//
//Bugs: cannot modify data
>>>>>>> Stashed changes
