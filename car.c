# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "car.h"

static car *db[MAX_CARS];
static int num_cars = 0;
//int input();

int initialize_db(char *filename) {  

    //printf("%s", filename);

    FILE *fin  = fopen(filename,  "r"); 

    int num_cars;
    
    if (fin == NULL) {
       printf("===============\nFile​​ not found!\n===============\n");
       return -1;

    } else {
        int i = 0;

        while (fscanf(fin,"%d %d %s %s %d %d", 
                        db[i]->carnum,
                        db[i]->year, 
                        db[i]->make, 
                        db[i]->category, 
                        db[i]->miles, 
                        db[i]->cost
                        ) 
                != EOF) {
                i++;
        }
        num_cars = i;
    }

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

            car *out = db[c];

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



void show_cars() {
    
    printf("\n=================================================================\n"); 
    for (int counter = 0; counter < num_cars; counter++) {

        car *c = db[counter];
        print_car(c);

    } 
    printf("=================================================================\n\n"); 

}


void print_car(car *c) {

        printf("CarNum: %d Year: %d Make: %s Category: %s Miles: %d Cost: $%.2d\n", 
        c->carnum, c->year, c->make, c->category, c->miles, c->cost);

}

car *find_car(int carnum) {
    
    printf("\n=================================================================\n"); 
    for (int counter = 0; counter < num_cars; counter++) {
        
        car *c = db[counter];
        if (c->carnum == carnum) {
            return c;
        }
    } 
    printf("=================================================================\n\n"); 

}

car *add_car(int carnum, int year, category category, int miles, int cost) {
    db[num_cars]->carnum;
    db[num_cars]->year;
    db[num_cars]->category;
    db[num_cars]->miles;
    db[num_cars]->cost;
    num_cars++;
}


//revise, don't know when to return the car really, or what to do if it doesn't fins anything 
car *update_cost(int carnum, int cost) {
    for (int counter = 0; counter < num_cars; counter++) {
        
        car *c = db[counter];
        if (c->carnum == carnum) {
            db[counter]->cost = cost;
            return c;
        }
    } 
}

//revise, don't know when to return the car really, or what to do if it doesn't fins anything 
car *update_miles(int carnum, int miles) {

    for (int counter = 0; counter < num_cars; counter++) {
        
        car *c = db[counter];
        if (c->carnum == carnum) {
            db[counter]->miles = miles;
            return c;
        }
    } 

}

// int get_year(car **cars, int year) { 



// }