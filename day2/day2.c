#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEVEL_UNKNOWN -1
#define LEVEL_INCREASING 0
#define LEVEL_DECREASING 1


int is_safe(int *numbers, int count) {
    int level_inc = LEVEL_UNKNOWN; 
    int diff, i;

    for (i = 1; i < count; i++) {
        diff = numbers[i] - numbers[i-1];
        if (diff == 0 || diff < -3 || diff > 3) {
            return 0;
        }
        if (level_inc == LEVEL_UNKNOWN) {
            level_inc = (diff > 0) ? LEVEL_INCREASING : LEVEL_DECREASING;
        } else if ((diff > 0 && level_inc == LEVEL_DECREASING) || (diff < 0 && level_inc == LEVEL_INCREASING)) {
            return 0;
        }
    }
    return 1;
}

int is_safe_with_dampener(int *numbers, int count) {
    int skip, k, i, tmp[10];

    for ( skip = 0; skip < count; skip++) {
        k = 0;
        for (i = 0; i < count; i++) {
            if (i == skip) continue; 
            tmp[k++] = numbers[i];
        }
        if (is_safe(tmp, k)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file;
    int ret = 0;
    int safe_reports = 0;
    int safe_reports_damp = 0;
    char buffer[1024];
    int numbers[10];
    char *token;
    int count;

    file = fopen("./input", "r");
    if (!file) { 
        perror("Error opening file");
        ret = 1;
        goto exit_0;
    }
    while (fgets(buffer, sizeof(buffer), file)) {
        count = 0;
        token = strtok(buffer, " \t\n");
        while (token != NULL) {
            numbers[count++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }
        if (is_safe(numbers, count)) {
            safe_reports++;
            safe_reports_damp++;
        }
        else if (is_safe_with_dampener(numbers, count)) {
            safe_reports_damp++;
        }       
    }
    printf("Number of safe reports: %d\n", safe_reports);
    printf("Number of safe reports with Dampener: %d\n", safe_reports_damp);
    fclose(file);
    exit_0:
        return ret;
    
}