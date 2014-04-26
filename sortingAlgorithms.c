/* some macros below to make the algorithms more abstract */
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

#define SIZE 6
#define maxN 20 /* maximum number os elements in the array to sort */
#define M 235  /* largest element in the array (for counting sort) */

typedef int Item; /* this can be changed to smth else, for example float or double */
Item aux[maxN]; /* used in MergeSort */

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
void mergesort(Item a[], int l, int r);
void merge(Item a[], int l, int m, int r); /* used in mergesort */
void heapsort(Item a[], int l, int r);
int parent(int k); /* used in heapsort */
int right(int k); /* used in heapsort */
int left(int k); /* used in heapsort */
void fixDown(Item a[], int l, int r, int k); /* used in heapsort */
void buildHeap(Item a[], int l, int r); /* used in heapsort */

/* ALGORTITHMS NOT BASED SOLEY ON COMPARATIONS */
void distcount(int a[], int l, int r);
/* END EFFICIENT SORTING ALGORITHMS */

#include <stdio.h>


int main(void){
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
	quicksort(a, l, i - 1); /* apply quick sort to the right part of the array */
	quicksort(a, i + 1, r); /* apply quick sort to the left part of the array */

	/* 	Initial Array: XOXOXXOXOXOP  (P is a[r], i.e. the pivot)
	Ater the "i = partition(a, l, r);" line: OOOOOOPXXXXXXX --> P is in it's final position.
	OOOOOO --> left part of the array
	XXXXXXX --> right part of the array
	*/
}

int partition(Item a[], int l, int r){
	/* This Function Is Used In QuickSort */
	int i = l - 1;
	int j = r;
	Item v = a[r]; /* a[r] is the pivot */

	while (i < j){
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

void merge(Item a[], int l, int m, int r){
	/* recieves two sorted vectors: a[l,...,m] and a[m+1,...,r] "returns" a sorted vector a[l,...,r]*/
	int i, j, k;

	/* the two for loops below build the aux array */
	for (i = m + 1; i > l; i--)
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++)
		aux[r + m - j] = a[j + 1];

	/* at the beginning i = l ; j = r | the array will be sorted here */
	for (k = l; k <= r; k++)
		if (less(aux[j], aux[i]))
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

void mergesort(Item a[], int l, int r){
	/* top-down version of mergesort */
	int m = (r + l) / 2;

	if (r <= l) return;

	mergesort(a, l, m); /* sort the left part of the array */
	mergesort(a, m + 1, r); /* sort the right part of the array */
	merge(a, l, m, r); /* merge both sorted arrays into one sorted array */
}

/* used heapsort */
int parent(int k){
	/* return the position parent of node k */
	return ((k + 1) / 2) - 1;
}

int left(int k){
	/* return the postion of left child of parent k */
	return 2 * k + 1;
}

int right(int k){
	/* return the position of right child of parent k */
	return 2 * (k + 1);
}

void fixDown(Item a[], int l, int r, int k){
	/* checks if node k has a larger child that him, in case he does,
	exchange the element on postion k(the parent) with it's largest child,
	then apply fixDown on the position of the largest child
	(the one that the parent was exchanged with) */

	int ileft, iright, largest = k; /* it's assumed that the parent is larger that its children */
	ileft = l + left(k - l); /* ileft is the left child of k */
	iright = l + right(k - l); /* iright is the right child of k */

	/* NOTE: k-l is used since k is the absolute position in the array
	(or part of the array) to sort. If the goal is to sort just some part of the
	array(from l to r), then the childs relative position is different
	from its absolute position in the array. */

	if (ileft <= r && less(a[largest], a[ileft]))
		/* if the right child is larger that the parent */
		largest = ileft; /* the largest element is now the left chil */
	if (iright <= r && less(a[largest], a[iright]))
		/* if the right child is larger that the parent */
		largest = iright; /* the largest element is now the left chil */

	if (largest != k){
		/* if the parent has children bigger than him */
		exch(a[k], a[largest]); /* exhcange parent with the largest child */
		fixDown(a, l, r, largest); /* apply fixDown to the largest child's position */
	}
}

void buildHeap(Item a[], int l, int r){
	/* transforms an ordinary array into a heap */
	int k, heapsize = r - l + 1;
	for (k = heapsize / 2 - 1; k >= 1; k--)
		/* call fixdown from the largest parent index with non-empty children down to the index 0
		this will transform an ordinary array into a heap*/
		fixDown(a, l, r, l + k);
}

void heapsort(Item a[], int l, int r){
	/* an implementation of heapsort */
	buildHeap(a, l, r); /* first the array must be transformed into a heap */
	while (r - l > 0){
		/* while the array has not been sorted completely */
		exch(a[l], a[r]); /* exchange the root with the last element in the array */
		/* now the element a[l] is sorted (is in it's final position) */
		/* call fixDown on the root to transform the array into a heap again (due to previous exch())
		since the last element (a[r]) is now in it's final position, it "gets excluded" from the rest
		of the sorting process, that's why r is decremented */
		fixDown(a, l, --r, l);
	}

}

void distcount(int a[], int l, int r){
	/* counting sort implementation */
	int i, j, cnt[M + 1]; /* M is the largest element in the array to sort */
	/*cnt[M+1] is like a histogram for the values in the array to sort */

	int b[maxN]; /* will store the ordered elements */

	/* initially, set all values in the histogram to 0 */
	for (j = 0; j <= M; j++)
		cnt[j] = 0;

	for (i = l; i <= r; i++)
		/* increment the number of times the element a[i] appears in the array*/
		cnt[a[i] + 1]++;

	for (j = l; j < M; j++)
		/* transform the histogram into a cumulutative distribution */
		cnt[j] += cnt[j - 1];
	/* now it's known in which index each of the possible numbers ends */

	for (i = l; i <= r; i++)
		/* fill the vector b with elements in sorted order */
		b[cnt[a[i]]++] = a[i];

	for (i = l; i <= r; i++)
		/* copy the elements from b to a, making it sorted */
		a[i] = b[i];
}