#include <stdio.h>
#include <string.h>

int priklad_1(void)
{
	char pole[101];

	printf("Zadaj retazec *max 100 znakov*: ");
	scanf("%100s", pole);

	int pocetZnakov = strlen(pole);

	int znak = 0;
	for(; znak < pocetZnakov; ++znak) {
		if(pole[znak] == '*') {
			if(pocetZnakov >= 100)
				break;

			int posun = pocetZnakov++;
			for(; posun > znak; --posun)
				pole[posun + 1] = pole[posun];
			pole[++znak] = '*';
		}
		else if(pole[znak] == '.') {
			int posun = znak;
			for(; posun < pocetZnakov; ++posun)
				pole[posun] = pole[posun + 1];

			--pocetZnakov;
		}
	}

	printf("Vystup: %s\n", pole);

	return 0;
}

int priklad_2(void)
{
	FILE *suborVstup = fopen("vstup.txt", "rt");
	FILE *suborVystup = fopen("vystup.txt", "wt");

	if(suborVstup == NULL || suborVystup == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	for(;;) {
		char pole[100];

		int pocetZnakov = 0;
		for(;;) {
			char znak = getc(suborVstup);

			if(znak == EOF) {
				fclose(suborVstup);
				fclose(suborVystup);

				return 0;
			}
			else if(znak == '\n')
				break;

			pole[pocetZnakov++] = znak;
		}

		int znak = 0;
		for(; znak < pocetZnakov; ++znak)
			putc(pole[pocetZnakov - znak - 1], suborVystup);
		putc('\n', suborVystup);
	}
}

int priklad_3(void)
{
	char sprava[101], kluc[101];

	printf("Zadaj spravu *max 100 znakov*: ");
	scanf("%100s", sprava);

	printf("Zadajte kluc *max 100 znakov*: ");
	scanf("%100s", kluc);

	int dlzkaSpravy = strlen(sprava);
	int dlzkaKluca = strlen(kluc);

	int znakSpravy = 0, znakKluca = 0;
	for(; znakSpravy < dlzkaSpravy; ++znakSpravy) {
		char posun = (sprava[znakSpravy] - 'A') + (kluc[znakKluca] - 'A') + 1;
		sprava[znakSpravy] = (posun % ('Z' - 'A' + 1)) + 'A';

		znakKluca = (znakKluca + 1) % dlzkaKluca;
	}

	printf("Vystup: %s\n", sprava);

	return 0;
}

int priklad_4(void)
{
	FILE *subor = fopen("list.txt", "rt");

	if(subor == NULL) {
		printf("Chyba: otvaranie suboru\n");
		return 1;
	}

	int najdlhsiRiadok = -1, dlzkaRiadku = -1;
	for(;; ++dlzkaRiadku) {
		char znak = getc(subor);

		if(znak == EOF)
			break;
		else if(znak == '\n') {
			if(najdlhsiRiadok > dlzkaRiadku || najdlhsiRiadok == -1)
				najdlhsiRiadok = dlzkaRiadku;

			dlzkaRiadku = -1;
		}
	}

	if(fclose(subor) != 0) {
		printf("Chyba: zatvaranie suboru\n");
		return 1;
	}

	printf("Najkratsi riadok ma: %d\n", najdlhsiRiadok);

	return 0;
}

int priklad_5(void)
{
	int polomerVlajky;

	printf("Zadaj cislo polomer vlajky *neparne* <3, 15>: ");
	scanf("%d", &polomerVlajky);

	if(polomerVlajky < 3 || polomerVlajky > 15 || polomerVlajky % 2 == 0) {
		printf("Zly vstup\n");
		return 1;
	}

	FILE *subor = fopen("obrazok.txt", "wt");

	if(subor == NULL) {
		printf("Chyba: otvaranie suboru\n");
		return 1;
	}

	int rozmerVlajky = polomerVlajky * 2 - 1;

	int riadok = 0;
	for(; riadok < polomerVlajky; ++riadok) {
		int stlpec = 0;
		for(; stlpec < rozmerVlajky; ++stlpec) {
			char znak = '-';

			if(stlpec < riadok + 1)
				znak = '*';

			putc(znak, subor);
		}

		putc('\n', subor);
	}

	riadok = 0;
	for(; riadok < rozmerVlajky; ++riadok)
		putc('*', subor);
	putc('\n', subor);

	riadok = 0;
	for(; riadok < polomerVlajky; ++riadok) {
		int stlpec = 0;
		for(; stlpec < rozmerVlajky; ++stlpec) {
			char znak = 'o';

			if(stlpec < polomerVlajky - riadok)
				znak = '*';

			putc(znak, subor);
		}

		putc('\n', subor);
	}

	if(fclose(subor) != 0) {
		printf("Chyba: zatvaranie suboru\n");
		return 1;
	}

	return 0;
}

int priklad_6(void)
{
	int rozmerPola;
	float pole[50];

	printf("Zadaj rozmer pola <0, 50>: ");
	scanf("%d", &rozmerPola);

	if(rozmerPola < 0 || rozmerPola > 50) {
		printf("Zly vstup\n");
		return 1;
	}

	printf("Zadaj %d hodnot pola:\n", rozmerPola);
	float *hodnota = pole;
	for(; hodnota < pole + rozmerPola; ++hodnota)
		scanf("%f", hodnota);

	printf("\nZaporne hodnoty pola:\n");
	hodnota = pole;
	for(; hodnota < pole + rozmerPola; ++hodnota) {
		if(*hodnota < 0.0)
			printf("%.2f\n", *hodnota);
	}

	return 0;
}

int priklad_7(void)
{
	int rozmerPola;
	int cisla[50], kladne[50], zaporne[50];

	printf("Zadaj rozmer pola <0, 50>: ");
	scanf("%d", &rozmerPola);

	if(rozmerPola < 0 || rozmerPola > 50) {
		printf("Zly vstup\n");
		return 1;
	}

	printf("Zadaj %d hodnot pola:\n", rozmerPola);
	int *hodnota = cisla;
	for(; hodnota < cisla + rozmerPola; ++hodnota)
		scanf("%d", hodnota);

	int rozmerKladnych = 0;
	int *hodnotaKladne = kladne;
	for(hodnota = cisla; hodnota < cisla + rozmerPola; ++hodnota) {
		if(*hodnota > 0) {
			*hodnotaKladne++ = *hodnota;
			++rozmerKladnych;
		}
	}

	int rozmerZapornych = 0;
	int *hodnotaZaporne = zaporne;
	for(hodnota = cisla; hodnota < cisla + rozmerPola; ++hodnota) {
		if(*hodnota < 0) {
			*hodnotaZaporne++ = *hodnota;
			++rozmerZapornych;
		}
	}

	printf("Kladne: ");
	for(hodnota = kladne; hodnota < kladne + rozmerKladnych; ++hodnota)
		printf("%d ", *hodnota);
	printf("\n");

	printf("Zaporne: ");
	for(hodnota = zaporne; hodnota < zaporne + rozmerZapornych; ++hodnota)
		printf("%d ", *hodnota);
	printf("\n");

	return 0;
}

void vloz_do_stredu(char *str, char c)
{
	int rozmer = strlen(str);

	int posun = rozmer;
	for(; posun >= rozmer / 2; --posun)
		str[posun + 1] = str[posun];

	str[rozmer / 2] = c;
}

int priklad_8(void)
{
	char str[100];
	char c;

	printf("Zadaj retazec: ");
	scanf("%s", str);

	printf("Zadaj znak: ");
	scanf(" %c", &c);

	vloz_do_stredu(str, c);

	printf("Vystup: %s", str);

	return 0;
}

void odstran_male_pismena(char *str)
{
	while(*str != '\0') {
		if(*str >= 'a' && *str <= 'z') {
			char *mazanie = str;
			for(; *mazanie != '\0'; ++mazanie)
				mazanie[0] = mazanie[1];
		}
		else
			++str;
	}
}

int priklad_9(void)
{
	char str[100];

	printf("Zadaj retazec: ");
	scanf("%s", str);

	odstran_male_pismena(str);

	printf("Vystup: %s\n", str);

	return 0;
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

	printf("\npriklad_5:\n");
	priklad_5();

	printf("\npriklad_6:\n");
	priklad_6();

	printf("\npriklad_7:\n");
	priklad_7();

	printf("\npriklad_8:\n");
	priklad_8();

	printf("\npriklad_9:\n");
	priklad_9();

	return 0;
}
