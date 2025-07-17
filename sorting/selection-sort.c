#include <stdio.h>

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

   for (int i = 0 ; i<n ; i++){
      
      int key = arr[i];
      for (int j =  i + 1 ; j < n ; j++){
          if(arr[j] < key ){
              int key = arr[i];
              arr[i] = arr[j];
             arr[j] = key;
              
          }
          else{continue;}
      }
        
   }

    // Print sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
