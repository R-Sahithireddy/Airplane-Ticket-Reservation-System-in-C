#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for the maximum number of users and flights
#define MAX_USERS 100
#define MAX_FLIGHTS 50

// Define structures for user and flight information
struct user {
    char username[20];
    char password[20];
    int seats;
    float price;
    float balance;
    char from[50];
    char to[50];
};

struct flight {
    char from[20];
    char to[20];
    int seats;
    float price;
    char status[10];
};

// Declare global variables for user and flight information
struct user users[MAX_USERS];
struct flight flights[MAX_FLIGHTS];

int num_users = 0;
int num_flights = 0;

// Function to display the main menu options
void display_menu() {
    printf("\nMain Menu\n");
    printf("1. Login\n");
    printf("2. Sign up\n");
    printf("3. Book a flight\n");
    printf("4. Cancel a flight\n");
    printf("5. Edit a booking\n");
    printf("6. View all flights\n");
    printf("7. View my bookings\n");
    printf("8. Logout\n");
    printf("Enter your choice (1-8): ");
}

// Function to handle user login
int login() {
    char username[20], password[20];
    int i;

    printf("\nEnter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Search for the user in the array of users
    for (i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful.\n");
            return i;
        }
    }

    printf("\nInvalid username or password.\n");
    return -1;
}

// Function to handle user sign up
void signup() {
    char username[20], password[20];

    printf("\nEnter a username: ");
    scanf("%s", username);

    // Check if the username already exists
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0) {
            printf("\nUsername already exists. Please choose a different one.\n");
            return;
        }
    }

    printf("Enter a password: ");
    scanf("%s", password);

    // Add the new user to the array of users
    strcpy(users[num_users].username, username);
    strcpy(users[num_users].password, password);
    num_users++;

    printf("\nSign up successful. Please login to continue.\n");
}

// Function to handle flight booking
void book_flight(int user_index) {
    char from[20], to[20];
    int date, time, seats, flight_index;

    printf("\nEnter the details of the flight you want to book:\n");
    printf("From: ");
    scanf("%s", from);
    printf("To: ");
    scanf("%s", to);

    // Search for the flight in the array of flights
    for (int i = 0; i < 1; i++){
        if (strcmp(from, flights[i].from) == 0 && strcmp(to, flights[i].to) == 0) {
            printf("\nFlight found:\n");
            printf("From: %s\n", flights[i].from);
            printf("To: %s\n", flights[i].to);
            printf("Seats available: %d\n", flights[i].seats);
            printf("Price per seat: %.2f\n", flights[i].price);

            // Prompt the user to enter the number of seats to book
            printf("Enter the number of seats you want to book: ");
            scanf("%d", &seats);

            // Check if there are enough seats available
            if (flights[i].seats < seats) {
                printf("\nSorry, there are not enough seats available.\n");
                return;
            }

            // Update the flight information
            flight_index = i;
            flights[i].seats -= seats;
            strcpy(flights[i].status, "Booked");

            // Display the booking summary
            printf("\nBooking successful:\n");
            printf("From: %s\n", flights[i].from);
            printf("To: %s\n", flights[i].to);
            printf("Seats booked: %d\n", seats);
            printf("Total price: %.2f\n", seats * flights[i].price);

            // Add the booking information to the user's account
            strcpy(users[user_index].from, flights[flight_index].from);
            strcpy(users[user_index].to, flights[flight_index].to);
            users[user_index].seats = seats;
            users[user_index].price = seats * flights[flight_index].price;

            return;
        }
    }

    printf("\nFlight not found.\n");
}

// Function to handle flight cancellation
void cancel_flight(int user_index) {
    char from[20], to[20];
    int i;

    printf("\nEnter the details of the flight you want to cancel:\n");
    printf("From: ");
    scanf("%s", from);
    printf("To: ");
    scanf("%s", to);

    // Search for the booking in the user's account
    for (i = 0; i < 2; i++) {
        if (strcmp(from, users[user_index].from) == 0 && strcmp(to, users[user_index].to) == 0) {
            printf("\nBooking found:\n");
            printf("From: %s\n", users[user_index].from);
            printf("To: %s\n", users[user_index].to);
            printf("Seats booked: %d\n", users[user_index].seats);
            printf("Total price: %.2f\n", users[user_index].price);

            // Update the flight information
            flights[i].seats += users[user_index].seats;
            strcpy(flights[i].status, "Available");

            // Remove the booking information from the user's account
            strcpy(users[user_index].from, "");
            strcpy(users[user_index].to, "");
            users[user_index].seats = 0;
            users[user_index].price = 0.0;

            printf("\nCancellation successful.\n");
            return;
        }
    }

    printf("\nBooking not found.\n");
}

// Function to handle editing of user information
void edit_user(int user_index) {
    int choice;

    printf("\nEnter the information you want to edit:\n");
    printf("1. Username\n");
    printf("2. Password\n");
    printf("3. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nEnter your new username: ");
            scanf("%s", users[user_index].username);
            printf("\nUsername updated successfully.\n");
            break;

        case 2:
            printf("\nEnter your new password: ");
            scanf("%s", users[user_index].password);
            printf("\nPassword updated successfully.\n");
            break;

        case 3:
            return;

        default:
            printf("\nInvalid choice.\n");
            break;
    }
}

// Function to handle payment
void make_payment(int user_index) {
    float amount;
    users[user_index].balance = 6000;
    printf("\nEnter the amount to be paid: ");
    scanf("%f", &amount);

    if (users[user_index].balance < amount) {
        printf("\nInsufficient balance. Please add more funds.\n");
        return;
    }

    users[user_index].balance -= amount;
    printf("\nPayment successful. Your new balance is %.2f.\n", users[user_index].balance);
}

int main() {
    int choice, user_index = -1;
    
    
    strcpy(flights[0].from, "Bengaluru");
    strcpy(flights[0].to, "Mumbai" );
    flights[0].seats = 10;
    flights[0].price = 3000.00;
    
    strcpy(flights[0].from, "Bengaluru");
    strcpy(flights[0].to, "Chennai" );
    flights[0].seats = 10;
    flights[0].price = 2300.00;
    while (1) {
        // Display the main menu
        printf("\nWelcome to Airline Reservation System\n");
        printf("1. Login\n");
        printf("2. Sign up\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                user_index = login();
                if (user_index == -1) {
                    printf("\nLogin failed. Please try again.\n");
                } else {
                    printf("\nLogin successful. Welcome, %s!\n", users[user_index].username);
                    while (1) {
                        // Display the user menu
                        printf("\n1. Book a flight\n");
                        printf("2. Cancel a flight\n");
                        printf("3. Edit user information\n");
                        printf("4. Make a payment\n");
                        printf("5. Logout\n");
                        printf("Choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                book_flight(user_index);
                                break;

                            case 2:
                                cancel_flight(user_index);
                                break;

                            case 3:
                                edit_user(user_index);
                                break;

                            case 4:
                                make_payment(user_index);
                                break;

                            case 5:
                                printf("\nLogout successful. Goodbye, %s!\n", users[user_index].username);
                                user_index = -1;
                                break;

                            default:
                                printf("\nInvalid choice.\n");
                                break;
                        }

                        if (user_index == -1) {
                            break;
                        }
                    }
                }
                break;

            case 2:
                signup();
                break;

            case 3:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
                break;

            default:
                printf("\nInvalid choice.\n");
                break;
        }
    }

    return 0;
}
