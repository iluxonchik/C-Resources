/*
Modele e implemente em C (ficheiros .h e .c) uma estrutura de dados que represente uma nova vers�o do conceito 
"gato". Um gato � um animal caracterizado pelo volume do ronronar ( _purrLevel) e pelo grau de suavidade do p�lo
( _fluffiness). Implemente a fun��o newCat que reserva mem�ria suficiente para representar um gato e permite 
inicializar os seus campos (atrav�s dos argumentos da fun��o). Implemente tamb�m a fun��o destroyCat, que liberta
os recursos associados ao gato.

a) Implemente a fun��o de compara��o - equalsCat -, por forma a considerar que dois gatos s�o iguais se as suas caracter�sticas forem iguais.
b) Implemente fun��es de acesso �s vari�veis internas de um gato: getCatName, getCatAge, getCatWeight, 
getCatPurrLevel, getCatFluffiness (dado um gato, retornam um dos seus campos). 
Note que algumas destas caracter�sticas s�o fornecidas pelo conceito "animal".
c) Implemente a fun��o printCat que, quando aplicada a um gato, apresenta os seus dados (use printf para apresentar cada campo do gato).
d) Implemente um programa - main - que ilustre a utiliza��o das fun��es anteriores.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"

struct cat{
	Animal* _animal;
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

