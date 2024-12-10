#include <stdio.h>
#include <stdlib.h>
#define RULES 21
#define UPDATES 6

typedef struct rule {
  int main;
  int sub;
} rule;

typedef struct update {
  int *pages;
  int count;
} update;

int main(void) {
  rule *rules = malloc(RULES * sizeof(rule));
  update *updates = malloc(UPDATES * sizeof(update));
  FILE *fp = fopen("sample.txt", "r");
  for (int i = 0; i < RULES; i++) {
    fscanf(fp, "%d|%d\n", &rules[i].main, &rules[i].sub);
  }
  for (int i = 0; i < UPDATES; i++) {
    int count = 0, offset = 0;
    char c;
    while ((c = fgetc(fp)) != '\n') {
      if (c == ',') {
        count++;
      }
      offset++;
    }
    count++, offset++;
    updates[i].pages = malloc(sizeof(int) * count);
    fseek(fp, -offset, SEEK_CUR);
    for (int j = 0; j < count - 1; j++) {
      fscanf(fp, "%d,", &updates[i].pages[j]);
    }
    fscanf(fp, "%d\n", &updates[i].pages[count - 1]);
    updates[i].count = count;
  }

  return 0;
}
