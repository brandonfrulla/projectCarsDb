# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "car.h"

static car db[MAX_CARS];
static int num_cars = 0;

int initialize_db(char *filename) {  

    FILE *fin  = fopen(filename,  "r"); 
    
    if (fin == NULL) {
       printf("===============\nFile​​ not found!\n===============\n");
       return -1;

    } else {
        int i = 0;
        while (fscanf(fin,"%d %d %s %s %d %d",
                        &db[i].carnum,
                        &db[i].year, 
                        db[i].make, 
                        db[i].category, 
                        &db[i].miles, 
                        &db[i].cost
                        ) 
                != EOF) {
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
                out->category, 
                out->miles, 
                out->cost
                );    
            
        }
        
        printf("=================================================================\n\n"); 

        fclose(fout);
        return 1;
    }
}

void showMatches(car **cars, int num_matches) {
    
    printf("\n=================================================================\n"); 
    for (int counter = 0; counter < num_matches; counter++) {

        car *c = cars[counter];
        print_car(c);

    } 
    printf("=================================================================\n\n"); 

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

        printf("CarNum: %d Year: %d Make: %s Category: %s Miles: %d Cost: $%.2d\n", 
        c->carnum, c->year, c->make, c->category, c->miles, c->cost);

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