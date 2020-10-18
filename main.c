# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "car.h"

int input() {
    char inputt[25] = "";
    scanf("%s", inputt);
    int length = strlen(inputt);

    //this loop is responsible for verifying that each character of the input is a digit. 
    for (int i=0;i<length; i++) {
        if (!isdigit(inputt[i]))
        {
            //exit program if something non-int is entered. Prevents never-ending loop.
            printf ("Entered input is not a number\n");
            exit(1);
        }
    }
    //cast from string to int once verified using atoi()
    return atoi(inputt);
}

//called by another function to welcome users and prompt input
void printSignIn() {
    printf("\nWelcome to the CPSC 305 Project Cars DB- please sign in.\nEnter a user type: ");
}

//method used for gathering pertinent new-car data and passing it to the new_car method
void addCar() {

    //checks to make sure we aren't overwriting another car in the db
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);

    //only enters if the carnum is not already in use
    if (exists ==NULL) {
        printf("Enter a year: ");
        int year = input();
        printf("Enter a make: ");
        char maker[24];
        scanf("%s", maker);

        printf("Enter a category: ");
        category trim;
        char entry[24];
        scanf("%s", entry);
        if (strcmp(entry,"sedan") == 0) {
            trim = sedan;
        } else if (strcmp(entry,"suv") == 0) {
            trim = suv;
        } else if (strcmp(entry,"truck") == 0) {
            trim = truck;
        } else if (strcmp(entry,"hybrid") == 0) {
            trim = hybrid;
        }
        
        printf("Enter miles: ");
        int mileage = input();
        printf("Enter cost: ");
        int price = input();
        car *newCar = add_car(carnum, year, maker, trim, mileage, price);
        printf("Car added:\n");
        print_car(newCar);
    } else {
        printf("That carnum is already in use!\n");
    }
}

//validates the user, either owner or shopper
int validateUser() {
    printSignIn();

    char userIn[30];
    scanf("%s", userIn);

    //in this case, one is returned and the program will take the corresponding menu path for it
    if (strcmp(userIn, "owner") == 0) {
        return 1;
    //will return 2 to the menu method and display the corresponding shopper menu to end user
    } else if (strcmp(userIn, "shopper") == 0) {
        return 2;
    //something else was entered. Gives back to user to they can see typo and exits
    } else  {
        printf("\nInvalid user! You entered: %s\n", userIn);
        exit(1);
    }
}

//called repettively by another method whenever menu is needed
int printMenu(int user) {
    //owner menu
    if (user == 1) {
        printf("\nSelect one of the following:\n");
        printf("[1] Print Cars in DB           [2] Add a new Car\n");
        printf("[3] Delete via carnum          [4] Update cost via carnum\n");
        printf("[5] Update miles via carnum    [6] Save DB to file\n");
        printf("[7] Show cars by year          [8] Show cars by make\n");
        printf("[9] Show cars by cost          [10] Show cars by category\n");
        printf("[11] Quit program\nEnter your choice: "); 
    //shopper menu
    } else {
        printf("\nSelect one of the following:\n");
        printf("[1] Show cars by year          [2] Show cars by make\n");
        printf("[3] Show cars by cost          [4] Show cars by category\n");
        printf("[5] Purchase car by carnum\n");
        printf("Enter your choice: "); 
    }

    return input();
}

//gathers info and updates car cost by carnum
void updateCarCost() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    
    //only executes if the car actually exists in db
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

//gathers info and updates car miles by carnum
void updateCarMiles() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
    
    //only executes if the car actually exists in db
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

//gathers info and deletes car from db by carnum
void deleteCarPrompt() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);
   
    //only executes if the car actually exists in db
    if (exists != NULL) {
        deleteCar(exists->carnum);
    } else {
        printf("That carnum isn't in the database!\n");
    }
   
}

//gathers info and purchases (deletes) car from db by carnum
void purchaseCarPrompt() {
    printf("\nEnter a carnum: ");
    int carnum = input();
    car *exists = find_car(carnum);

    //only executes if the car actually exists in db
    if (exists != NULL) {
        purchase(exists->carnum);
        printf("\nCongratulations on the purhcase!\n");
        //we only need to write to the db if the shopper actually entered a valid carnum, so this is called here
        char *out_file = "out_data.txt";
        write_db(out_file);
    } else {
        printf("That carnum isn't in the database!\n");
    }
}

//can take two paths depending on what value is passed to it, it will either get an array of 
//cars that are equal to or newer than a specific year, or get cars equal to or lesser
//than a specific cost
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
   
    int numMatches; //holds the number of matches found for later 
    if (yearOrCost == 0) {
        //below function will insert matches into the matches array and return num matches
        numMatches = get_year(matches, yrOrCst);
    } else {
        //below function will insert matches into the matches array and return num matches 
        numMatches = get_cost(matches, yrOrCst);    
    }

    if (numMatches >= 1) {
        //prints the matches found by the previous functions
        for (int counter = 0; counter < numMatches; counter++) {
            car *c = matches[counter];
            print_car(c);
        }
    } else {
        //either path will handle the case that an empty array is returned (i.e. no matches found)
        if (yearOrCost == 0) {
            printf("No car that year or newer is in the Database!\n");
        } else {
            printf("No car that price or cheaper is in the Database!\n");
        }
    }
}

//like the function above, uses input passed from calling function to determine which 'path' it is going to take
void getPrompt(int makeOrCat) {
    car *matches[MAX_CARS];
    char makeSearchVal[25];
    category catSearchVal;
    char entry[24];

    //handles case that user is searching for cars of a specific make
    if (makeOrCat == 0) {
        printf("Enter a make: ");
        scanf("%s", makeSearchVal);

    //handles case that user is searching for cars of a specific type
    } else { 
        printf("Enter a category: ");
        scanf("%s", entry);
        if (strcmp(entry,"sedan") == 0) {
            catSearchVal = sedan;
        } else if (strcmp(entry,"suv") == 0) {
            catSearchVal = suv;
        } else if (strcmp(entry,"truck") == 0) {
            catSearchVal = truck;
        } else if (strcmp(entry,"hybrid") == 0) {
            catSearchVal = hybrid;
        }
    }
    printf("\n");
    
    //same as above function, calls corresponding matches functions and stores returned int for later use
    int numMatches;
    if (makeOrCat == 0) {
        numMatches = get_make(matches, makeSearchVal);
    } else {
        numMatches = get_category(matches, catSearchVal);
    }
        
    if (numMatches >= 1) {
        //prints all matches found as long as there was at least one
        for (int counter = 0; counter < numMatches; counter++) {
            car *c = matches[counter];
            print_car(c);
        }
    //handles event that no matches were found
    } else {
        if (makeOrCat) {
            printf("No car that of that make in the Database!\n");
        } else {
            printf("No car that of that category in the Database!\n");
        }
    }
}

//main driver, runs the entirety of the program from this method
void runProgram(int user) {
    int choice;

    do {
        //gets the user response to the menu and goes to corresponding switch statement         
        choice = printMenu(user);

        //if owner
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
                    getNumPrompt(0);
                    break;
                }
                case 8: {
                    getPrompt(0);
                    break;
                }
                case 9: {
                    getNumPrompt(1);
                    break;
                }
                case 10: {
                    getPrompt(1);
                    break;
                }  
                case 11: {
                    printf("\nExiting...\n");
                    exit(1);
                }
                default:
                    printf("Invalid command!\n");
                    break;
            }
        //if shopper
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
                   
                    exit(1);
                } 
                default:
                    printf("Invalid command!\n");
                    break;
            }

        }

    //determines when it is time to break the loop, never really reached because the program exits within the switch statement, 
    //but on the bright side it  never causes an early close either
    } while (!(choice == 11 && user == 1) || !(choice == 6 && user == 2));
}

//initiates program
int main(int argc, char **argv) {

    char *filename = argv[1];
    int foundFile = initialize_db(filename);
    int returnVal = 0;

    //only runs the program if the file is found and the DB is successfully loaded
    if (foundFile == 1) {
        int user = validateUser();
        runProgram(user);

    //returns the -1 FNF value from the initiate_db method
    } else {
        returnVal = foundFile;
    }

    return returnVal;
}