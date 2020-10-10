# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "car.h"

int input() {
    int inputt;
    scanf("%d", &inputt);
    return inputt;
}

void printSignIn() {
    printf("\nWelcome to the CPSC 305 Project Cars DB- please sign in.\nEnter a user type: ");
}

void addCar() {

    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    if (exists ==NULL) {
        printf("Enter a year: ");
        int year = input();
        printf("Enter a make: ");
        char maker[24];
        scanf("%s", maker);
        printf("Enter a category: ");
        char category[24];
        scanf("%s", category);
        printf("Enter miles: ");
        int mileage = input();
        printf("Enter cost: ");
        int price = input();
        car *newCar = add_car(carnum, year, maker, category, mileage, price);
        printf("Car added:\n");
        print_car(newCar);
    } else {
        printf("That carnum is already in use!\n");
    }
}

int validateUser() {
    printSignIn();

    char userIn[30];
    scanf("%s", userIn);

    if (strcmp(userIn, "owner") == 0) {
        return 1;
    } else if (strcmp(userIn, "shopper") == 0) {
        return 2;
    } else  {
        "Invalid user!";
        exit(1);
    }
}

int printMenu(int user) {

    if (user == 1) {
        printf("\nSelect one of the following:\n");
        printf("[1] Print Cars in DB           [2] Add a new Car\n");
        printf("[3] Delete via carnum          [4] Update cost via carnum\n");
        printf("[5] Update miles via carnum    [6] Save DB to file\n");
        printf("[7] Quit program\nEnter your choice: "); 
    } else {
        printf("\nSelect one of the following:\n");
        printf("[1] Show cars by year          [2] Show cars by make\n");
        printf("[3] Show cars by cost          [4] Show cars by category\n");
        printf("[5] Purchase car by carnum     [6] Quit program\n");
        printf("Enter your choice: "); 
    }

    return input();
}

void updateCarCost() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    if (exists != NULL) {
        printf("Enter the new cost: ");
        int cost = input();
        car *newCost = update_cost(carnum, cost);
        printf("Car updated:\n");
        print_car(newCost);
    } else {
        printf("That carnum isn't in the database!\n");
    }
   
}

void updateCarMiles() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    if (exists != NULL) {
        printf("Enter the new mileage: ");
        int miles = input();
        car *newMiles = update_miles(carnum, miles);
        printf("Car updated:\n");
        print_car(newMiles);
    } else {
        printf("That carnum isn't in the database!\n");
    }
   
}

void deleteCarPrompt() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    if (exists != NULL) {
        deleteCar(exists->carnum);
    } else {
        printf("That carnum isn't in the database!\n");
    }
   
}

void purchaseCarPrompt() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    if (exists != NULL) {
        purchase(exists->carnum);
        printf("Congratulations on the purhcase!\n");
    } else {
        printf("That carnum isn't in the database!\n");
    }
}

void getYearsPrompt() {
   car **matchingYears[MAX_CARS];
   printf("Enter a year: ");
   int year = input();
   int numMatches = get_year(*matchingYears, year);
   showMatches(*matchingYears, numMatches);
}

int runProgram(int user) {
    int choice;

    do {
        
        choice = printMenu(user);

        if (user == 1) {
            switch (choice) {
                case 1: {
                    printf("\nCars currently held in DB:");
                    show_cars();
                    break;
                }
                case 2: {
                    addCar();
                    break;
                }
                case 3: {
                    deleteCarPrompt();
                    break;
                }
                case 4: {
                    updateCarCost();
                    break;
                } 
                case 5: {
                    updateCarMiles();
                    break;
                } 
                case 6: {
                    char *out_file = "out_data.txt";
                    write_db(out_file);
                    break;
                } 
                case 7: {
                    printf("\nExiting...\n");
                    exit(1);
                }
                default:
                    printf("Invalid command!\n");
                    break;
            }
        } else {
            switch (choice) {
                case 1: {
                    getYearsPrompt();
                    break;
                }
                case 2: {
                    printf("show car by make to be implemented...\n");
                    break;
                }
                case 3: {
                    printf("show car by cost to be implemented...\n");
                    break;
                }
                case 4: {
                    printf("show car by category to be implemented...\n");
                    break;
                } 
                case 5: {
                    purchaseCarPrompt();
                    break;
                } 
                case 6: {
                    printf("\nExiting...\n");
                    exit(1);
                }
                default:
                    printf("Invalid command!\n");
                    break;
            }

        }

    } while (!(choice == 7 && user == 1) || !(choice == 6 && user == 2));

    return 0;
}


int main(int argc, char **argv) {


    char *filename = argv[1];
    initialize_db(filename);

    int user = validateUser();

    int returnVal = runProgram(user);
    
    return returnVal;
}

