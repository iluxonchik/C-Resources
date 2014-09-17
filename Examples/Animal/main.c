#include <stdio.h>
#include "Animal.h"

int main(void){
	Animal* a1;
	Animal* a2;

	a1 = newAnimal("Cat", 1, 1);
	a2 = newAnimal("Dog", 1, 1);

	printAnimal(a1);
	printAnimal(a2);

	if (equalsAnimal(a1, a2))
		printf("Both animals are identical!\n");
	else
		printf("They ain't the same!\n");

	destroyAnimal(a1);
	destroyAnimal(a2);

	scanf("%d"); // keep the console open

}