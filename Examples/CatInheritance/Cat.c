/*
Modele e implemente em C (ficheiros .h e .c) uma estrutura de dados que represente uma nova versão do conceito 
"gato". Um gato é um animal caracterizado pelo volume do ronronar ( _purrLevel) e pelo grau de suavidade do pêlo
( _fluffiness). Implemente a função newCat que reserva memória suficiente para representar um gato e permite 
inicializar os seus campos (através dos argumentos da função). Implemente também a função destroyCat, que liberta
os recursos associados ao gato.

a) Implemente a função de comparação - equalsCat -, por forma a considerar que dois gatos são iguais se as suas características forem iguais.
b) Implemente funções de acesso às variáveis internas de um gato: getCatName, getCatAge, getCatWeight, 
getCatPurrLevel, getCatFluffiness (dado um gato, retornam um dos seus campos). 
Note que algumas destas características são fornecidas pelo conceito "animal".
c) Implemente a função printCat que, quando aplicada a um gato, apresenta os seus dados (use printf para apresentar cada campo do gato).
d) Implemente um programa - main - que ilustre a utilização das funções anteriores.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Cat.h"
#include "Animal.h"

struct cat{
	Animal* _animal; // forward-declaring a struct
	int _purrLevel;
	int _fluffiness;
};

struct cat* newCat(char* name, int age, int weight, int fluffiness, int purrLevel){
	struct cat* cat = (struct cat*)malloc(sizeof(struct cat));
	
	if (cat != NULL){
		cat->_animal = newAnimal(name, age, weight);

		cat->_fluffiness = fluffiness;
		cat->_purrLevel = purrLevel;

		return cat;
	}
	else
		return NULL;
}

void destroyCat(struct cat* cat){
	if (cat != NULL){
		destroyAnimal(cat->_animal);

		free(cat);
	}
}

char* getCatName(struct cat* cat){
	return getAnimalName(cat->_animal);
}

int getCatAge(struct cat* cat){
	return getAnimalAge(cat->_animal);
}

int getCatWeight(struct cat* cat){
	return getAnimalWeight(cat->_animal);
}

int getCatFlusffiness(struct cat* cat){
	return cat->_fluffiness;
}

int getCatPurrLevel(struct cat* cat){
	return cat->_purrLevel;
}

int equalsCat(struct cat* c1, struct cat* c2){
	if (c1 != NULL && c2 != NULL){
		return (equalsAnimal(c1->_animal, c2->_animal) && c1->_fluffiness == c2->_fluffiness
			&& c1->_purrLevel == c2->_purrLevel);
	}
	return -1; // something went wrong
}

void printCat(struct cat* cat){
	printAnimal(cat->_animal);
	printf("Purr Level: %d \nFlufiness Level: %d\n", cat->_fluffiness, cat->_purrLevel);
}
