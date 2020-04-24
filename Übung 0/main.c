#include<stdio.h>

extern int getDivisorCount(int zahl);

int eingabeZahl() {
	int eingabe;
	printf("\nEingabe Zahl: ");
	scanf_s("%f", &eingabe);
	return eingabe;
}

void ausgabeErgebnis(int ergebnis) {
	printf("\nErgebnis: %f\n", ergebnis);
}

int main() {
	// Rechenvorgang
	ausgabeErgebnis(getDivisorCount(eingabeZahl()));
	return 0;
}