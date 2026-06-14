#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 130
#define UP 0
#define RIGHT 90
#define DOWN 180
#define LEFT 270

int main(void)
{
	FILE *f;
	char map[SIZE][SIZE], buffer[164], *ptr;
	int pc, pl;
	int spaces = 0;
	int line = 0;
	int direction = 0;
	bool walking = true;

	f = fopen("./input", "r");
	if (!f) {
		perror("Error opening file");
		return 1;
	}
	while (fgets(buffer, sizeof(buffer), f)) {
		strncpy(map[line], buffer, SIZE);
		ptr = strchr(buffer, '^');
		if (ptr != NULL) {
			pc = ptr - buffer;
			pl = line;
			map[pl][pc] = 'x';
			spaces = 1;
		}
		line++;
	}
	fclose(f);
	while (walking){
		while (direction == UP && walking){
			if (pl == 0){
				walking = false;
			} else if (map[pl-1][pc] == '.') {
				map[--pl][pc] = 'x';
				spaces++;
			} else if (map[pl-1][pc] == 'x'){
				pl--;
			} else if (map[pl-1][pc] == '#'){
				direction = RIGHT;
			}
		}
		while (direction == RIGHT && walking){
			if (pc == SIZE-1){
				walking = false;
			} else if (map[pl][pc+1] == '.') {
				map[pl][++pc] = 'x';
				spaces++;
			} else if (map[pl][pc+1] == 'x'){
				pc++;
			} else if (map[pl][pc+1] == '#'){
				direction = DOWN;
			}
		}
		while (direction == DOWN && walking){
			if (pl == SIZE-1){
				walking = false;
			} else if (map[pl+1][pc] == '.') {
				map[++pl][pc] = 'x';
				spaces++;
			} else if (map[pl+1][pc] == 'x'){
				pl++;
			} else if (map[pl+1][pc] == '#'){
				direction = LEFT;
			}
		}
		while (direction == LEFT && walking){
			if (pc == 0){
				walking = false;
			} else if (map[pl][pc-1] == '.') {
				map[pl][--pc] = 'x';
				spaces++;
			} else if (map[pl][pc-1] == 'x'){
				pc--;
			} else if (map[pl][pc-1] == '#'){
				direction = UP;
			}
		}
	}
	printf("The guard visited %d distinct positions\n", spaces);
	return 0;
}
