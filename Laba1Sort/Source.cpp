#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void qsortx(int *a, int low, int  high, long long* movents, long long* compasion) {

	int i = 0, j = 0;
	int tmp = 0, medianofthree = 0;

	i = low;
	j = high;
	int k = 0, l = 0, m = 0;
	k = *(a + 0);
	l = *(a + high);
	m = *(a + (high + low) / 2);
	/*Median-of-three*/
	if (k > l && k < m || k < l && k > m)
		medianofthree = k;
	else
		if (l > k && l < m || l < k && l > m)
			medianofthree = l;
		else
			medianofthree = m;
	/*Median-of-three*/
	//printf("\n%d\n", medianofthree);
	do {
		while (*(a + i) < medianofthree)
		{
			i++;
			++(*compasion);
		}
		while (*(a + j) > medianofthree)
		{
			j--;
			++(*compasion);
		}
		if (i <= j)
		{
			if (*(a + i) > *(a + j))
			{
				tmp = *(a + i);
				*(a + i) = *(a + j);
				*(a + j) = tmp;
				*movents = *movents + 2;
			}
			i++;
			if (j > 0)
			{
				j--;
			}
		}
	} while (i <= j);

	if (i < high)
	{
		qsortx(a, i, high, movents, compasion);
	}
	if (j > low)
	{
		qsortx(a, low, j, movents, compasion);
	}

}

void insert(int *a, int N, long long* movents, long long* compasion) {
	int x = 0;
	int i = 0, j = 0;

	for (i = 0; i < N; i++)
	{
		x = a[i];
		*movents = *movents + 1;
		for (j = i - 1; j >= 0 && a[j] > x; j--)
		{
			a[j + 1] = a[j];
			*compasion = *compasion + 1;
			++(*movents);

		}
		a[j + 1] = x;
		++(*movents);
		

	}
}
int increment(int *inc, int size, long long* movents, long long* compasion) // приращения 
{ // формула сеждвика 
	int p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 = p2 * 2;
			p3 = p3 * 2;
		}
		p1 *= 2;
		*compasion = *compasion + 1;
	} while (3 * inc[s] < size);
	if (s > 0)
		return  --s;
	else return 0;
}


void shell(int *a, int size, long long* movents, long long* compasion) {
	int inc, i, j, seq[50];
	int s;
	int temp;

	// вычисление последовательности приращений
	s = increment(seq, size, movents, compasion);
	while (s >= 0) {
		// сортировка вставками с инкрементами inc[] 
		inc = seq[s--];

		for (i = inc; i < size; i++) {
			temp = a[i];
			++(*compasion);
			for (j = i - inc; (j >= 0) && (a[j] > temp); j = j - inc) {
				a[j + inc] = a[j];
			}
			a[j + inc] = temp;
			*movents = *movents + 2;
			*compasion = *compasion + 2;
		}
	}
}

void select(int *a, int K, long long *movents, long long *compasion) {
	int i, j, k;
	int x;

	for (i = 0; i < K; i++) {   	// i - номер текущего шага
		k = i;
		x = a[i];
		for (j = i + 1; j < K; j++)	// цикл выбора наименьшего элемента
			*compasion = *compasion + 1;
		if (a[j] < x) {
			k = j; x = a[j];
			// k - индекс наименьшего элемента
		}
		++(*compasion);

		a[k] = a[i]; a[i] = x;
		++(*movents);

	}
}
int main()
{
	clock_t start, stop;

	srand(time(NULL));
	int  i = 0, j = 0;
	FILE *fp;

	//fp = fopen("C:\\Users\\Elvin\\Desktop\\numbers.txt", "r");
	puts("1.From file\n2.Random ");
	char c;
	c = getchar();
	long long movents = 0;
	long long compasion = 0;
	char t;
	switch (c)
	{
	case('1'):
	{
		char Path[100];
		puts("Enter the path");
		t = getchar();
		scanf("%s", Path);
		
		fp = fopen(Path, "r");
		if (fp == NULL) {
			printf("No such file");
			getchar();
			getchar();
			return 0;
		}
		int A[10000], B[10000], C[10000], D[10000];
		int N = 10000;
		for (i = 0; i < 10000; i++)
		{
			if (1 != fscanf(fp, "%d", &A[i]));
			B[i] = A[i];
			C[i] = B[i];
			*(D + i) = *(A + i);
		}


		//	for (i=0; i < N; i++)
		//	{
		//		*(A + i) = rand() % 1234567;
		//		printf("%6d", A[i]);

		//		j++;
		//		if(j>100) { putchar('\n'); j = 0; }
		//	}
		start = clock();
		qsortx(A, 0, N - 1, &movents, &compasion);
		stop = clock();
		putchar('\n');
		//	for (i = 0; i < N; i++)
		//	{
		//		printf("%6d", *(A+i));
		//	}
		printf("\n\t\t\t\t\t\tStats for quick");
		printf("\n\t\t\t\t\t\t%.0d  compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d  movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов 
		movents = 0;
		compasion = 0;
		start = clock();
		insert(B, N - 1, &movents, &compasion);
		stop = clock();
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for insert ");
		printf("\n\t\t\t\t\t\t%.0d  compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d  movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC);
		// приведение типов
		//	for (i = 0; i < N; i++)
				//	{
		//		printf("%6d", *(B+i));
		//		}

		movents = 0;
		compasion = 0;

		start = clock();
		shell(C, N - 1, &movents, &compasion);
		stop = clock();
		//		for (i = 0; i < N; i++)
		//		{
		//			printf("%6d", *(C+i));
		//		}
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for shell ");
		printf("\n\t\t\t\t\t\t%.0d compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов
		movents = 0;
		compasion = 0;
		start = clock();
		select(D, N-1, &movents, &compasion);
		stop = clock();
		//		for (i = 0; i < N; i++)
		//		{
		//			printf("%6d", *(D+i));
		//		}
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for select ");
		printf("\n\t\t\t\t\t\t%.0d compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов
		break;
	}

	fclose(fp);
	case('2'):
	{

		int E[52000], F[52000], G[52000], Y[52000];
		int M = 52000;
		for (i = 0; i < M; i++)
		{
			*(E + i) = rand() % 100;
			*(F + i) = *(E + i);
			*(G + i) = *(E + i);
			*(Y + i) = *(E + i);

		}

		//	for (i=0; i < N; i++)
		//	{
		//		*(E + i) = rEnd() % 1234567;
		//		printf("%6d", E[i]);

		//		j++;
		//		if(j>100) { putchar('\n'); j = 0; }
		//	}
		start = clock();
		qsortx(E, 0, M - 1, &movents, &compasion);
		stop = clock();
		putchar('\n');
		//	for (i = 0; i < N; i++)
		//	{
		//		printf("%6d", *(A+i));
		//	}
		printf("\n\t\t\t\t\t\tStats for quick");
		printf("\n\t\t\t\t\t\t%.0d  compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d  movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов 
		movents = 0;
		compasion = 0;
		start = clock();
		insert(F, M - 1, &movents, &compasion);
		stop = clock();
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for insert ");
		printf("\n\t\t\t\t\t\t%.0d  compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d  movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC);
		// приведение типов
		 //	for (i = 0; i < N; i++)
		 //	{
		  //		printf("%6d", *(B+i));
		//		}

		movents = 0;
		compasion = 0;

		start = clock();
		shell(G, M - 1, &movents, &compasion);
		stop = clock();
		//		for (i = 0; i < N; i++)
		//		{
		//			printf("%6d", *(C+i));
		//		}
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for shell ");
		printf("\n\t\t\t\t\t\t%.0d compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов
		movents = 0;
		compasion = 0;
		start = clock();
		select(Y, M-1, &movents, &compasion);
		stop = clock();
		//		for (i = 0; i < N; i++)
		//		{
		//			printf("%6d", *(D+i));
		//		}
		putchar('\n');
		printf("\n\t\t\t\t\t\tStats for select ");
		printf("\n\t\t\t\t\t\t%.0d compasions were made", compasion);
		printf("\n\t\t\t\t\t\t%.0d movements were made", movents);
		printf("\n\t\t\t\t\t\t%f  seconds was spent", (double)(stop - start) / CLOCKS_PER_SEC); // приведение типов
		break;
	}

	default:puts("NO such sort");
	}
	_getch();
	return 0;
}