#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DO 1
#define DONT 0

int main(void) {
	FILE *f;
	int ret=0;
	int x, y;
	long size, sum, i, j;
	char *buf;
	int enable = DO;

	f = fopen("input", "r");
	if (!f) {
		perror("Error opening file");
		ret = 1;
		goto exit_0;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buf = malloc(size + 1);
	if (!buf) {
		fprintf(stderr, "Memory allocation failed\n");
		fclose(f);
		ret = 1;
		goto exit_0;
	}
	fread(buf, 1, size, f);
	fclose(f);
	sum = 0;
	// Part 1
	for (i = 0; i < size; i++) {
	if (buf[i] == 'm' && buf[i+1] == 'u' && buf[i+2] == 'l' && buf[i+3] == '(') {
		j = i + 4;
		if (!isdigit(buf[j]))
			continue;
		x = 0;
		while (isdigit(buf[j])) {
		x = x * 10 + (buf[j] - '0');
		j++;
		}
		if (buf[j] != ',')
			continue;
		j++;
		if (!isdigit(buf[j]))
			continue;
		y = 0;
		while (isdigit(buf[j])) {
		y = y * 10 + (buf[j] - '0');
		j++;
		}
		if (buf[j] != ')')
			continue;
		sum += x * y;
	}
	}
	printf("\nSum of all products = %ld\n", sum);
	// Part 2
	sum = 0;
	for (i = 0; i < size; i++) {
	if (enable == DO && buf[i] == 'd' && buf[i+1] == 'o' && buf[i+2] == 'n' && buf[i+3] == '\'' && buf[i+4] == 't' && buf[i+5] == '(' && buf[i+6] == ')')
		enable = DONT;
	else if (enable == DONT && buf[i] == 'd' && buf[i+1] == 'o' && buf[i+2] == '(' && buf[i+3] == ')')
		enable = DO;
	else if (enable == DO && buf[i] == 'm' && buf[i+1] == 'u' && buf[i+2] == 'l' && buf[i+3] == '(') {
		j = i + 4;
		if (!isdigit(buf[j]))
			continue;
		x = 0;
		while (isdigit(buf[j])) {
		x = x * 10 + (buf[j] - '0');
		j++;
		}
		if (buf[j] != ',')
			continue;
		j++;
		if (!isdigit(buf[j]))
			continue;
		y = 0;
		while (isdigit(buf[j])) {
		y = y * 10 + (buf[j] - '0');
		j++;
		}
		if (buf[j] != ')')
			continue;
		sum += x * y;
	}
	}
	printf("\nSum of all enable products = %ld\n", sum);
	free(buf);
	exit_0:
		return ret;
}
