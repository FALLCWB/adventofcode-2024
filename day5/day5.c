#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YES 1
#define NO 0

struct rule {
	int value;
	struct rule *next;
};
void insert (struct rule *list[], int idx, int value)
{
	struct rule *node = malloc(sizeof(struct rule));
	if (node == NULL)
		return;
	node->value = value;
	node->next = list[idx];
	list[idx] = node;
}
void clear_list(struct rule *list[])
{
	int idx;
	for (idx = 0; idx < 100; idx++) {
		struct rule *p = list[idx];
		while (p != NULL) {
			struct rule *tmp = p;
			p = p->next;
			free(tmp);
		}
		list[idx] = NULL;
	}
}
int main(void)
{
	FILE *f;
	struct rule *list[100], *print;
	int i, j, pages[25], size, idx, value, correct, current, cp;
	int middles = 0;
	int mcorrected = 0;
	char line[256], *token;

	for (i = 0; i < 100; i++) {
		list[i] = NULL;
	}
	f = fopen("input", "r");
	if (!f) {
		perror("Error opening file");
		return 1;
	}
	while (fgets(line, sizeof(line), f)) {
		if (line[0] == '\n' || line[0] == '\0')
			continue;
		if (strchr(line, '|')) {
			if (sscanf(line, "%d|%d", &idx, &value) == 2)
				insert(list, idx, value);
		}
		else if (strchr(line, ',')) {
			size = 0;
			token = strtok(line, ",\n");
			while (token){
				pages[size++] = atoi(token);
				token = strtok(NULL, ",\n");
			}
			correct = YES;
			for (i = 0; i < size; i++){
				current = pages[i];
				cp = i;
				for (j = i - 1; j >= 0; j--){
					print = list[current];
					while (print != NULL){
						if (print->value == pages[j]) {
							correct = NO;
							pages[cp] = pages[j];
							pages[j] = current;
							cp = j;
						}
						print = print->next;
					}
				}
			}
			if (correct == YES) {
				middles += pages[size / 2];
			}
			else {
				mcorrected += pages[size / 2];
			}
		}
	}
	printf("Sum of the middle values = %d\n", middles);
	printf("Sum of the middle of the corrected values = %d\n", mcorrected);
	clear_list(list);
	return 0;
}
