#include <stdio.h>
#include <stdlib.h>
#include "hexdump.h"

typedef struct list_node {
  int value;
  struct list_node* next;
} list_node_t;

typedef struct {
  list_node_t* head;
} list_t;

void append(list_t* list, int value) {
  list_node_t* cur = list->head;

  if (cur != NULL) {
    while (cur->next != NULL) {
      cur = cur->next;
    }
  }

  list_node_t* new_node = (list_node_t*)malloc(sizeof(list_node_t));
  new_node->next = NULL;
  new_node->value = value;

  if (cur != NULL) {
    cur->next = new_node;
  } else {
    list->head = new_node;
  }
}

int main() {
  list_t* l = (list_t*)malloc(sizeof(list_t));
  l->head = NULL;

  for (int i = 0; i < 100; i++) {
    append(l, i);
  }

  hexdump(l, sizeof(list_t));
  hexdump(l->head, sizeof(list_node_t));
  hexdump(l->head->next->next->next->next, sizeof(list_node_t));

  printf("sizeof(list_node_t): %lu\n", sizeof(list_node_t));

  free(l);
}
