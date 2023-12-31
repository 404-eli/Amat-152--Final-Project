#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

#define ADMIN_PASSWORD "admin123"
#define MAX_LINE_LENGTH 100 //deleting records
#define MAX_FILE_NAME 50    //displaying records
#define MAX_BUFFER_SIZE 100 //displaying records

#define MAX_FILENAME_LEN 100//search
#define MAX_USERNAME_LEN 50//search
#define MAX_LINE_LEN 1000//search

void displayMessage();//done
void menu();//done
void writeHeader(FILE *record, const char *header);//allowed
int isUsernameExists(const char *username);
//tenant panel functions
void tenantPanel();
//can be found on both 
void logIn();//partially done
void logOut();//done
//admin panel functions
void adminPanel();//done
void addTenantRecord();//done
void AddNextMonth();
void searchrecords();//done
void trim_whitespace(char *str);//remove later

//list-------------------------------------------------------------------------------------------------------------------------------------------
int displayList(); //new executed func sa switch
void listrecords(); 
void printFile();

//search-----------------------------------------------------------------------------------------------------------------------------------------
int searchFile(); //new executed func sa switch
void printAvailableFiles();
void searchByUsername(const char *filename, const char *username);
void searchrecords();
int searchMonthly();



void payment();//starting
void modifyrecords();//idk if apilon ba ni 
void addBill();//done
void tryAgain();//done

//deleterecord funcs
void getInputWithoutExtension(char *input, size_t size, const char *prompt);
void getInput(char *input, size_t size, const char *prompt, const char *fileExtensions);
void removeDataFromFile(const char *inputFile, const char *outputFile, const char *dataToRemove);
void deleterecords();


int main(){

    displayMessage();
    menu();

    return 0;
}

void displayMessage(){
    printf("\n\n================================================================");
	printf("\n\t------WELCOME TO SILVA PAYMENT SYSTEM------");
	printf("\n==================================================================\n\n");
}

void menu(){
    int choice;

    while (1)
    {
        system("cls");
        displayMessage();
        printf("\n A : Admin Panel\n T : Tenant Panel\n E : Exit\nChoice: ");
        choice = getche();
        choice = toupper(choice);
        fflush(stdin);
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
        displayMessage();
		printf("\n Enter\n A : Add new Records.\n L : List of records\n S : Searching records.");
		printf("\n B : Add Water & Electricty Bill\n P : Payment");
		printf("\n N : Add next month record");
		printf("\n D : Delete records.\n O : Log out\nChoice: ");
		choice=getche();
		choice=toupper(choice);
        fflush(stdin);
		switch(choice)
		{
			case 'P':
				payment();
                break;
			case 'A':
				addTenantRecord();
                break;
			case 'L':
				displayList();
                break;
			case 'N':
				AddNextMonth();
                printf("\nAny key to continue");
                getch();
                break;
			case 'S':
				searchFile();
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
        displayMessage();
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
    displayMessage();
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
    scanf("%d", &tenant.roomRate);//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa I edited from f to d

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
        writeHeader(record, "Username, Room Number, Room Rate, Water Bill, Electricity Bill, Days to Pay, Total Payment");
    }

    // Append the record with the new total_payment column
    fprintf(record, "%s, %s, %.2d, %.2f, %.2f, %d, %.2f\n",
            tenant.username, tenant.roomNumber, tenant.roomRate, tenant.waterBill, tenant.electricityBill, tenant.daysToPay, total_payment);

    fflush(stdin);
    printf("\n1 record successfully added");
    printf("\n Press any key to exit: ");
    getch();
    system("cls");
    fclose(record);
}

//DisplayRecords----------------------------------------------------------------------------------------------------------------------------------


// Function to print the content of a file
void printFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}
// Function to list tenant records
void listrecords() {
    FILE *record = fopen("tenant_records.txt", "r");
    int i;

    if (record == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    system("cls");
    printf("\n%-15s%-15s%-15s%-10s%-15s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
    for (i = 0; i < 100; i++) {
        printf("=");
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
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        char *total_payment = strtok(NULL, "\n"); // Adjust to read until the end of the line

        float bill = atof(electricity) + atof(water);

        printf("%-15s%-15s%-15s%-10.2f%-15s%10s\n", username, room_number, room_rate, bill, days_to_pay, total_payment);
    }

    for (i = 0; i < 100; i++) {
        printf("=");
    }

    fclose(record);
    getchar(); // Consume newline character
}


int displayList() {
    int choice;
    char userFile[MAX_FILE_NAME];

    // Print contents of "name_container.txt" before prompting the user
    printf("\nRecorded Months:\n");
    printFile("name_container.txt");

    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Print Monthly Records:\n");
        printf("2. Print tenant_records.txt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the file to print: ");
                scanf("%s", userFile);
                printFile(userFile);
                break;
            case 2:
                listrecords();
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

        // Consume newline character after reading the choice
        while (getchar() != '\n');

    } while (choice != 3);

    return 0;
}

void logIn(){
    char admin_val[] = "admin";
    char username_user[] = "user", username_in[10];

    char user_pass[] = "22F5";
    char password_in[10]; 
    system("cls");

    while (1)
    {
        displayMessage();
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
        displayMessage();
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


int searchFile() {
    int choice;

    do {
        printf("Choose an option:\n");
        printf("1. Search Tenant Records File\n");
        printf("2. Search Monthly Records File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchrecords();
                break;
            case 2:
                searchMonthly();
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    return 0;
}

void searchByUsername(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char header[MAX_LINE_LEN];
    fgets(header, MAX_LINE_LEN, file); // Read the header line
    printf("%s", header);

    char line[MAX_LINE_LEN];
    int usernameFound = 0;

    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        // Check if the username is a substring of the line
        if (strstr(line, username) != NULL) {
            printf("%s", line);
            usernameFound = 1;
        }
    }

    if (!usernameFound) {
        printf("Username not found in %s\n", filename);
    }

    fclose(file);
}
void searchrecords() {
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char username_search[256];

    // Get input for search
   // Get input for search
system("cls");
printf("Enter username: ");
scanf("%s", username_search);

    // Skip the first line (header)
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        return;
    }

    // Search for the record
    int record_found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username_search) == 0) {
            // Display the found record in a single line
            printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");

            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%8.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
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

int searchMonthly() {
    printAvailableFiles();

    char filename[MAX_FILENAME_LEN];
    printf("\nEnter the filename: ");
    scanf("%s", filename);

    char username[MAX_USERNAME_LEN];
    printf("Enter the username to search for: ");
    scanf("%s", username);

    searchByUsername(filename, username);

    return 0;
}

void printAvailableFiles() {
    FILE *fileContainer = fopen("name_container.txt", "r");

    if (fileContainer == NULL) {
        perror("Error opening name_container.txt");
        exit(EXIT_FAILURE);
    }

    printf("Available files:\n");
    char filename[MAX_FILENAME_LEN];

    while (fgets(filename, MAX_FILENAME_LEN, fileContainer) != NULL) {
        // Remove newline character from the end
        filename[strcspn(filename, "\n")] = '\0';
        printf("%s\n", filename);
    }

    fclose(fileContainer);
}

void payment(){
    FILE *file = fopen("tenant_records.txt", "r");
    FILE *tempFile = fopen("temp_records.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening the file(s).\n");
        return;
    }

    char username_search[256];

    // Get input for search
    displayMessage();
    printf("Enter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    for (int i = 0; username_search[i]; i++) {
        username_search[i] = toupper(username_search[i]);
    }

    // Skip the first line (header)
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    fprintf(tempFile, "%s", line);  // Write the header to the temp file

    // Search for the record
    int record_found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_username = strtok(line, ",");
        char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ",");
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username_search) == 0) {
            // Display the found record along with total_payment
            printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");

            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
            record_found = 1;

            // Get payment input from the user
            float payment_amount;
            printf("\nEnter payment amount: ");
            scanf("%f", &payment_amount);

            // Deduct payment_amount from total_payment
            total_payment -= payment_amount;
        }

        // Write the line as is to the temporary file
        fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%.2f\n", record_username, room_number, room_rate, electricity, water, days_to_pay, total_payment);
    }

    fclose(file);
    fclose(tempFile);

    if (!record_found) {
        printf("Record not found.\n");
        remove("temp_records.txt");  // Remove the temporary file if record not found
        getch();
    } else {
        // Remove the original file and rename the temporary file to the original file
        remove("tenant_records.txt");
        rename("temp_records.txt", "tenant_records.txt");
    }
}


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
    char dataToRemove[MAX_LINE_LENGTH];
    char password[20];
    int counter = 0;

    // Get input for the input file name and data to remove
    system("cls");
    displayMessage();
    printf("\n");
    getInput(inputFile, sizeof(inputFile), "Enter the input file name", ".txt or .csv");
    getInputWithoutExtension(dataToRemove, sizeof(dataToRemove), "Enter the data to remove");

    // Generate the output file name based on the input file name
    char outputFile[MAX_LINE_LENGTH];
    snprintf(outputFile, sizeof(outputFile), "%s", inputFile);

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
    }
}
//=======
void addBill(){
    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
    }

    char username_search[256];

    // Get input for search
    system("cls");
    displayMessage();
    printf("\nEnter username: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0';  // Remove the newline character

    for (int i = 0; username_search[i]; i++) {
        username_search[i] = toupper(username_search[i]);
    }

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
        char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ",");
        char *days_to_pay = strtok(NULL, ",");
        float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float

        // Trim whitespaces from the found record values
        trim_whitespace(record_username);

        // Compare with the provided username
        if (strcmp(record_username, username_search) == 0) {
            // Display the found record along with total_payment
            printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");

            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
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
            fprintf(tempFile, "%s,%s,%s,%.2f,%.2f,%s,%.2f\n", record_username, room_number, room_rate, new_electricity, new_water, days_to_pay, total_payment);
        } else {
            // Write the unchanged record to the temp file
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%.2f\n", record_username, room_number, room_rate, electricity, water, days_to_pay, total_payment);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!record_found) {
        printf("Record not found.\n");
        remove("temp_records.txt");  // Remove the temporary file if record not found
        getch();
    }
    else{
    // Remove the original file and rename the temporary file to the original file
    remove("tenant_records.txt");
    rename("temp_records.txt", "tenant_records.txt");
    }
}

//Add Next Month Records--------------------------------------------------------------------------------------------------------------------------


void AddNextMonth() {
    FILE *newFile, *nameContainerFile;
    struct Tenant tenant;

    // Get input for the month
    char month[10];
    printf("Enter the month: ");
    scanf("%s", month);

    // Construct the file name with the format "month_tenant_records.txt"
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s_tenant_records.txt", month);

    // Open a new file for writing
    newFile = fopen(fileName, "w");
    if (newFile == NULL) {
        perror("Error creating new file");
        exit(EXIT_FAILURE);
    }

    // Write header to the new file
    fprintf(newFile, "Username,Room Rate,Water Bill,Electricity Bill,Days to Pay,Total Bill\n");

    // Get input for the number of tenant records
    int numRecords;
    printf("Enter the number of tenant records you want to add: ");
    scanf("%d", &numRecords);

    // Loop based on the number of records
    for (int i = 0; i < numRecords; i++) {
        printf("\nEnter Tenant Information (Record %d):\n", i + 1);

        // Get input for username
        printf("Username: ");
        scanf("%s", tenant.username);

        // Get input for room rate
        printf("Room Rate: ");
        scanf("%d", &tenant.roomRate);

        // Get input for water bill
        printf("Water Bill: ");
        scanf("%f", &tenant.waterBill);

        // Get input for electricity bill
        printf("Electricity Bill: ");
        scanf("%f", &tenant.electricityBill);

        // Get input for days to pay
        printf("Days to Pay: ");
        scanf("%d", &tenant.daysToPay);

        // Calculate total bill
        float totalBill = tenant.roomRate * tenant.daysToPay + tenant.waterBill + tenant.electricityBill;

        // Write tenant information to the file
        fprintf(newFile, "%s,%.2d,%.2f,%.2f,%d,%.2f\n", tenant.username, tenant.roomRate, tenant.waterBill, tenant.electricityBill, tenant.daysToPay, totalBill);
    }

    // Close the file
    fclose(newFile);

    printf("\nNew file '%s' created successfully.\n", fileName);

    // Open the name container file for appending
    nameContainerFile = fopen("name_container.txt", "a");
    if (nameContainerFile == NULL) {
        perror("Error opening name container file");
        exit(EXIT_FAILURE);
    }

    // Write the new file name to the name container file
    fprintf(nameContainerFile, "%s\n", fileName);

    // Close the name container file
    fclose(nameContainerFile);

    printf("File name added to 'name_container.txt'.\n");
    printf("Tenant records have been saved.\n");

    // Flush the output buffer to ensure messages are displayed before the function ends
    fflush(stdout);
}

//additional functions
int isUsernameExists(const char *username) {
    FILE *file = fopen("tenant_records.txt", "r");

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

//<<<<<<< Updated upstream
//=======


//Analysis: remove water bill and electricity bill merge it to total payment column
//Do not display how many tenants in each room
//
//Bugs: cannot modify data 
//things to work on:
    // Search: searching username is sensitive to case: pag mag search: jerry != JERRY (ichange pa ni? or should it stay)
    // Search: ang format sa output.

    //List Records: Format sa output.
    
    //Also general error trapping.

    //if nakoy mali somewhere eli i mention lang ko -c
    
//>>>>>>> Stashed changes
