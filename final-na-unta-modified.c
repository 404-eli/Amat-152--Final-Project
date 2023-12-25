#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100
#define ADMIN_PASSWORD "admin123"

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void createUserFile() {
    char adminPassword[MAX_PASSWORD_LENGTH];

    printf("Enter admin password: ");
    scanf("%s", adminPassword);

    if (strcmp(adminPassword, ADMIN_PASSWORD) != 0) {
        printf("Invalid admin password. Access denied.\n");
        return;
    }

    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    int numUsers;

    printf("Enter the number of users: ");
    scanf("%d", &numUsers);

    fprintf(file, "username | password\n"); // Header for the notepad

    int i;
    for (i = 0; i < numUsers; i++) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        printf("Enter username for user %d: ", i + 1);
        scanf("%s", username);

        printf("Enter password for user %d: ", i + 1);
        scanf("%s", password);

        fprintf(file, "%s | %s\n", username, password);
    }

    fclose(file);

    printf("User data written to users.txt successfully.\n");
}

void displayUserFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 5]; // Extra space for username, password, and separator

    // Skip the first line (header)
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " | ");
        printf("Username: %s\n", token);
    }

    fclose(file);
}

int validateLogin(const char *providedUsername, const char *providedPassword) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    struct User users[MAX_USERS];
    int numUsers = 0;

    // Read user data from the file
    while (fscanf(file, "%s | %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
        if (numUsers >= MAX_USERS) {
            printf("Maximum number of users reached.\n");
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    // Check if the entered username and password match
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(providedUsername, users[i].username) == 0 && strcmp(providedPassword, users[i].password) == 0) {
            return 1; // Login successful
        }
    }

    return 0; // Login failed
}

void logout() {
    printf("Logged out successfully!\n");
}

int main() {
    int choice;
    do {
        printf("\n1. Create User File\n2. Display User Data\n3. Login\n4. Logout\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createUserFile();
                break;
            case 2:
                displayUserFile();
                break;
            case 3: {
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                int loggedIn = 0;

                while (!loggedIn) {
                    printf("Please enter your username (or 'exit' to quit): ");
                    scanf("%s", username);

                    if (strcmp(username, "exit") == 0) {
                        printf("Exiting the program...\n");
                        return 0;
                    }

                    printf("Please enter your password: ");
                    scanf("%s", password);

                    if (validateLogin(username, password)) {
                        printf("Login successful!\n");
                        loggedIn = 1;
                    } else {
                        printf("Invalid username or password.\n");
                    }
                }
                break;
            }
            case 4:
                logout();
                break;
            case 5:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}


/*
Additionals:
- append additional users
- admin password should be confidential
- tenant panel should not have the access to display user profiles
*/