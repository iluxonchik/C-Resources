
typedef struct cat Cat;

// Constructors / Destructors
Cat* newCat(char* name, int age, int weight, int purrLevel, int fluffiness);
void destroyCat(Cat* cat);

int equalsCat(Cat* c1, Cat* c2);

// Getters
char* getName(Cat* cat);
int getAge(Cat* cat);
int getWeight(Cat* cat);
int getPurrLevel(Cat* cat);
int getFluffiness(Cat* cat);

void printCat(Cat* cat);
