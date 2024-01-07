// Using structures example

struct car
{
    int year;
    char model[10];
    char plate[7];
    int odometer;
    double engine_size;
};

int main(void)
{
    // variable declaration
    struct car mycar;

    // field accessing
    mycar.year = 2011;
    strcpy(mycar.plate, "CS50");
    mycar.odometer = 50505;


    // Dynamically allocate structures
    // variable delcaration
    struct car *yourcar = malloc(sizeof(struct car));

    // field accessing
    (*yourcar).year = 2011;
    strcpy((*yourcar).plate, "CS50");
    (*yourcar).odometer = 50505;

    // or
    yourcar->year = 2011;
    strcpy(yourcar->plate, "CS50");
    yourcar->odometer = 50505;
}