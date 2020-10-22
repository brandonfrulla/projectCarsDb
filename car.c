# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "car.h"

static car db[MAX_CARS];
static int num_cars = 0;
const char *strings[] = { "sedan", "suv", "truck", "hybrid"};

//reads in data file and handles not found errors as well as formatting the new cars as needed per line
int initialize_db(char *filename) {  

    FILE *fin  = fopen(filename,  "r");
    char str[60]; 
    
    if (fin == NULL) {
       printf("===============\nFile​​ not found!\n===============\n");
       return -1;

    } else {
        int i = 0;
        while (fgets(str, 60, fin) != NULL) {
                //printf("%s, %d\n", str, i); //commented out, for gusty debugging 
                char * split = strtok(str, " ");
                int innerIndex = 0;
                while (split != NULL) {
                    if (innerIndex == 0) {
                        db[i].carnum = atoi(split);
                    } else if (innerIndex == 1) {
                        db[i].year = atoi(split);
                    } else if (innerIndex == 2) {
                        strcpy(db[i].make,split);
                    } else if (innerIndex == 3) {
                        if (strcmp(split,"sedan") == 0) {
                            db[i].category = sedan;
                        } else if (strcmp(split,"suv") == 0) {
                            db[i].category = suv;
                        } else if (strcmp(split,"truck")== 0) {
                            db[i].category = truck;
                        } else if (strcmp(split,"hybrid") == 0) {
                            db[i].category = hybrid;
                        }
                    } else if (innerIndex == 4) {
                        db[i].miles = atoi(split);
                    } else {
                        db[i].cost = atoi(split);
                    }


                    split = strtok(NULL, " ");
                    innerIndex++;
                }
                i++;
        }
        num_cars = i;
    }

    printf("\n=================================================================\n"); 
    printf("DB loaded successfully!");
    printf("\n=================================================================\n"); 

    fclose(fin); 
    return 1;
}

//responsible for writing entirety of DB to an out file
int write_db(char *filemame) {

    FILE *fout = fopen(filemame, "w+");  

    if (fout == NULL) {
        return -1;
    } else {

        printf("\n=================================================================\n"); 
        printf("Writing DB to file...\n");

        for (int c = 0; c < num_cars; c++) {

            car *out = &db[c];

            fprintf(fout,  "CarNum: %d Year: %d Make: %s Category: %s Miles: %d Cost: $%.2d\n",
                out->carnum, 
                out->year, 
                out->make, 
                enumToString(out->category), 
                out->miles, 
                out->cost
                );    
            
        }
        
        printf("=================================================================\n\n"); 

        fclose(fout);
        return 1;
    }
}

//primary function used to print each car held in db when called
void show_cars() {
    
    printf("\n=================================================================\n"); 
    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        print_car(c);

    } 
    printf("=================================================================\n\n"); 

}

//helper fucntion for show_cars, prints the formatted lines for each car 
void print_car(car *c) {

        printf("CarNum: %d Year: %d Make: %s ", c->carnum, c->year, c->make);
        printf("Category: %s ", enumToString(c->category)); 
        printf("Miles: %d Cost: $%.2d\n", c->miles, c->cost);

}

//uses the static var aboce to convert the enum 'indeces' held by the car struct types into actual string values for human consumption
char* enumToString(category cat) {
    return (char*) strings[cat];
}

//finds cars in db by carnum, or returns null when car cannot be located
car *find_car(int carnum) {
    
    for (int counter = 0; counter < num_cars; counter++) {
        
        car *c = &db[counter];
        if (c->carnum == carnum) {
            return c;
        }
    }
    return NULL; 

}

//adds cars to db 
car *add_car(int carnum, int year, char *make, category category, int miles, int cost) {
    
    car carro;
    
    carro.carnum = carnum;
    carro.year = year;
    strcpy(carro.make, make);
    carro.category = category;
    carro.miles = miles;
    carro.cost = cost;
    
    db[num_cars] = carro;
    car * point  = &db[num_cars];
    num_cars++;

    return point;
}

//updates cars' respective costs in db if they are found
car *update_cost(int carnum, int cost) {
    car *exists = find_car(carnum);
    exists->cost = cost;
    return exists;
}

//updates cars' respecive mileages in db if they are found
car *update_miles(int carnum, int miles) {
    car *exists = find_car(carnum);
    exists->miles = miles;
    return exists;
} 

//returns an int of matches to calling function and assigns copies of any matches found to the array passed to it calling function 
int get_year(car **cars, int year) {    
    int found = 0;

    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        if (c->year >= year) {
            cars[found] = c;
            found++;
        }
    }
    return found;
}

//returns an int of matches to calling function and assigns copies of any matches found to the array passed to it calling function 
int get_cost(car **cars, int cost) {    
    int found = 0;

    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        if (c->cost <= cost) {
            cars[found] = c;
            found++;
        }
    }
    return found;
}

//returns an int of matches to calling function and assigns copies of any matches found to the array passed to it calling function 
int get_make(car **cars, char *make) {    
    int found = 0;

    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        if (strcmp(c->make, make) == 0) {
            cars[found] = c;
            found++;
        }
    }
    return found;
}

//returns an int of matches to calling function and assigns copies of any matches found to the array passed to it calling function 
int get_category(car **cars, category category) {    
    int found = 0;

    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        if (c->category == category) {
            cars[found] = c;
            found++;
        }
    }
    return found;
}

//used by both owner and shopper, this is responsible for deleting a car from the db. Owner can delete any car they want, 
//shopper will 'purchase' a car, which essentially just calls this function again but prints a bit of extra congratulatory jargon to the new happy car owner
void deleteCar(int carnum) {
    for (int counter = 0; counter < num_cars; counter++) {
        int bigbreak = 0;
        car *c = &db[counter];
        if (c->carnum == carnum) {
            printf("Deleting: ");
            print_car(c);
            num_cars--;
            for (int d = counter; d < num_cars; d++) {
                 db[d] = db[d+1];
                 if (d == num_cars) {
                    bigbreak = 1;
                    break;
                 }
            }
        }
        if (bigbreak) {
            break;
        }
    }
}

//like outlined in above comment, simply the delete function for the shopper 
car *purchase(int carnum) {
    car *toBuy = find_car(carnum);
    if (toBuy != NULL) {
        deleteCar(toBuy->carnum);
    }
    return toBuy;
}