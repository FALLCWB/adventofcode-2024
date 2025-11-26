#include <stdio.h>
#include <stdlib.h>

// Comparison function used by qsort to sort integers in ascending order
int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;  // negative if x < y, positive if x > y, zero if equal
}

int main() {
    // Open the input file in read mode ("r")
    // The file must exist and contain lines with 2 integers per line
    FILE *file = fopen("./numberlist.txt", "r");
    if (!file) {  // If the file could not be opened
        perror("Error opening file");
        return 1;
    }

    int capacity  = 4;  // Initial capacity of the arrays (will grow dynamically)
    int num_lines = 0;  // Number of lines read so far

    // Allocate initial memory for the two lists
    int *left_list  = malloc(capacity * sizeof(int));
    int *right_list = malloc(capacity * sizeof(int));

    if (!left_list || !right_list) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        free(left_list);
        free(right_list);
        return 1;
    }

    // Read pairs of integers from the file
    // fscanf returns the number of successfully read items
    // If it returns 2, both integers were read; otherwise, we stop (EOF or error)
    while (fscanf(file, "%d %d", &left_list[num_lines], &right_list[num_lines]) == 2) {

        num_lines++;  // Count this line

        // If we reached the current capacity, double the size of the arrays
        if (num_lines == capacity) {
            capacity *= 2;  // double the capacity

            int *temp_left  = realloc(left_list,  capacity * sizeof(int));
            int *temp_right = realloc(right_list, capacity * sizeof(int));

            if (!temp_left || !temp_right) {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(file);
                free(left_list);
                free(right_list);
                return 1;
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
    int total_distance = 0;

    for (int i = 0; i < num_lines; i++) {
        total_distance += abs(left_list[i] - right_list[i]);
    }
    
    printf("%d - Distance\n", total_distance);

    // ---- Part 2: Similarity ----
    // For each value in left_list, count how many times it appears in right_list,
    // then add value * count to the total similarity.
    int total_similarity = 0;

    for (int i = 0; i < num_lines; i++) {
        int occurrence_count = 0;

        for (int j = 0; j < num_lines; j++) {
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
    free(left_list);
    free(right_list);

    return 0;
}