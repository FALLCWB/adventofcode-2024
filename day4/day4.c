#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *f;
	int ret = 0;
	char buffer[1024];
	char letter[1024][1024];
	int  i, j, x, y = 0;
	int sum = 0;

	f = fopen("input", "r");
	if (!f) {
		perror("Error opening file");
		ret = 1;
		goto exit_0;
	}
	while (fgets(buffer, sizeof(buffer), f)) {
        x = 0;
        while (buffer[x] != '\n') {
            letter[y][x] = buffer[x];
			x++;
        }
		y++;	
	}
	// Part 1
	for (i = 0; i <= y;  i++){
			for (j = 0; j <= x; j++){
				if (letter[i][j] == 'X' && letter[i][j+1] == 'M'
				&& letter[i][j+2] == 'A' && letter[i][j+3] == 'S')
						sum++;
				if (letter[i][j] == 'S' && letter[i][j+1] == 'A'
				&& letter[i][j+2] == 'M' && letter[i][j+3] == 'X')
						sum++;						
				if (letter[i][j] == 'X' && letter[i+1][j] == 'M'
				&& letter[i+2][j] == 'A' && letter[i+3][j] == 'S')
						sum++;
				if (letter[i][j] == 'S' && letter[i+1][j] == 'A'
				&& letter[i+2][j] == 'M' && letter[i+3][j] == 'X')
						sum++;
				if (letter[i][j] == 'X' && letter[i+1][j+1] == 'M'
				&& letter[i+2][j+2] == 'A' && letter[i+3][j+3] == 'S')
						sum++;
				if (letter[i][j] == 'S' && letter[i+1][j+1] == 'A'
				&& letter[i+2][j+2] == 'M' && letter[i+3][j+3] == 'X')
						sum++;
				if (letter[i][j] == 'X' && letter[i+1][j-1] == 'M'
				&& letter[i+2][j-2] == 'A' && letter[i+3][j-3] == 'S')
						sum++;
				if (letter[i][j] == 'S' && letter[i+1][j-1] == 'A'
				&& letter[i+2][j-2] == 'M' && letter[i+3][j-3] == 'X')
						sum++;
			}
	}
	printf("\nSum of XMAS = %d\n", sum);
	// Part 2
	sum = 0;
	for (i = 0; i <= y;  i++){
			for (j = 0; j <= x; j++){
					if ((letter[i][j] == 'M' && letter[i][j+2] == 'S'
						&& letter[i+1][j+1] == 'A' && letter[i+2][j] == 'M'
						&& letter[i+2][j+2] == 'S') || (letter[i][j] == 'S'
						&& letter[i][j+2] == 'M' && letter[i+1][j+1] == 'A'
						&& letter[i+2][j] == 'S' && letter[i+2][j+2] == 'M')
						|| (letter[i][j] == 'S' && letter[i][j+2] == 'S'
						&& letter[i+1][j+1] == 'A' && letter[i+2][j] == 'M'
						&& letter[i+2][j+2] == 'M') || (letter[i][j] == 'M'
						&& letter[i][j+2] == 'M' && letter[i+1][j+1] == 'A'
						&& letter[i+2][j] == 'S' && letter[i+2][j+2] == 'S'))
						sum++;
			}
	}
	printf("\nSum of XMAS Part 2 = %d\n", sum);
	exit_0:
		return ret;
}
