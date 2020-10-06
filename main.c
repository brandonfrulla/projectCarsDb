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

int runProgram(int user, int choice) {
    if (user == 1) {
        switch (choice) {
        	case 1: {
        		printf("\nCars currently held in DB:");
                show_cars();
        		break;
         	}
    	    case 2: {
    	    	printf("add car to be implemented...\n");
    	    	break;
    	    }
    	    case 3: {
    	        printf("delete car to be implemented...\n");
                break;
    	    }
            case 4: {
                printf("update cost to be implemented...\n");
                break;
            } 
            case 5: {
                printf("update miles to be implemented...\n");
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
	    }
    } else {
        switch (choice) {
        	case 1: {
        		printf("show car by year to be implemented");
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
                printf("purchase car by carnum to be implemented...\n");
                break;
            } 
            case 6: {
                printf("\nExiting...\n");
                exit(1);
            }
	        default:
		        printf("Invalid command!\n");
	    }

    }
    return 1;
}


int main(int argc, char **argv) {


    char *filename = argv[1];
    initialize_db(filename);

    /*int user = validateUser();

    int choice = printMenu(user);
	
    int outNum = runProgram(user, choice);

    return outNum;*/
}

