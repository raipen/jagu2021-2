#include <stdio.h>
#include <time.h>
#define SWAP(a,b,c) c=a, a=b, b=c
#define MAX_SIZE 1001

void sort(int l[], int n) {
	int i, j, m, t;
	for (i = 0;i < n - 1;i++) {
		m = i;
		for (j = i + 1;j < n;j++) {
			if (l[j] < l[m]) {
				m = j;
			}
		}
		SWAP(l[i], l[m], t);
	}
}

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double d;

	printf("     n\trepetitions\ttime\n");
	for (n = 0;n <= 1000;n += step) {
		
		long r = 0;
		clock_t start = clock();
		do {
			r++;

			for (i = 0;i < n;i++)
				a[i] = n - i;

			sort(a, n);
		} while (clock() - start < 1000);

		d = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		d /= r;
		printf("%6d\t%9d\t%f\n", n,r, d);
		if (n == 100) step = 100;
	}
}