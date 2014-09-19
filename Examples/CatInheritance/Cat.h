#ifndef __CAT_H__
#define __CAT_H__

typedef struct cat Cat;

// Constructors/Destructors
struct cat* newCat(char* name, int age, int weight, int fluffiness, int purrLevel);
void destroyCat(struct cat* cat);

// Getters
char* getCatName(struct cat* cat);
int getCatAge(struct cat* cat);
int getCatWeight(struct cat* cat);
int getCatFlusffiness(struct cat* cat);
int getCatPurrLevel(struct cat* cat);
int equalsCat(struct cat* c1, struct cat* c2);

void printCat(struct cat* cat);

#endif
