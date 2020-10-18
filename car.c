# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "car.h"

static car db[MAX_CARS];
static int num_cars = 0;
const char *strings[] = { "sedan", "suv", "truck", "hybrid"};

int initialize_db(char *filename) {  

    FILE *fin  = fopen(filename,  "r");
    char str[60]; 
    
    if (fin == NULL) {
       printf("===============\nFile​​ not found!\n===============\n");
       return -1;

    } else {
        int i = 0;
        while (fgets(str, 60, fin) != NULL) {
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

void show_cars() {
    
    printf("\n=================================================================\n"); 
    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        print_car(c);

    } 
    printf("=================================================================\n\n"); 

}

void print_car(car *c) {

        printf("CarNum: %d Year: %d Make: %s ", c->carnum, c->year, c->make);
        printf("Category: %s ", enumToString(c->category)); 
        printf("Miles: %d Cost: $%.2d\n", c->miles, c->cost);

}

char* enumToString(category cat) {
    return (char*) strings[cat];
}

car *find_car(int carnum) {
    
    for (int counter = 0; counter < num_cars; counter++) {
        
        car *c = &db[counter];
        if (c->carnum == carnum) {
            return c;
        }
    }
    return NULL; 

}

car *add_car(int carnum, int year, char *make, char *category, int miles, int cost) {
    
    car carro;
    
    carro.carnum = carnum;
    carro.year = year;
    strcpy(carro.make, make);
    strcpy(carro.category, category);
    carro.miles = miles;
    carro.cost = cost;
    
    db[num_cars] = carro;
    car * point  = &db[num_cars];
    num_cars++;

    return point;
}


car *update_cost(int carnum, int cost) {
    car *exists = find_car(carnum);
    exists->cost = cost;
    return exists;
}

car *update_miles(int carnum, int miles) {
    car *exists = find_car(carnum);
    exists->miles = miles;
    return exists;
} 

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

int get_category(car **cars, char *category) {    
    int found = 0;

    for (int counter = 0; counter < num_cars; counter++) {

        car *c = &db[counter];
        if (strcmp(c->category, category) == 0) {
            cars[found] = c;
            found++;
        }
    }
    return found;
}

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

car *purchase(int carnum) {
    car *toBuy = find_car(carnum);
    if (toBuy != NULL) {
        deleteCar(toBuy->carnum);
    }
    return toBuy;
}