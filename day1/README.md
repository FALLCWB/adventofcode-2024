# 📘 Advent of Code 2024 --- Day 1

This folder contains my solution for **Day 1** of **Advent of Code
2024**, implemented in **C**.

## 🧩 Problem Summary

The input file contains two columns of integers:

    85215 94333
    24582 34558
    98037 94333
    ...

Each line represents a pair of related values.

The program loads the entire file dynamically, splitting the numbers
into two separate lists:

-   **Left list**
-   **Right list**

Both lists are then sorted in ascending order.

## 🧮 Part 1 --- Total Distance

For each index **i**, compute:

    abs(left[i] - right[i])

The final answer is the sum of all these absolute differences.

## 🔍 Part 2 --- Similarity Score

For each value in the left list:

1.  Count how many times the same value appears in the right list\
2.  Multiply the value by its number of occurrences\
3.  Add the result to the total similarity score

There are two implementations for this solution, the first (day1_doublefor.c) uses an **double loop**, the second (day1_binsearch.c) uses an **optimized binary search approach** to
efficiently count how many time a value on the left_list appears on the right_list.

## 🚀 Build & Run

Compile with:

``` bash
gcc -std=gnu11 -Wall -Werror -Wpedantic -o day1_binsearch day1_binsearch.c
gcc -std=gnu11 -Wall -Werror -Wpedantic -o day1_doublefor day1_doublefor.c
```

Run:

``` bash
./day1_binsearch
./day1_doublefor
```

Make sure the input file `numberlist.txt` is in the same directory.

## 🧪 Performance Notes

Two implementations were benchmarked:

-   **O(n²)** version using a naive nested loop\
-   **O(n log n)** version using binary search + forward scanning

### 1000 executions benchmark:

    Binary Search Version:   ~0.789 seconds
    Double For Version:      ~0.941 seconds

✔ The optimized version is approximately **19% faster**, even for small
Advent of Code inputs.

## 📁 Folder Structure

    day1/
     ├── day1_binsearch.c
     ├── day1_doublefor.c
     ├── numberlist.txt
     └── README.md

## 👤 Author

**Filipe Augusto da Luz Lemos (FALLCWB)**\
MSc, PhD

### Reviewers

-   **Bruno Meneguele (bmeneg)**
