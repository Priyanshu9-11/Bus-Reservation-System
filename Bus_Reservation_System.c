#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Bus {
    int busNo;
    char source[100];
    char destination[100];
    int totalSeats;
    int availableSeats;
    float fare;
};

struct User {
    char username[20];
    char password[20];
};

void mainMenu();
void userMenu();
int loginUser(struct User[], int, char[], char[]);
void bookTicket(struct Bus[], int);
void cancelTicket(struct Bus[], int);
void checkBusStatus(struct Bus[], int);

void mainMenu() {
    printf("\n======================\n");
    printf("Bus Reservation System\n");
    printf("======================\n");
    printf("\n\n\n-----Main Menu-----\n");
    printf("1.Login\n");
    printf("2.Exit\n");
    printf("Enter your Choice: ");
}

void userMenu() {
    printf("\n\n\n\n------User Menu------\n");
    printf("1.View All Buses\n");
    printf("2.Book a ticket\n");
    printf("3.Cancel a ticket\n");
    printf("4.Check Bus Status\n");
    printf("5.Log Out\n");
    printf("Enter your choice: ");
}

int main() {
    struct User users[5] = {
        {"user1", "password1"}, {"user2", "password2"},
        {"user3", "password3"}, {"user4", "password4"},
        {"user5", "password5"},
    };
    int noofusers = 5;

    struct Bus buses[10] = {
        {101, " Nagpur", "Mumbai", 50, 50, 1550.0},
        {102, " Mumbai", "Bhopal", 40, 40, 4000.0},
        {103, " Nagpur", "Wardha", 30, 30, 300.0},
        {104, " Nagpur", "Pune", 30, 30, 1300.0},
        {105, " Pune", "Nagpur", 30, 30, 1000.0},
        {106, " Nagpur","Thane", 30, 30, 1800.0},
        {107, "Surat", "Nagpur", 30, 30, 1300.0}
        /*{103, "", "City F", 30, 30, 300.0},
        {103, "City E", "City F", 30, 30, 300.0},
        {103, "City E", "City F", 30, 30, 300.0},*/
    };
    int noofbuses = 7;

    int luID = -1;

    while(1) {
        if (luID == -1) {
            mainMenu();
            int c;
            scanf("%d", &c);
            if (c == 1) {
                char username[20];
                char password[20];
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                luID = loginUser(users, noofusers, username, password);
                if (luID == -1) {
                    printf("Login Failed!!\n");
                    printf("Check your Username and Password.\n");
                } else {
                    printf("@ Login Successful..\n");
                    printf("Welcome %s\n", username);
                }
            } else if(c == 2) {
                printf("Exiting the program.\n");
                break;
            } else {
                printf("Invalid Choice! Try Again.\n");
            }
        } else {
            userMenu();
            int uc;
            scanf("%d", &uc);
            switch(uc) {
                case 1:
                    viewAllBuses(buses,noofbuses);
                    break;
                case 2:
                    bookTicket(buses, noofbuses);
                    break;
                case 3:
                    cancelTicket(buses, noofbuses);
                    break;
                case 4:
                    checkBusStatus(buses, noofbuses);
                    break;
                case 5:
                    printf("Logging Out\n");
                    luID = -1;
                    break;
                default:
                    printf("Invalid Choice. Please Try Again Later.\n");
            }
        }
    }
    return 0;
}

int loginUser(struct User users[], int numofusers, char username[], char password[]) {
    for (int i = 0; i < numofusers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void bookTicket(struct Bus buses[], int numofbuses) {
    printf("\nEnter Bus Number: ");
    int busNo;
    scanf("%d", &busNo);

    int busIndex = -1;
    for (int i = 0; i < numofbuses; i++) {
        if (buses[i].busNo == busNo) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNo);
    } else {
        printf("Enter Number of Seats: ");
        int seatsToBook;
        scanf("%d", &seatsToBook);

        if (buses[busIndex].availableSeats < seatsToBook) {
            printf("Sorry, only %d seats are available.\n", buses[busIndex].availableSeats);
        } else {
            buses[busIndex].availableSeats -= seatsToBook;
            printf("Booking successful! %d seats booked on Bus Number %d.\n", seatsToBook, busNo);
        }
    }
}

void cancelTicket(struct Bus buses[], int numofbuses) {
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numofbuses; i++) {
        if (buses[i].busNo == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
    } else {
        printf("Enter Number of Seats to Cancel: ");
        int seatsToCancel;
        scanf("%d", &seatsToCancel);

        if (seatsToCancel > (buses[busIndex].totalSeats - buses[busIndex].availableSeats)) {
            printf("Error: You can't cancel more seats than were booked.\n");
        } else {
            buses[busIndex].availableSeats += seatsToCancel;
            printf("Cancellation successful! %d seats canceled on Bus Number %d.\n", seatsToCancel, busNumber);
        }
    }
}

void checkBusStatus(struct Bus buses[], int numofbuses) {
    printf("\nEnter Bus Number: ");
    int busNo;
    scanf("%d", &busNo);

    int busIndex = -1;
    for (int i = 0; i < numofbuses; i++) {
        if (buses[i].busNo == busNo) {
            busIndex = i;
            break;
        }
    }

    if (busIndex != -1) {
        printf("\nBus Number: %d\n", buses[busIndex].busNo);
        printf("Source: %s\n", buses[busIndex].source);
        printf("Destination: %s\n", buses[busIndex].destination);
        printf("Total Seats: %d\n", buses[busIndex].totalSeats);
        printf("Available Seats: %d\n", buses[busIndex].availableSeats);
        printf("Fare: %.2f\n", buses[busIndex].fare);
    } else {
        printf("Bus with Bus Number %d not found.\n", busNo);
    }
}
void viewAllBuses(struct Bus buses[], int numofbuses) {
    printf("\n====== All Bus Status ======\n");
    printf("\nBus Number\tSource\t\tDestination\tTotal Seats\tAvailable Seats\t\tFare\n");
    for (int i = 0; i < numofbuses; i++) {
        printf("%d\t\t%s\t\t%s\t\t%d\t\t\t%d\t\t%0.2f\n", buses[i].busNo, buses[i].source, buses[i].destination, buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
    }
}
