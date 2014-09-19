#include <stdio.h>
#include "Cat.h"

int main(void){

	Cat* c1 = newCat("Meowings", 1, 1, 1, 1);
	Cat* c2 = newCat("Meowington", 1, 1, 1, 1);

	printCat(c1);
	printCat(c2);

	equalsCat(c1, c2);
	
	destroyCat(c1);
	destroyCat(c2);

	scanf("%d"); // keep the console window open
}
