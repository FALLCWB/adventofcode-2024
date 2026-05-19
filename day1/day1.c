#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

static int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main(void)
{
	FILE *f;
	int left[MAX], right[MAX];
	int n = 0, i, j, count;
	long total = 0, similarity = 0;

	f = fopen("input", "r");
	if (!f) {
		perror("input");
		return 1;
	}

	while (n < MAX && fscanf(f, "%d %d", &left[n], &right[n]) == 2)
		n++;
	fclose(f);

	qsort(left, n, sizeof(int), cmp);
	qsort(right, n, sizeof(int), cmp);

	for (i = 0; i < n; i++)
		total += abs(left[i] - right[i]);

	printf("Part 1: %ld\n", total);

	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++) {
			if (right[j] == left[i])
				count++;
		}
		similarity += (long)left[i] * count;
	}

	printf("Part 2: %ld\n", similarity);

	return 0;
}
