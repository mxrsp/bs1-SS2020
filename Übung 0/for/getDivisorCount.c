#include<stdio.h>

extern void getDivisorCount(int zahl, int* result);

int eingabeZahl() {
    int eingabe;
    printf("Geben Sie eine natürliche Zahl ein: ");
    scanf("%d", &eingabe);
    return eingabe;
}

void printResult(int* result) {

    printf("Anzahl der Teiler mit For-Schleife : %d\n", *result);
    
}

int main() {
	// Rechenvorgang
    int ergebnis;
    int* result = &ergebnis;
    int zahl = eingabeZahl();
    getDivisorCount(zahl, result);
    printResult(result);
    
	return 0;
}
