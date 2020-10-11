#define MAX_CARS 100
#define MAX_MAKE_CHARS 32

typedef enum { sedan, suv, truck, hybrid } category;

typedef struct {
   int   carnum;
   int   year;
   char  make[MAX_MAKE_CHARS];
   char  category[25];
   int   miles;
   int   cost;
} car;  

int initialize_db(char *filename); //done
int write_db(char *filename);    //done
void show_cars();                  //done
void print_car(car *c);          //done
car *find_car(int carnum);        // done
car *add_car(int carnum, int year, char *make, char *category, int miles, int cost); //done
car *update_cost(int carnum, int cost); //done
car *update_miles(int carnum, int miles); //done
int get_year(car **cars, int year); //done
int get_cost(car **cars, int cost); //done
int get_category(car **cars, char *category); //done
car *purchase(int carnum); //done

//methods added by me
void deleteCar(int carnum); //done
int get_make(car **cars, char *make); //done
