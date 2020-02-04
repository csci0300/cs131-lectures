#include <stdio.h>

struct list_node_t {
  int v;
  struct list_node* next;
};

struct list_t {
  struct list_node* head;
};

int main() {
  printf("sizeof(list_node_t): %lu\n", sizeof(struct list_node_t));
  printf("sizeof(list_t): %lu\n", sizeof(struct list_t));
}
