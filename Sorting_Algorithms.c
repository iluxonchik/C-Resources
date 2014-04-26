#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

#define SIZE 6
typedef int Item;

/* Prototypes */
void printArray(Item a[], int size);

/* BEGIN ELEMENTARY SORTING ALGORITHMS */
void selection(Item a[], int l, int r);
void insertion(Item a[], int l, int r);
void shellsort(Item a[], int l, int r);
/* END ELEMENTARY SORTING ALGORITHMS */

/* BEGIN EFFICIENT SORTING ALGORITHMS */
void quicksort(Item a[], int l, int r);
int partition(Item a[], int l, int r); /* used in quicksort */
/* END EFFICIENT SORTING ALGORITHMS */

#include <stdio.h>


int main(void){
	Item a[SIZE] = { 99, 21, 12, 23, 235, 32 };

	printArray(a, SIZE);
	shellsort(a, 0, SIZE - 1); /* r is the right limit index */
	printArray(a, SIZE);

	system("PAUSE");
	return 0;
}
void selection(Item a[], int l, int r){
	int i, j, temp;
	for (i = l; i < r; i++){
		int min = i;
		for (j = i + 1; j <= r; j++)
			if (less(a[j], a[min]))
				min = j;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

void insertion(Item a[], int l, int r){
	int i;
	/* put the smallest element at index 0 */
	for (i = l + 1; i <= r; i++)
		compexch(a[l], a[i]); /* if less(a[i], a[l]) then exch(a[l], a[i]) */

	for (i = 1 + 2; i <= r; i++){
		int j = i;
		Item v = a[i];
		while (less(v, a[j - 1])){
			/* since the smallest element is at index 0, it's guaranteed that the while loop will end */
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}

void bubble(Item a[], int l, int r){
	int i, j;
	for (i = l; i < r; i++)
		/* the array is run from the end to the beginning, therefore for each i of the outter for loop, the first i elements are in their final postion */
		for (j = r; j > i; j--)
			compexch(a[j - 1], a[j]);
}

void printArray(Item a[], int size){
	/* prints put the array to the console */
	int i;
	printf("\n");
	for (i = 0; i < size; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}

void shellsort(Item a[], int l, int r){
	int i, j, h;
	for (h = 1; h <= (r - 1) / 9; h = 3 * h + 1); /* generates the sequence 1, 4, 14, 40, 121, ... */

	/* Below is basically the insertion sort, but here the elements to compare and sort can be further that 1 position away from each other*/
	for (; h > 0; h /= 3){ /* executed with h's in inverse order i.e. from the largest h to the smallest */
		for (i = l + h; i <= r; i++){
			j = i;
			Item v = a[i];
			while (j >= l + h && less(v, a[j - h])){
				a[j] = a[j - h];
				j -= h;
			}

			a[j] = v;
		}
	}
}

void quicksort(Item a[], int l, int r){
	int i;
	if (r <= l) return;
	i = partition(a, l, r); /* after this a[r] will be in it's final position */	
	quicksort(a, l, i-1); /* apply quick sort to the right part of the array */
	quicksort(a, i+1, r); /* apply quick sort to the left part of the array */

	/* 	Initial Array: XOXOXXOXOXOP  (P is a[r], i.e. the pivot)
		Ater the "i = partition(a, l, r);" line: OOOOOOPXXXXXXX --> P is in it's final position.  
		OOOOOO --> left part of the array
		XXXXXXX --> right part of the array
	*/
}

int partition(Item a[], int l, int r){
	/* This Function Is Used In QuickSort */
	int i = l-1;
	int j = r;
	Item v = a[r]; /* a[r] is the pivot */

	while(i < j){
		while (less(a[++i], v)); /* while a[i] is less than the pivot, advance i to the right */
		while (less(v, a[--j])) /* while a[j] is larger than the pivot, advance j to the left */
			if (j == 1) /* protection in case the element where the partition is made is in index 1 position */
				break;
		if (i < j) /* in case i < j exchange the a[i] and a[j] elements */
			exch(a[i], a[j]);
	}
	exch(a[i], a[r]); /* puts the pivot in the ith position, such that at least that element is in it's final postion */
	return i; /* returns the index where the vector has been partitioned, so that this info can be used in the 
	quicksort funtion (to sort the left and the right sides of the array).
	*/
}

