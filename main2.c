#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

#define ADMIN_PASSWORD "admin123"
#define ADMIN_USERNAME "admin"
#define MAX_LINE_LENGTH 100 //deleting records
#define MAX_FILE_NAME 50   //displaying records
#define MAX_BUFFER_SIZE 100 //displaying records
#define MAX_FILENAME_LEN 100//search
#define MAX_USERNAME_LEN 50//search
#define MAX_LINE_LEN 1000//search

void displayMessage();//done
void menu();//done
void writeHeader(FILE *record, const char *header);//allowed
int isNameExists(const char *filename, const char *name);
void trim_whitespace(char *str);//remove later
void toUpperCase(char *str);

//tenant panel functions----------------------------------------------------------------------------------------------------
void tenantPanel(char *username);
//can be found on both 
void logIn();//partially done
void logOut();//done

//admin panel functions----------------------------------------------------------------------------------------------------
void adminPanel();//done
void addTenantRecord();//done
void AddNextMonth();
void searchrecords();//done


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

//payment------------------------------------------------------------------------------------------------------------------------------------------------------------
int payment_search();
void payment();//starting
void tryAgain();//done

//deleterecord funcs--------------------------------------------------------------------------------------------------------------
void getInputWithoutExtension(char *input, size_t size, const char *prompt);
void getInput(char *input, size_t size, const char *prompt, const char *fileExtensions);
void removeDataFromFile(const char *inputFile, const char *outputFile, const char *dataToRemove);
void deleterecords();

//main function-----------------------------------------------------------------------------------------------------------
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
            logIn();break;
        case 'T':
            logIn();break;
        case 'E':
            printf("\n\nThank you for using our service!");exit(0);
        default:
            printf("\n\nIncorrect Input\nAny key to continue");getch();break;
        }
    }
}

void adminPanel(){
    int choice;
	while (1)
	{
        system("cls");
        displayMessage();
		printf("\n MAIN MENU: \n\n Add records:\n A : Add new Tenant Record.\n N : Add Monthly Records.\n");
        printf("\n Find existing records:\n L : List of records\n S : Searching records");
		printf("\n\n P : Payment");
		printf("\n\n D : Delete records.\n O : Log out\nChoice: ");
		choice=getche();
		choice=toupper(choice);
        fflush(stdin);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addTenantRecord();break;
			case 'L':
				displayList();break;
			case 'N':
				AddNextMonth();break;
			case 'S':
				searchFile();break;
			case 'D':
				deleterecords();break;
			case 'O':
                system("cls");logOut();break;
			default:
				printf("\n\nIncorrect Input\nAny key to continue");getch();
		}
	}
}

//ADD TENANT RECORDS ONLY---------------------------------------------------------------------------------------------------------
void addTenantRecord() {
	int i;
    FILE *record;
    FILE *info;
    record = fopen("tenant_records.txt", "a+");
    if (record == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    system("cls");
    displayMessage();
    printf("\nEntering for Tenants Database: \n\n");
    do {// Get input for username and check for existing username
        printf("Enter Username: ");
        scanf("%s", tenant.username); toUpperCase(tenant.username);
        
        if (isNameExists("tenant_records.txt", tenant.username)) {// Check if the username already exists
            printf("Username already exists. Please enter a different username.\n");
        }
    } while (isNameExists("tenant_records.txt", tenant.username));

    // Get input for other fields
    printf("Enter Room Number: ");
    scanf("%s", tenant.roomNumber); toUpperCase(tenant.roomNumber);

    while ((printf("Enter Room Rate: ") && scanf("%d", &tenant.roomRate) == 1) ? (fflush(stdin), 0) : (printf("Invalid Input: Enter a number.\n") && fflush(stdin), 1));
    while ((printf("Enter Water Bill: ") && scanf("%f", &tenant.waterBill) == 1) ? 0 : (printf("Invalid Input: Enter a number.\n") && fflush(stdin), 1));
    while ((printf("Enter Electricity Bill: ") && scanf("%f", &tenant.electricityBill) == 1) ? 0 : (printf("Invalid Input: Enter a number.\n") && fflush(stdin), 1));
    while ((printf("Enter Number of Days to Pay: ") && scanf("%d", &tenant.daysToPay) == 1) ? (fflush(stdin), 0) : (printf("Invalid Input: Enter a number.\n") && fflush(stdin)));

    // Calculate total_payment by multiplying room_rate and days_to_pay, then adding electricity and water
    float total_payment = tenant.roomRate * tenant.daysToPay + tenant.waterBill + tenant.electricityBill;

    writeHeader(record, "Username, Room Number, Room Rate, Water Bill, Electricity Bill, Days to Pay, Total Payment");
    // Append the record with the new total_payment column
    fprintf(record, "%s, %s, %d, %.2f, %.2f, %d, %.2f\n",
            tenant.username, tenant.roomNumber, tenant.roomRate, tenant.waterBill, tenant.electricityBill, tenant.daysToPay, total_payment);

    fclose(record);

    //write the log-in information
    info = fopen("log_info.txt", "a+");
    if (info != NULL){
            writeHeader(info, "Username, Password");
            fprintf(info, "%s, %s\n", tenant.username, tenant.roomNumber);
    }

    fclose(info);
    printf("\n 1 record successfully added\n Press any key to exit: ");getch();
    system("cls");
}
//END--------------------------------------------------------------------------------------------------------------------------------------

//DisplayRecords----------------------------------------------------------------------------------------------------------------------------------
//main display
int displayList() {
    int choice;
    char buffer[MAX_FILE_NAME];

    do {
        system("cls"); displayMessage();
        printf("\nMenu:\n");// Display menu
        printf("1. Print Monthly Tenant Records\n");
        printf("2. Print Tenant Database\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1)
        {
            fflush(stdin);
            switch (choice) {
            case 1:
                printFile();break;
            case 2:
                listrecords();break;
            case 3:
                printf("\n\nReturning to MAIN MENU\nEnter any key to continue.");getch();break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
            }
        }
        else{
            printf("Invalid Input: Please enter an integer.");
            fflush(stdin);
        }
    } while (choice != 3);
    return 0;
}

// Function to print the content of a file
void printFile() {
    int i;
    char userFile[MAX_FILE_NAME]; char month[20];
    char year[5]; char buffer[256];

    FILE *file;
    FILE *month_rec = fopen("name_container.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printAvailableFiles();
    printf("Enter month: "); scanf("%s", month); toUpperCase(month);
    printf("Enter year: "); scanf("%s", year);

    // Construct the file name with the format "monthyear.txt"
    snprintf(userFile, sizeof(userFile), "%s%s.txt", month, year);

    file = fopen(userFile, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", userFile);
    }
    else{
        system("cls");
        displayMessage();
        printf("\n\n\t\tPrinting %s %s.....\n\n", month, year);
        printf("\n%-15s%-15s%-15s%-15s%-15s%15s\n", "Username", "Room Number", "Room Rate", "Bills", "Days to Pay", "Total Payment");
        for (i = 0; i < 100; i++)printf("=");
        printf("\n");
        // Skip the first line (header)
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            return;
        }
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            char *username = strtok(buffer, ","); char *room_number = strtok(NULL, ",");
            char *room_rate = strtok(NULL, ","); char *electricity = strtok(NULL, ",");
            char *water = strtok(NULL, ","); char *days_to_pay = strtok(NULL, ",");
            char *total_payment = strtok(NULL, "\n"); // Adjust to read until the end of the line

            float bill = atof(electricity) + atof(water);

            printf("%-15s%-15s%-15s%-15.2f%-15s%10s\n", username, room_number, room_rate, bill, days_to_pay, total_payment);
        }
        for (i = 0; i < 100; i++)printf("=");
    }

    fclose(file);
    fclose(month_rec);
    getch();
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
    displayMessage();
    printf("\n\n\t\tTenant Database\n\n");
    printf("\n%-15s%-15s%-15s%-15s%15s\n", "Username", "Room Number", "Room Rate", "Days to Pay", "Total Payment");
    for (i = 0; i < 90; i++)printf("=");
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
        char *username = strtok(line, ","); char *room_number = strtok(NULL, ",");
        char *room_rate = strtok(NULL, ","); char *electricity = strtok(NULL, ",");
        char *water = strtok(NULL, ","); char *days_to_pay = strtok(NULL, ",");
        char *total_payment = strtok(NULL, "\n"); // Adjust to read until the end of the line

        printf("%-15s%-15s%-15s%-15s%10s\n", username, room_number, room_rate, days_to_pay, total_payment);
    }

    for (i = 0; i < 90; i++)printf("=");

    fclose(record);
    getchar(); // Consume newline character
}
//END--------------------------------------------------------------------------------------------------------------------------

//SEARCH FUNCTION----------------------------------------------------------------------------------------------------------------------
int searchFile() {
    int choice;
    do {
        system("cls");
        displayMessage();
        printf("\nChoose an option:\n");
        printf("1. Search Tenant Records File\n2. Search Monthly Records File\n3. Exit\nEnter your choice: ");
        if (scanf("%d", &choice) == 1)
        {
            fflush(stdin);
            switch (choice) {
                case 1:
                    searchrecords(); break;//FOR MAIN RECORDS
                case 2:
                    searchMonthly(); break;//FOR MONTHLY RECORDS
                case 3:
                    printf("Exiting program. Goodbye!\n"); break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        }
        else printf("Invalid input: Please enter an integer\n");
    } while (choice != 3);
    return 0;
}

void searchrecords() {
    int record_found = 0, i;

    FILE *file = fopen("tenant_records.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        getch();
    }
    else{
        char username_search[256];

        // Get input for search
        // Get input for search
        system("cls");
        displayMessage();
        printf("\n\n\t\tTenant Database\n\n");
        printf("\nEnter username: ");
        scanf("%s", username_search);
        toUpperCase(username_search);

        // Skip the first line (header)
        char line[256];
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            return;
        }

        printf("\n\n%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
        for (i = 0; i < 90; i++)printf("=");
        printf("\n");

        while (fgets(line, sizeof(line), file) != NULL) {
            char *record_username = strtok(line, ","); char *room_number = strtok(NULL, ",");
            char *room_rate = strtok(NULL, ","); char *electricity = strtok(NULL, ",");
            char *water = strtok(NULL, ","); char *days_to_pay = strtok(NULL, ",");
            float total_payment = atof(strtok(NULL, "\n"));  // Retrieve total_payment as a float
            trim_whitespace(record_username); // Trim whitespaces from the found record values
            // Compare with the provided username
            if (strcmp(record_username, username_search) == 0) {
                // Display the found record in a single line
                float bill = atof(electricity) + atof(water);
                printf("%-15s%-15s%-15s%-10.2f%-15s%8.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
                record_found = 1;
                break;
            }
        }
            if (!record_found) {
            printf("\nRecord not found.\n");
        }
        for (i = 0; i < 90; i++)printf("=");
    }
    fclose(file); printf("\n\nPress any key to continue."); getch();
}

int searchMonthly() {
    char month[10];
    char year[5];
    char filename[MAX_FILENAME_LEN];
    char username[MAX_USERNAME_LEN];

    system("cls");
    displayMessage();
    printAvailableFiles();
    
    printf("\nEnter month: ");
    scanf("%s", month);
    toUpperCase(month);
    printf("Enter year: ");
    scanf("%s", year);

    snprintf(filename, sizeof(filename), "%s%s.txt", month, year);
    
    system("cls");
    displayMessage();
    printf("\n\t\tSearching in %s %s...\n\n", month, year);
    printf("Enter the username to search for: ");
    scanf("%s", username);
    toUpperCase(username);

    searchByUsername(filename, username);

    return 0;
}

void searchByUsername(const char *filename, const char *username) {
    int i, record_found = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
    }
    else{
    char line[256];
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        return;
    }
    printf("\n\n");
    printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
    for (i = 0; i < 90; i++) printf("=");
    printf("\n");

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
        if (strcmp(record_username, username) == 0) {
            // Display the found record in a single line
        
            float bill = atof(electricity) + atof(water);
            printf("%-15s%-15s%-15s%-10.2f%-15s%8.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
            record_found = 1;
            break;
        }
    }
        if (!record_found) {
            printf("Username not found in %s\n", filename);
        }
        for (i = 0; i < 90; i++)printf("=");
    }
    fclose(file);
    printf("\n\nPress any key to continue.");
    getch();
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

//END----------------------------------------------------------------------------------------------------------------------------------------

/// PAYMENT FUNCTION-------------------------------------------------------------------------------------------------------
int payment_search(){
    int choice;

    do {
        system("cls");
        displayMessage();
        printf("\nChoose an option:\n");
        printf("1. Payment for month\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 0)
        {
            fflush(stdin);
            switch (choice) {
            case 1:
                payment();//FOR MAIN RECORDS
                break;
            case 2:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
            }
        }
        else{
            printf("Invalid input: Please enter an integer.");
            fflush(stdin);
        }
    } while (choice != 2);

    return 0;
}

void payment() {
    char userFile[MAX_FILE_NAME]; char username_search[256];
    char line[256]; char month[15];
    char year[6];
    int i, record_found = 0;

    FILE *file, *tempFile;

    tempFile = fopen("temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp_records.txt for writing");
        return;
    }
    else{
        system("cls");
        displayMessage();
        printAvailableFiles();
        printf("\nEnter the month: ");
        scanf("%s", month);
        toUpperCase(month);
        printf("Enter year: ");
        scanf("%s", year);

        // Construct the file name with the format "monthyear.txt"
        snprintf(userFile, sizeof(userFile), "%s%s.txt", month, year);

        file = fopen(userFile, "r");
        if (file == NULL) {
            perror("Error opening the file");
            fclose(tempFile);
            return;
        }

        // Get input for search
        system("cls");
        displayMessage();
        listrecords();
        printf("Searching in %s %s.....\n", month, year);
        printf("Enter username: ");
        scanf("%s", username_search);
        toUpperCase(username_search);

        // Skip the first line (header)
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading the header.\n");
            fclose(file);
            fclose(tempFile); 
            return;
        }

        fprintf(tempFile, "%s", line);  // Write the header to the temp file

        printf("\n%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
        for (i = 0; i < 90; i++)printf("=");

        while (fgets(line, sizeof(line), file) != NULL) {
            char *record_username = strtok(line, ","); char *room_number = strtok(NULL, ",");
            char *room_rate = strtok(NULL, ","); char *electricity = strtok(NULL, ",");
            char *water = strtok(NULL, ","); char *days_to_pay = strtok(NULL, ",");
            float total_payment = atof(strtok(NULL, "\n")); 
            trim_whitespace(record_username);// Trim whitespaces from the found record values
            // Compare with the provided username
            if (strcmp(record_username, username_search) == 0) {
                // Display the found record along with total_payment

                float bill = atof(electricity) + atof(water);
                printf("\n%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);
                for (i = 0; i < 90; i++)printf("=");
                printf("\n");
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
            printf("\nRecord not found.\n");
            remove("temp_records.txt");
            getch();
        } else {
            // Remove the original file and rename the temporary file to the original file
            remove(userFile);
            rename("temp_records.txt", userFile);
        }
    }
}

//END----------------------------------------------------------------------------------------------------------------------

///DELETING RECORDS---------------------------------------------------------------------------------------------------------
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
        return;
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
    printAvailableFiles();
    getInput(inputFile, sizeof(inputFile), "Enter the input file name", ".txt or .csv");
    getInputWithoutExtension(dataToRemove, sizeof(dataToRemove), "Enter the data to remove");

    // Generate the output file name based on the input file name
    char outputFile[MAX_LINE_LENGTH];
    snprintf(outputFile, sizeof(outputFile), "%s", inputFile);

    // Prompt for admin password with limited attempts
    do {
        printf("Please enter the admin password: ");
        scanf("%19s", password);

        if (strcmp(password, ADMIN_PASSWORD) == 0) {
            // Call the function to remove data from the file
            removeDataFromFile(inputFile, outputFile, dataToRemove);
        } else {
            printf("Invalid Password! \n");
            counter++;
        }
    } while (strcmp(password, ADMIN_PASSWORD) != 0 && counter < 5);

    if (counter >= 5) {
        printf("Maximum attempts reached!\n");
    }
}
//END---------------------------------------------------------------------------------------------------------------------------


//Add Next Month Records--------------------------------------------------------------------------------------------------------------------------
void AddNextMonth() {
    char month[10], year[5];
    char fileName[50];

    FILE *file = fopen("tenant_records.txt", "r");
    FILE *newFile, *nameContainerFile;

    if (file == NULL) {
        perror("\n\nError opening the file.\n");
        printf("\nAny key to continue");
        getch();
        return;
    }
    // Get input for the month
    system("cls");
    // displayMessage();
    printf("\nEnter the month: ");
    scanf("%s", month);
    toUpperCase(month);
    printf("Enter year: ");
    scanf("%s", year);

    // Construct the file name with the format "monthyear.txt"
    snprintf(fileName, sizeof(fileName), "%s%s.txt", month, year);

    // Open the name container file for appending
    nameContainerFile = fopen("name_container.txt", "a+");
    if (nameContainerFile == NULL) {
        perror("Error opening name container file");
        fclose(nameContainerFile);  // Close the file before returning
        return;
    }

    // Check if the file already exists in name_container.txt
    if (isNameExists("name_container.txt", fileName) == 1) {
        printf("Error: File '%s' already exists in name_container.txt.\n", fileName);
        fclose(nameContainerFile);  // Close the file before returning
        return;
    }

    // Open a new file for writing fileName = MONTHYEAR.txt
    newFile = fopen(fileName, "w");
    if (newFile == NULL) {
        perror("Error creating new file");
        fclose(nameContainerFile);  // Close the name container file before returning
        return;
    }


    char line[256];

    // Skip the first line (header)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error reading the header.\n");
        fclose(file);
        return;
    }

    // Write the header to the new file
    fprintf(newFile, "%s", line);
    fprintf(nameContainerFile, "%s,\n", fileName);

    // Iterate through all records in the file
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

        // Display the record details
        printf("%-15s%-15s%-15s%-10s%-10s%15s\n", "Username", "Room Number", "Room Rate", "Bill", "Days to Pay", "Total Payment");
        float bill = atof(electricity) + atof(water);
        printf("%-15s%-15s%-15s%-10.2f%-15s%10.2f\n", record_username, room_number, room_rate, bill, days_to_pay, total_payment);

        // Get new electricity and water bill values from the user
        float new_electricity, new_water;
        int new_daystopay;
        printf("\nEnter new electricity bill for %s: ", record_username);
        scanf("%f", &new_electricity);
        printf("Enter new water bill for %s: ", record_username);
        scanf("%f", &new_water);
        printf("Enter how many days %s would pay: ", record_username);
        scanf("%d", &new_daystopay);

        float new_bill = new_electricity + new_water;
        float new_total_payment = new_bill + (atof(room_rate) * new_daystopay);

        // Append the modified record to the new file
        fprintf(newFile, "%s,%s,%s,%.2f,%.2f,%d,%.2f\n", record_username, room_number, room_rate, new_electricity, new_water, new_daystopay, new_total_payment);
    }

    printf("\nNew file '%s' created successfully.\n", fileName);

    // Close the files
    fclose(file);
    fclose(newFile);
    fclose(nameContainerFile);
}
//END----------------------------------------------------------------------------------------------------------------------------


//TENANT PANEL------------------------------------------------------------------------------------------------------------------------------
void tenantPanel(char *username){
    int choice;
    char month[10], year[5];
    char filename[20];

    while (1)
    {
        system("cls");
        displayMessage();
        printf(" B : See Monthly Balance\n O : Log out\nChoice: ");
        choice = getche();
        choice = toupper(choice);
        switch (choice)
        {
        case 'B':
            printf("\nEnter month: ");scanf("%s", month);toUpperCase(month);
            printf("Enter year: ");scanf("%s", year);
            snprintf(filename, sizeof(filename), "%s%s.txt", month, year);
            printf("%s", filename);
            searchByUsername(filename, username);
            break;
        case 'O':
            system("cls");
            menu();
            break;
        default:
            printf("\n\nIncorrect Input");
            printf("\nAny key to continue");
            getch();
            break;
        }
    }

    menu();
}

//LOGIN---------------------------------------------------------------------------------------------------------------------------
void logIn() {
    char admin[] = "admin";
    char admin_pass[] = "admin123";
    char username_in[10];
    char password_in[10];
    char buffer[256];
    int found = 0;

    system("cls");
    displayMessage();
    printf("Enter username: ");
    scanf("%s", username_in);
    printf("Enter password: ");
    scanf("%s", password_in);
    
    if (strcmp(username_in, admin) == 0 && strcmp(password_in, ADMIN_PASSWORD) == 0)
    {
        adminPanel();
    }

    FILE *login_info = fopen("log_info.txt", "r");

    if (login_info != NULL)
    {
        if (fgets(buffer, sizeof(buffer), login_info) == NULL) {
            printf("Error reading the header.\n");
            fclose(login_info);
            return;
        }

        while (fgets(buffer, sizeof(buffer), login_info) != NULL) {
            char *record_username = strtok(buffer, ",");
            char *room_number = strtok(NULL, "\n");

            // Trim whitespaces from the found record values
            trim_whitespace(record_username);
            trim_whitespace(room_number);
            trim_whitespace(username_in);
            trim_whitespace(password_in);

            if (strcmp(record_username, username_in) == 0 && strcmp(room_number, password_in) == 0) {
                found = 1;
                break;
            }
        }

        fclose(login_info);

        if (found) {
            tenantPanel(username_in);
        }
        else {
            tryAgain();
        } 
    }
    else{
        printf("Invalid Log-in! Please wait for the admin\n");
        getch();
        fflush(stdin);
    }
}

void logOut(){
    printf("\n\nLogged out!\n\n");
    getch();
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
//END----------------------------------------------------------------------------------------------------------------------------------

//additional functions----------------------------------------------------------------------------------------------------------------------
int isNameExists(const char *filename, const char *name) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0; // Return 0 assuming the file doesn't exist or there was an error
    }

    char line[256];

    // Skip the first line (header) of files other than name_container.txt which has no header
    if (strcmp(filename, "name_container.txt") == 1)  
    {
        
        if (fgets(line, sizeof(line), file) == NULL) {
            fclose(file);
            return 0; // Return 0 if there is an error reading the header
        }
    }

    // Search for the username in the records
    while (fgets(line, sizeof(line), file) != NULL) {
        char *record_name = strtok(line, ",");
        trim_whitespace(record_name);

        // Compare with the provided username
        if (strcmp(record_name, name) == 0) {
            fclose(file);
            return 1; // Return 1 if the username already exists
        }
    }

    fclose(file);
    return 0; // Return 0 if the username does not exist
}

void writeHeader(FILE *record, const char *header) {
    fseek(record, 0, SEEK_END);
    if (ftell(record) == 0) {
        fprintf(record, "%s\n", header);
    }
}

// Trim leading and trailing whitespaces from a string
void trim_whitespace(char *str) {
    int start = 0, end = strlen(str) - 1, i;

    while (isspace((unsigned char)str[start])) {
        start++;
    }

    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    for (i = start; i <= end; i++) {
        str[i - start] = str[i];
    }

    str[i - start] = '\0';
}

void toUpperCase(char *str) {
	int i;
    for (i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
//<<<<<<< Updated upstream
//=======

//things to work on:
    // Search: searching username is sensitive to case: pag mag search: jerry != JERRY (ichange pa ni? or should it stay) ---- OKAY NA
    // Search: ang format sa output. ----- OKAY NA
    //List Records: Format sa output. ---- OKAY NA
    
    //Also general error trapping.

    //if nakoy mali somewhere eli i mention lang ko -c

//MODIFICATIONS-----------------------------------------------------------------------------------------------------------------
//list here::
//1. 
    
    //new mod for displayList() function : 
    // displayList() : if possible the user should only input the name of the file without the .txt extension
//>>>>>>> Stashed changes
