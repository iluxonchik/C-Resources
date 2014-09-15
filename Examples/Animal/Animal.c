#include "Animal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Modele e implemente em C (ficheiros .h e .c) uma estrutura de dados que represente uma vers�o simples do
conceito "animal". Um animal tem como caracter�sticas o nome ( _name), a idade ( _age) e o peso ( _weight).
Implemente a fun��o newAnimal que reserva mem�ria suficiente para representar um animal e permite inicializar
os seus campos (atrav�s dos argumentos da fun��o). Por simplicidade, assuma que o campo _name tem comprimento
fixo m�ximo de 16 caracteres (incluindo o terminador). Implemente tamb�m a fun��o destroyAnimal, que liberta
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
