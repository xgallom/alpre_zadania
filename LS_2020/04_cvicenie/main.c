#include <stdio.h>

int priklad_1(void)
{
	int pocetRiadkov;

	printf("Zadaj pocet riadkov <1, 10>: ");
	scanf("%d", &pocetRiadkov);

	if(pocetRiadkov < 1 || pocetRiadkov > 10) {
		printf("Cislo nie je z daneho intervalu\n");
		return 1;
	}

	int hodnota = 0, riadok = 0;
	for(; riadok < pocetRiadkov; ++riadok) {
		int stlpec = 0;
		for(; stlpec < riadok + 1; ++stlpec)
			printf("%2d ", ++hodnota);

		printf("\n");
	}

	return 0;
}

int priklad_3(void)
{
	int pocetRiadkov;

	printf("Zadaj pocet riadkov <1, 15>: ");
	scanf("%d", &pocetRiadkov);

	if(pocetRiadkov < 1 || pocetRiadkov > 15) {
		printf("Cislo nie je z daneho intervalu\n");
		return 1;
	}

	int riadok = 0;
	for(; riadok < pocetRiadkov; ++riadok) {
		printf("%2d: ", riadok + 1);

		int stlpec = pocetRiadkov - riadok;
		for(; stlpec > 0; --stlpec)
			printf("%2d ", stlpec);

		printf("\n");
	}

	return 0;
}

int priklad_4(void)
{
	int maximum;

	printf("Zadaj maximum <1, *): ");
	scanf("%d", &maximum);

	if(maximum < 1) {
		printf("Cislo nie je z daneho intervalu\n");
		return 1;
	}

	int k = 1, sucet = 0;
	for(; k <= maximum; ++k) {
		sucet += k;

		if(sucet % 3 == 0)
			printf("%d ", k);
	}

	printf("\n");

	return 0;
}

int priklad_8(void)
{
	int rozmerHviezdy, pocetHviezd;

	printf("Zadaj cislo rozmer hviezdy *neparne* <1, 15>, zadaj pocet hviezd <1, 5>: ");
	scanf("%d%d", &rozmerHviezdy, &pocetHviezd);

	if(rozmerHviezdy < 1 || rozmerHviezdy > 15 || rozmerHviezdy % 2 == 0 || pocetHviezd < 1 || pocetHviezd > 5) {
		printf("Zly vstup\n");
		return 1;
	}

	int riadok = 0;
	for(; riadok < rozmerHviezdy; ++riadok) {
		int hviezda = 0;
		for(; hviezda < pocetHviezd; ++hviezda) {
			int stlpec = 0;
			for(; stlpec < rozmerHviezdy; ++stlpec) {
				char znak = '-';

				int absolutnaPozicia = riadok;
				if(riadok > rozmerHviezdy / 2)
					absolutnaPozicia = rozmerHviezdy - riadok - 1;

				if(riadok == rozmerHviezdy / 2 || stlpec == rozmerHviezdy / 2)
					znak = '*';
				else if(stlpec == absolutnaPozicia || rozmerHviezdy - stlpec - 1 == absolutnaPozicia)
					znak = '*';

				putchar(znak);
			}
		}

		putchar('\n');
	}

	printf("\n");

	return 0;
}

int main()
{
	printf("priklad_1:\n");
	priklad_1();

	printf("\npriklad_3:\n");
	priklad_3();

	printf("\npriklad_4:\n");
	priklad_4();

	printf("\npriklad_8:\n");
	priklad_8();

	return 0;
}
