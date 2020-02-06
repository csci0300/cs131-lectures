#include <stdio.h>
#include <stdlib.h>
#include "hexdump.h"

typedef struct {
} list_t;

void append(list_t* l, int v) {
}

int main() {
  list_t* l = malloc(sizeof(list_t));

  for (int i = 0; i < 100; i++) {
    append(l, i);
  }

  hexdump(l, sizeof(list_t));

  free(l);
}
