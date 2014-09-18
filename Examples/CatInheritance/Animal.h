
typedef struct animal Animal;

// Constructors & destructors
Animal* newAnimal(char* name, int age, int weight);
void destroyAnimal(Animal* animal);

int equalsAnimal(Animal* animal1, Animal* animal2);

// "Getters"
char* getAnimalName(Animal* animal);
int getAnimalAge(Animal* animal);
int getAnimalWeight(Animal* animal);

void printAnimal(Animal* animal);
