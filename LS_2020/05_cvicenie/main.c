#include <stdio.h>

int priklad_1(void)
{
	float zaklad;

	printf("Zadaj zaklad nasobkov: ");
	scanf("%f", &zaklad);

	FILE *subor = fopen("nasobky.txt", "wt");
	if(subor == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	int riadok = 1;
	for(; riadok <= 10; ++riadok)
		fprintf(subor, "%2d * %.2f = %.2f\n", riadok, zaklad, riadok * zaklad);

	fclose(subor);

	return 0;
}

int priklad_3(void)
{
	FILE *subor1 = fopen("prvy.txt", "rt");
	FILE *subor2 = fopen("druhy.txt", "rt");

	if(subor1 == NULL || subor2 == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	int pocetRozdielnych = 0;
	char znak1, znak2;

	for(;;) {
		znak1 = getc(subor1);
		znak2 = getc(subor2);

		if(znak1 == EOF && znak2 == EOF)
			break;
		else if(znak1 == EOF) {
			int rozdielSuborov = 1;
			for(;;++rozdielSuborov) {
				znak2 = getc(subor2);

				if(znak2 == EOF) {
					printf("Subor 2 je dlhsi o: %d\n", rozdielSuborov);
					break;
				}
			}

			break;
		}
		else if(znak2 == EOF) {
			int rozdielSuborov = 1;
			for(;;++rozdielSuborov) {
				znak1 = getc(subor1);

				if(znak1 == EOF) {
					printf("Subor 2 je dlhsi o: %d\n", rozdielSuborov);
					break;
				}
			}

			break;
		}

		if(znak1 != znak2)
			++pocetRozdielnych;
	}

	if(pocetRozdielnych == 0)
		printf("Subory su identicke\n");
	else
		printf("Pocet rozdielnych znakov: %d\n", pocetRozdielnych);

	fclose(subor1);
	fclose(subor2);

	return 0;
}

int priklad_4(void)
{
	FILE *suborVstup = fopen("vstup.txt", "rt");
	FILE *suborVystup = fopen("cisla.txt", "at");

	if(suborVstup == NULL || suborVystup == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	int pocetMalych = 0;
	for(;;) {
		char znak = getc(suborVstup);

		if(znak == EOF)
			break;

		putc(znak, suborVystup);

		if(znak >= 'a' && znak <= 'z')
			++pocetMalych;
		else if(znak == '\n') {
			fprintf(suborVystup, "%d\n", pocetMalych);
			pocetMalych = 0;
		}
	}

	fclose(suborVstup);
	fclose(suborVystup);

	return 0;
}

int priklad_6(void)
{
	FILE *subor = fopen("vystup.txt", "wt");
	if(subor == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 1;
	}

	printf("Zadavaj znaky ukoncene *: ");

	for(;;) {
		char znak = getchar();

		if(znak == '*')
			break;
		else if(znak >= 'a' && znak <= 'z')
			znak = znak - 'a' + 'A';
		else if(znak == '\t' || znak == '\n')
			znak = ' ';
		else if(znak < 'A' || znak > 'Z')
			znak = '-';

		putc(znak, subor);
	}

	fclose(subor);

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

	printf("\npriklad_6:\n");
	priklad_6();

	return 0;
}
