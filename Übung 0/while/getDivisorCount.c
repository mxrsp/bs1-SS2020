#include<stdio.h>
extern int getDivisorCount(unsigned int zahl);

int eingabeZahl() {
    int eingabe;
    printf("Geben Sie eine natürliche Zahl ein: ");
    scanf("%u", &eingabe);
    return eingabe;
}

void ausgabeErgebnis(int ergebnis) {
    printf("Anzahl der Teiler mit While-Schleife: %u \n", ergebnis);
}

int main() {
	
    ausgabeErgebnis(getDivisorCount(eingabeZahl()));
	
	return 0;
}
