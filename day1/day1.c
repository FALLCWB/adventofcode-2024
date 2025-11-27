#include <stdio.h>
#include <stdlib.h>

// Comparison function used by qsort to sort integers in ascending order
int cmp_int(const void *left_list, const void *right_list) {
    int left;
    int right;

    left = *(const int *)left_list;
    right = *(const int *)right_list;

    return left - right;
}

int main() {

    FILE *file;
    int capacity  = 4;
    int num_lines = 0;
    int *left_list;
    int *right_list;
    int *temp_left;
    int *temp_right;
    int total_distance = 0;
    int total_similarity = 0;
    int occurrence_count;
    int i, j;
    int ret = 0;

    // Open the input file in read mode ("r")
    // The file must exist and contain lines with 2 integers per line
    file = fopen("./numberlist.txt", "r");
    if (!file) {  // If the file could not be opened
        perror("Error opening file");
        ret = 1;
        goto exit_0;
    }

    // Allocate initial memory for the two lists
    left_list  = malloc(capacity * sizeof(int));
    right_list = malloc(capacity * sizeof(int));

    if (!left_list || !right_list) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        ret = 1;
        goto exit_0;
    }

    // Read pairs of integers from the file
    // fscanf returns the number of successfully read items
    // If it returns 2, both integers were read; otherwise, we stop (EOF or error)
    while (fscanf(file, "%d %d", &left_list[num_lines], &right_list[num_lines]) == 2) {

        num_lines++;  // Count this line

        // If we reached the current capacity, double the size of the arrays
        if (num_lines == capacity) {
            capacity *= 2;  // double the capacity

            temp_left  = realloc(left_list,  capacity * sizeof(int));
            temp_right = realloc(right_list, capacity * sizeof(int));

            if (!temp_left || !temp_right) {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(file);
                ret = 1;
                goto exit_1;
            }

            left_list  = temp_left;
            right_list = temp_right;
        }
    }

    // We are done reading from the file
    fclose(file);

    // Sort both lists in ascending order
    qsort(left_list,  num_lines, sizeof(int), cmp_int);
    qsort(right_list, num_lines, sizeof(int), cmp_int);

    // ---- Part 1: Distance ----
    // Compute the total distance as the sum of absolute differences

    for (i = 0; i < num_lines; i++) {
        total_distance += abs(left_list[i] - right_list[i]);
    }
    
    printf("%d - Distance\n", total_distance);

    // ---- Part 2: Similarity ----
    // For each value in left_list, count how many times it appears in right_list,
    // then add value * count to the total similarity.

    for (i = 0; i < num_lines; i++) {
        occurrence_count = 0;

        for (j = 0; j < num_lines; j++) {
            if (left_list[i] == right_list[j]) {
                occurrence_count++;
            } else if (left_list[i] < right_list[j]) {
                // Since right_list is sorted, we can stop early:
                // once right_list[j] is greater than left_list[i],
                // there will be no more matches.
                break;
            }
        }

        total_similarity += occurrence_count * left_list[i];
    }
    
    printf("%d - Similarity\n", total_similarity);

    // Free dynamically allocated memory
    exit_1:
        free(left_list);
        free(right_list);
    exit_0:
        return ret;
    
}