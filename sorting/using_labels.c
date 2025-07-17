#include <stdio.h>

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 0, j;

first_index:
    if (i < n - 1) {
        j = i + 1;

second_index:
        if (j < n) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j++;
            goto second_index;
        }

        i++;
        goto first_index;
    }

    // Print sorted array
    printf("Sorted array: ");
    for (int k = 0; k < n; k++)
        printf("%d ", arr[k]);

    return 0;
}
