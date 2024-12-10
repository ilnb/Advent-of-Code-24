#include <stdio.h>
#include <stdlib.h>
#define LEN 1000

typedef struct data {
  int *num1;
  int *num2;
} data;

void selsort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    int t = arr[min];
    arr[min] = arr[i];
    arr[i] = t;
  }
}

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  data data;
  data.num1 = NULL;
  data.num2 = NULL;
  for (int i = 0; i < LEN; i++) {
    data.num1 = realloc(data.num1, sizeof(int) * (i + 1));
    data.num2 = realloc(data.num2, sizeof(int) * (i + 1));
    fscanf(fp, "%d   %d\n", data.num1 + i, data.num2 + i);
  }
  selsort(data.num1, LEN);
  selsort(data.num2, LEN);
  int dis = 0;
  for (int i = 0; i < LEN; i++) {
    int n = data.num1[i] - data.num2[i];
    if (n < 0) {
      dis += -n;
    } else {
      dis += n;
    }
  }
  int sim = 0;
  for (int i = 0; i < LEN; i++) {
    int count = 0;
    for (int j = 0; j < LEN; j++) {
      if (data.num1[i] == data.num2[j]) {
        count++;
      }
    }
    sim += data.num1[i] * count;
  }
  printf("Distance: %d\nSimilarity score: %d\n", dis, sim);
  free(data.num1);
  free(data.num2);
  free(fp);
  return 0;
}
