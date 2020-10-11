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
        printf("\nInvalid user! You entered: %s\n", userIn);
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

void getNumPrompt(int yearOrCost) {
    car *matches[MAX_CARS];
    int yrOrCst;

    if (yearOrCost == 0) { 
        printf("Enter a year: ");
        yrOrCst = input();
    } else {
        printf("Enter a cost: ");
        yrOrCst = input();
    }
    printf("\n");
   
    int numMatches;
    if (yearOrCost == 0) {
        numMatches = get_year(matches, yrOrCst);
    } else {
        numMatches = get_cost(matches, yrOrCst);    
    }

    if (numMatches >= 1) {
        for (int counter = 0; counter < numMatches; counter++) {
            car *c = matches[counter];
            print_car(c);
        }
    } else {
        if (yearOrCost == 0) {
            printf("No car that year or newer is in the Database!\n");
        } else {
            printf("No car that price or cheaper is in the Database!\n");
        }
    }
}

void getPrompt(int makeOrCat) {
    car *matches[MAX_CARS];
    char searchVal[25];
    
    if (makeOrCat == 0) {
        printf("Enter a make: ");
    } else { 
        printf("Enter a category: ");
    }
    scanf("%s", searchVal);
    printf("\n");
    
    int numMatches;
    if (makeOrCat == 0) {
        numMatches = get_make(matches, searchVal);
    } else {
        numMatches = get_category(matches, searchVal);
    }
        
    if (numMatches >= 1) {
        for (int counter = 0; counter < numMatches; counter++) {
            car *c = matches[counter];
            print_car(c);
        }
    } else {
        if (makeOrCat) {
            printf("No car that of that make in the Database!\n");
        } else {
            printf("No car that of that category in the Database!\n");
        }
    }
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
                    getNumPrompt(0);
                    break;
                }
                case 2: {
                    getPrompt(0);
                    break;
                }
                case 3: {
                    getNumPrompt(1);
                    break;
                }
                case 4: {
                    getPrompt(1);
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

