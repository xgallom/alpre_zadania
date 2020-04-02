#include <stdio.h>
#include <string.h>

int priklad_1(void)
{
	char pole[21];

	printf("Zadaj retazec *max 20 znakov*: ");
	scanf("%20s", pole);

	int pocetZnakov = strlen(pole);

	int znak = 0;
	for(; znak < pocetZnakov / 2; ++znak) {
		char c = pole[znak];
		pole[znak] = pole[pocetZnakov - znak - 1];
		pole[pocetZnakov - znak - 1] = c;
	}

	printf("Obratene pole: %s", pole);

	return 0;
}

int priklad_2(void)
{
	char pole[11];

	// Zmazanie noveho riadku z minuleho prikladu
	getchar();

	printf("Zadaj retazec *max 10 znakov*: ");

	int pocetZnakov = 0;
	for(;;) {
		if(pocetZnakov == 11) {
			printf("Prekonany maximalny pocet znakov\n");
			return 1;
		}

		char znak = getchar();

		if(znak == '\n') {
			pole[pocetZnakov] = '\0';
			break;
		}

		pole[pocetZnakov++] = znak;
	}

	int znak = 0, textJeSkrateny = 0;
	for(; znak < pocetZnakov; ++znak) {
		if(pole[znak] == '*') {
			if(pocetZnakov >= 10) {
				textJeSkrateny = 1;
				break;
			}

			int posun = pocetZnakov++;
			for(; posun > znak; --posun)
				pole[posun + 1] = pole[posun];
			pole[znak++] = '+';
			pole[znak] = '*';

			if(pocetZnakov >= 10) {
				textJeSkrateny = 1;
				break;
			}

			posun = pocetZnakov++;
			for(; posun > znak; --posun)
				pole[posun + 1] = pole[posun];
			pole[znak++] = '*';
			pole[znak] = '-';
		}
	}

	printf("Vystup: %s\n", pole);

	if(textJeSkrateny != 0)
		printf("Text je skrateny\n");

	return 0;
}

int priklad_3(void)
{
	char pole[31], naZmazanie[16];

	printf("Zadajte text *max 30 znakov*: ");
	int pocetZnakovPola = 0;
	for(;;) {
		if(pocetZnakovPola == 31) {
			printf("Pole je prilis dlhe\n");
			return 1;
		}

		char znak = getchar();

		if(znak == '\n') {
			pole[pocetZnakovPola] = '\0';
			break;
		}

		pole[pocetZnakovPola++] = znak;
	}

	printf("Zadajte text *3-15 znakov*: ");
	int pocetZnakovNaZmazanie = 0;
	for(;;) {
		if(pocetZnakovNaZmazanie == 16) {
			printf("Pole je prilis dlhe\n");
			return 1;
		}

		char znak = getchar();

		if(znak == '\n') {
			if(pocetZnakovNaZmazanie < 3) {
				printf("Pole je prilis kratke\n");
				return 1;
			}

			naZmazanie[pocetZnakovNaZmazanie] = '\0';
			break;
		}

		naZmazanie[pocetZnakovNaZmazanie++] = znak;
	}

	int znak = 0;
	for(; znak < pocetZnakovPola; ++znak) {
		int posun = 0, najdene = 1;
		for(; posun < pocetZnakovNaZmazanie; ++posun) {
			if(pole[znak + posun] != naZmazanie[posun]) {
				najdene = 0;
				break;
			}
		}

		if(najdene != 0) {
			pocetZnakovPola -= pocetZnakovNaZmazanie;

			int posun = znak;
			for(; posun <= pocetZnakovPola; ++posun)
				pole[posun] = pole[posun + pocetZnakovNaZmazanie];

			--znak;
		}
	}

	printf("Vystup: %s\n", pole);

	return 0;
}

int priklad_4(void)
{
	FILE *suborVstup = fopen("vstup.txt", "rt");
	FILE *suborVystup = fopen("vystup.txt", "wt");

	if(suborVstup == NULL || suborVystup == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	for(;;) {
		for(;;) {
			char znak = getc(suborVstup);

			if(znak == EOF) {
				fclose(suborVstup);
				fclose(suborVystup);
				return 0;
			}
			else if(znak == ' ' || znak == '\n')
				break;
		}

		for(;;) {
			char znak = getc(suborVstup);

			if(znak == EOF) {
				putc(' ', suborVystup);
				fclose(suborVstup);
				fclose(suborVystup);
				return 0;
			}
			else if(znak == ' ' || znak == '\n') {
				putc(' ', suborVystup);
				break;
			}

			putc(znak, suborVystup);
		}
	}
}

int main()
{
	printf("priklad_1:\n");
	priklad_1();

	printf("\npriklad_2:\n");
	priklad_2();

	printf("\npriklad_3:\n");
	priklad_3();

	printf("\npriklad_4:\n");
	priklad_4();

	return 0;
}
