#include<stdio.h>

extern void getDivisorCount(int zahl, int *result);
void printResult();

int ergebnis;
int* result = &ergebnis;
int zahl = 15;

int main() {
	// Rechenvorgang
    getDivisorCount(zahl, result); 
    printResult();
	return 0;
}

void printResult() {
    printf("value is : %d\n", *result);
}
