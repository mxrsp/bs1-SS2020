#include<stdio.h>

extern int getDivisorCount(int zahl);

int main() {
	// Rechenvorgang
    int zahl = 3;
    getDivisorCount(zahl);
	//printf("Divisor count : %d", getDivisorCount(zahl));
	return 0;
}
