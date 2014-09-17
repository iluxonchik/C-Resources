/*
Modele e implemente em C (ficheiros .h e .c) uma estrutura de dados que represente uma versão simples do conceito 
"gato". Um gato tem como características o nome ( _name), a idade ( _age), o peso ( _weight), o volume do 
ronronar ( _purrLevel) e o grau de suavidade do pêlo ( _fluffiness). Implemente a função newCat que reserva 
memória suficiente para representar um gato e permite inicializar os seus campos (através dos argumentos da 
função). Por simplicidade, assuma que o campo _name tem comprimento fixo máximo de 16 caracteres (incluindo o 
terminador). Implemente também a função destroyCat, que liberta os recursos associados ao gato.

a. Implemente a função de comparação - equalsCat -, por forma a considerar que dois gatos são iguais se as suas 
características forem iguais.
b. Implemente funções de acesso às variáveis de um gato: getCatName, getCatAge, getCatWeight, getCatPurrLevel,
getCatFluffiness (dado um gato, retornam um dos seus campos).
c. Implemente a função printCat que, quando aplicada a um gato, apresenta os seus dados (use printf para apresentar 
cada campo do gato).
d. Implemente um programa - main - que ilustre a utilização das funções anteriores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cat.h"

struct cat{
	char _name[16];
	int _age;
	int _weight;
	int _purrLevel;
	int _fluffiness;
};

Cat* newCat(char* name, int age, int weight, int purrLevel, int fluffiness){
	Cat* cat;

	// Allocate memory for the "Cat" structure
	cat = (Cat*)malloc(sizeof(Cat));


	if (cat != NULL){
		strcpy(cat->_name, name);
		cat->_age = age;
		cat->_weight = weight;
		cat->_purrLevel = purrLevel;
		cat->_fluffiness = fluffiness;
	}

	return cat;
}

void destroyCat(Cat* cat){
	if (cat != NULL){
		free(cat);
	}
}

int equalsCat(Cat* c1, Cat* c2){
	if (c1 != NULL && c2 != NULL)
	{
		return (
			getFluffiness(c1) == getFluffiness(c2) && 
			getAge(c1) == getAge(c2) && 
			getPurrLevel(c1) == getPurrLevel(c2)
			&& getWeight(c1) == getWeight(c2) 
			&& !strcmp(c1->_name, c2->_name)
			);
	}
	return -1; // One of the addresses is NULL (Error)
}

char* getName(Cat* cat){
	return cat->_name;
}

int getAge(Cat* cat){
	return cat->_age;
}

int getWeight(Cat* cat){
	return cat->_weight;
}

int getPurrLevel(Cat* cat){
	return cat->_purrLevel;
}

int getFluffiness(Cat* cat){
	return cat->_fluffiness;
}

void printCat(Cat* cat){
	printf("N: %s \nA: %d \nW: %d \nPL: %d \nF: %d \n", getName(cat), getAge(cat), getWeight(cat), getPurrLevel(cat), getFluffiness(cat));
}
