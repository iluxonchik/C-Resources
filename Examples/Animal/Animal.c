#include "Animal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Modele e implemente em C (ficheiros .h e .c) uma estrutura de dados que represente uma versão simples do
conceito "animal". Um animal tem como características o nome ( _name), a idade ( _age) e o peso ( _weight).
Implemente a função newAnimal que reserva memória suficiente para representar um animal e permite inicializar
os seus campos (através dos argumentos da função). Por simplicidade, assuma que o campo _name tem comprimento
fixo máximo de 16 caracteres (incluindo o terminador). Implemente também a função destroyAnimal, que liberta
os recursos associados ao animal.

a. Implemente a função de comparação - equalsAnimal -, por forma a considerar que dois animais são iguais se as suas características forem iguais.
a. Implemente funções de acesso às variáveis de um animal: getAnimalName, getAnimalAge, getAnimalWeight (dado um animal, retornam um dos seus campos).
a. Implemente a função printAnimal que, quando aplicada a um animal, apresenta os seus dados (use printf para apresentar cada campo do animal).
a. Implemente um programa - main - que ilustre a utilização das funções anteriores.
*/

typedef struct animal{
	char* _name;
	int _age;
	int _weight;
}Animal;


Animal* newAnimal(char* name, int age, int weight){
	Animal* animal;
	int nameLen;

	animal = (Animal*)malloc(sizeof(Animal));
	if (animal != NULL) {
		animal->_age = age;
		animal->_weight = weight;

		// Deal with the name
		nameLen = strlen(name); // get the length of the animal's name
		animal->_name = (char*)malloc(sizeof(char*) * (nameLen + 1));
		strcpy(animal->_name, name);
		animal->_name[nameLen] = '\0';
	}
	return animal;
}

void destroyAnimal(Animal* animal){
	if (animal != NULL){
		// First, free the string (name)
		if (animal->_name != NULL){
			free(animal->_name);
		}
		free(animal);
	}
}

int equalsAnimal(Animal* animal1, Animal* animal2){
	if (animal1 != NULL && animal2 != NULL){
		if (animal1->_age == animal2->_age && animal1->_weight == animal2->_weight && !(strcmp(animal1->_name, animal2->_name)))
			return 1;
		else
			return 0;
	}
	return -1; // something went wrong
}