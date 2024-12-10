#include <stdio.h>
#include <stdlib.h>
#define LEN 1000

int safetyCheckPtr(int *arr, int n, int *index) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!arr[i]) {
        *index = i;
        return 0;
      } else if (arr[i] > 0) {
        if (arr[j] < 0 || arr[j] > 3) {
          *index = j;
          return 0;
        }
      } else {
        if (arr[j] > 0 || arr[j] < -3) {
          *index = j;
          return 0;
        }
      }
    }
  }
  return 1;
}

int safetyCheck(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!arr[i]) {
        return 0;
      } else if (arr[i] > 0) {
        if (arr[j] < 0 || arr[j] > 3) {
          return 0;
        }
      } else {
        if (arr[j] > 0 || arr[j] < -3) {
          return 0;
        }
      }
    }
  }
  return 1;
}

void elRemove(int *arr, int n, int index) {
  int *b = malloc(sizeof(int) * (n - 1));
  for (int i = 0; i < index; i++) {
    b[i] = arr[i];
  }
  for (int i = index; i < n - 1; i++) {
    b[i] = arr[i + 1];
  }
  for (int i = 0; i < n - 1; i++) {
    arr[i] = b[i];
  }
  free(b);
}

int main() {
  FILE *fp = fopen("input.txt", "r");
  int safe = 0, allowed = 0;
  for (int i = 0; i < LEN; i++) {
    int n = 0, p = 0;
    char c;
    while ((c = fgetc(fp)) != '\n') {
      if (c == ' ') {
        n++;
      }
      p++;
    }
    n++, p++;
    fseek(fp, -p, SEEK_CUR);
    int *arr = malloc(sizeof(int) * n), l;
    for (int k = 0; k < n - 1; k++) {
      l = 0;
      while ((c = fgetc(fp)) != ' ') {
        l += (c - 48);
        l *= 10;
      }
      arr[k] = l / 10;
    }
    l = 0;
    while ((c = fgetc(fp)) != '\n') {
      l += (c - 48);
      l *= 10;
    }
    arr[n - 1] = l / 10;
    int *temp = malloc(sizeof(int) * n);
    for (int j = 0; j < n; j++) {
      temp[j] = arr[j];
    }
    int *diff = malloc(sizeof(int) * (n - 1));
    for (int j = 0; j < n - 1; j++) {
      diff[j] = arr[j + 1] - arr[j];
    }
    int index;
    l = safetyCheckPtr(diff, n - 1, &index);
    if (l == 1) {
      safe++;
    } else {
      elRemove(arr, n, index);
      for (int j = 0; j < n - 2; j++) {
        diff[j] = arr[j + 1] - arr[j];
      }
      l = safetyCheck(diff, n - 2);
      if (l == 1) {
        allowed++;
      } else {
        for (int j = 0; j < n; j++) {
          arr[j] = temp[j];
        }
        elRemove(arr, n, index + 1);
        for (int j = 0; j < n - 2; j++) {
          diff[j] = arr[j + 1] - arr[j];
        }
        l = safetyCheck(diff, n - 2);
        if (l == 1) {
          allowed++;
        } else if (index > 0) {
          for (int j = 0; j < n; j++) {
            arr[j] = temp[j];
          }
          elRemove(arr, n, index - 1);
          for (int j = 0; j < n - 2; j++) {
            diff[j] = arr[j + 1] - arr[j];
          }
          l = safetyCheck(diff, n - 2);
          if (l == 1) {
            allowed++;
          }
        }
      }
    }
    free(arr);
    free(diff);
  }
  printf("safe: %d\nallowed: %d\ntotal: %d\n", safe, allowed, safe + allowed);
  fclose(fp);
  return 0;
}
