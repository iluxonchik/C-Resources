#include <stdio.h>
#include "Cat.h"

int main(void){
	Cat* c1 = newCat("Meowington", 1, 1, 1, 1);
	Cat* c2 = newCat("Meowings", 1, 1, 1, 1);

	printCat(c1);
	printCat(c2);

	(equalsCat(c1, c2)) ? printf("Identical Cats!\n") : printf("Those cats ain't the same...\n");

	destroyCat(c1);
	destroyCat(c2);

	scanf("%d"); // keep the console open

	return 0;
}