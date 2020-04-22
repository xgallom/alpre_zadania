#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **create(int riadky, int stlpce)
{
	int **p, i;
	p = (int **) malloc(riadky * sizeof(int *));
	for(i = 0; i < riadky; i++)
		p[i] = (int *) malloc(stlpce * sizeof(int));
	return p;
}

int **AlokujNapln(char *nazovSuboru, int *rozmerX, int *rozmerY)
{
	FILE *subor = fopen(nazovSuboru, "rt");

	fscanf(subor, "%d%d", rozmerX, rozmerY);
	int **data = create(*rozmerY, *rozmerX);

	int y = 0;
	for(; y < *rozmerY; ++y) {
		int x = 0;
		for(; x < *rozmerX; ++x) {
			fscanf(subor, "%d", data[y] + x);
		}
	}

	fclose(subor);

	return data;
}

void Uvolni(int **data, int rozmerX, int rozmerY)
{
	int y = 0;
	for(; y < rozmerY; ++y)
		free(data[y]);
	free(data);
}

void Vypis(int **data, int rozmerX, int rozmerY)
{
	while(rozmerY--) {
		int *riadok = *data++;
		int x = 0;
		for(; x < rozmerX; ++x)
			printf("%d ", riadok[x]);

		printf("\n");
	}
}

int MinTabExt(int **data, int rozmerX, int rozmerY, int *sX, int *sY)
{
	int minimum = data[0][0];
	*sX = *sY = 0;

	int y = 0;
	for(; y < rozmerY; ++y) {
		int x = 0;
		for(; x < rozmerX; ++x) {
			if(data[y][x] < minimum) {
				*sX = x;
				*sY = y;
				minimum = data[y][x];
			}
		}
	}

	return minimum;
}

int SpecSum (int **data, int rozmerX, int rozmerY)
{
	int x, y;

	printf("Sucet stlpcov: ");
	for(x = 0; x < rozmerX; ++x) {
		int sucetStlpca = 0;

		for(y = 0; y < rozmerY; ++y)
			sucetStlpca += data[y][x];

		printf("%d ", sucetStlpca);
	}

	int sucet = 0;

	printf("\nSucet Riadkov: ");
	for(y = 0; y < rozmerY; ++y) {
		int sucetRiadku = 0;

		for(x = 0; x < rozmerX; ++x)
			sucetRiadku += data[y][x];

		sucet += sucetRiadku;

		printf("%d ", sucetRiadku);
	}
	printf("\n");

	return sucet;
}

int main()
{
	char nazovSuboru[100];
	printf("Zadaj nazov suboru: ");
	scanf("%s", nazovSuboru);

	int rozmerX, rozmerY;
	int **data = AlokujNapln(nazovSuboru, &rozmerX, &rozmerY);

	Vypis(data, rozmerX, rozmerY);

	int minimumX, minimumY;
	int minimum = MinTabExt(data, rozmerX, rozmerY, &minimumX, &minimumY);
	printf("Minimum matice v riadku %d, stlpci %d: %d\n", minimumY, minimumX, minimum);

	int suma = SpecSum(data, rozmerX, rozmerY);
	printf("Suma: %d\n", suma);

	Uvolni(data, rozmerX, rozmerY);

	return 0;
}
