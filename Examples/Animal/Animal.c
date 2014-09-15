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
