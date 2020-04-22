#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *AlokujNapln(const char *nazovSuboru, int *velkost)
{
	FILE *subor = fopen(nazovSuboru, "rt");

	if(subor == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return NULL;
	}

	int *data = (int *) malloc(sizeof(int) * 500);

	if(data == NULL) {
		printf("Nepodarilo sa alokovat pole");
		fclose(subor);
		return NULL;
	}

	*velkost = 0;
	int cislo;

	while(fscanf(subor, "%d", &cislo) == 1) {
		if(cislo > 0) {
			data[(*velkost)++] = cislo;

			if(*velkost == 500)
				break;
		}
	}

	fclose(subor);

	return data;
}

void Vypis(int *pole, int velkost)
{
	while(velkost--)
		printf("%d ", *pole++);
	printf("\n");
}

int *Maximum(int *pole, int velkost, int *pozicia)
{
	*pozicia = 0;

	int terajsiaPozicia = 0;
	for(; terajsiaPozicia < velkost; ++terajsiaPozicia) {
		if(pole[terajsiaPozicia] > pole[*pozicia])
			*pozicia = terajsiaPozicia;
	}

	return pole + *pozicia;
}

int VymazNeparne(int *pole, int velkost)
{
	int pozicia = velkost - 1;
	for(; pozicia >= 0; --pozicia) {
		if(pole[pozicia] % 2) {
			int mazanie = pozicia;
			for(--velkost; mazanie < velkost; ++mazanie)
				pole[mazanie] = pole[mazanie + 1];
		}
	}

	return velkost;
}

int DuplikujCislo(int *pole, int velkost, int cislo)
{
	int pozicia = 0;
	for(; pozicia < velkost; ++pozicia) {
		if(pole[pozicia] == cislo) {
			if(velkost == 500)
				break;

			int duplikacia = velkost;
			for(; duplikacia > pozicia; --duplikacia)
				pole[duplikacia] = pole[duplikacia - 1];

			++velkost;
			++pozicia;
		}
	}

	return velkost;
}

int main()
{
	char nazovSuboru[100];
	printf("Zadaj nazov suboru: ");
	scanf("%s", nazovSuboru);

	int pocet;
	int *data = AlokujNapln(nazovSuboru, &pocet);

	if(data == NULL)
		return 0;

	Vypis(data, pocet);

	int poziciaMaxima;
	int maximum = *Maximum(data, pocet, &poziciaMaxima);
	printf("Maximum na pozicii %d: %d\n", poziciaMaxima, maximum);

	pocet = VymazNeparne(data, pocet);

	Vypis(data, pocet);

	int cislo;
	printf("Zadaj cislo na duplikaciu: ");
	scanf("%d", &cislo);

	pocet = DuplikujCislo(data, pocet, cislo);

	Vypis(data, pocet);

	return 0;
}
