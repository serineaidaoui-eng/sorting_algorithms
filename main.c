#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNS 5

// Exchange two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 1. Bubble Sort
void bubbleSort(int a[], int n) {
    int i, j, swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;

        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }
}

// 2. Selection Sort
void selectionSort(int a[], int n) {
    int i, j, min;

    for (i = 0; i < n - 1; i++) {
        min = i;

        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
        }

        swap(&a[i], &a[min]);
    }
}

// 3. Insertion Sort
void insertionSort(int a[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Merge function
void merge(int a[], int left, int mid, int right) {
    int i, j, k;
    int size = right - left + 1;

    int *temp = malloc(size * sizeof(int));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    i = left;
    j = mid + 1;
    k = 0;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = 0; i < size; i++)
        a[left + i] = temp[i];

    free(temp);
}

// 4. Merge Sort
void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

// Partition function
// Pivot = last element
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

// 5. Quick Sort
void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

// Copy array
void copyArray(int source[], int destination[], int n) {
    int i;

    for (i = 0; i < n; i++)
        destination[i] = source[i];
}

// Generate random numbers
void generateArray(int a[], int n) {
    int i;

    for (i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

// Print array
void printArray(int a[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

// Run one sorting algorithm
void runSort(int a[], int n, int choice) {
    if (choice == 1)
        bubbleSort(a, n);
    else if (choice == 2)
        selectionSort(a, n);
    else if (choice == 3)
        insertionSort(a, n);
    else if (choice == 4)
        mergeSort(a, 0, n - 1);
    else if (choice == 5)
        quickSort(a, 0, n - 1);
}

// Get algorithm name
char* getName(int choice) {
    if (choice == 1) return "Bubble Sort";
    if (choice == 2) return "Selection Sort";
    if (choice == 3) return "Insertion Sort";
    if (choice == 4) return "Merge Sort";
    return "Quick Sort";
}

// Measure average execution time
double measureTime(int original[], int n, int choice) {
    int *array;
    int i;
    clock_t start, end;
    double totalTime = 0;

    array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < RUNS; i++) {
        // Copy before starting the timer
        copyArray(original, array, n);

        start = clock();

        runSort(array, n, choice);

        end = clock();
        totalTime += (double)(end - start) / CLOCKS_PER_SEC;
    }

    free(array);

    return totalTime / RUNS;
}

// Compare all algorithms
void compareSorts(int original[], int n) {
    int i;
    double averageTime;

    printf("\n===== COMPARISON =====\n");
    printf("Array size: %d\n", n);
    printf("Number of runs: %d\n\n", RUNS);

    for (i = 1; i <= 5; i++) {
        averageTime = measureTime(original, n, i);

        printf("%s: %f seconds\n",
               getName(i), averageTime);
    }
}

// Main function
int main() {
    int choice, n;
    int *original;
    int *array;

    // Fixed random seed
    srand(42);

    do {
        printf("\n===== SORTING ALGORITHMS =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Compare all algorithms\n");
        printf("7. Large array test (100000)\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

        if (choice == 0) {
            printf("Goodbye!\n");
            break;
        }

        if (choice < 1 || choice > 7) {
            printf("Invalid choice!\n");
            continue;
        }

        if (choice == 7)
            n = 100000;
        else {
            printf("Enter array size: ");

            if (scanf("%d", &n) != 1 || n <= 0) {
                printf("Invalid size!\n");
                return 1;
            }
        }

        original = malloc(n * sizeof(int));

        if (original == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        generateArray(original, n);

        if (choice == 6) {
            compareSorts(original, n);
        }
        else if (choice == 7) {
            // Large array: use Merge and Quick Sort
            array = malloc(n * sizeof(int));

            if (array == NULL) {
                printf("Memory allocation failed!\n");
                free(original);
                return 1;
            }

            copyArray(original, array, n);

            printf("\nLarge array test:\n");

            printf("Merge Sort time: %f seconds\n",
                   measureTime(original, n, 4));

            printf("Quick Sort time: %f seconds\n",
                   measureTime(original, n, 5));

            free(array);
        }
        else {
            array = malloc(n * sizeof(int));

            if (array == NULL) {
                printf("Memory allocation failed!\n");
                free(original);
                return 1;
            }

            copyArray(original, array, n);

            printf("\nOriginal array:\n");

            if (n <= 30)
                printArray(original, n);

            printf("\nSorting using %s...\n", getName(choice));

            printf("Average execution time: %f seconds\n",
                   measureTime(original, n, choice));

            runSort(array, n, choice);

            printf("\nSorted array:\n");

            if (n <= 30)
                printArray(array, n);

            free(array);
        }

        free(original);

    } while (choice != 0);

    return 0;
}