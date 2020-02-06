typedef struct list_node_t {
  int v;
  struct list_node_t* next;
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
  new_node->v = value;

  if (cur != NULL) {
    cur->next = new_node;
  } else {
    list->head = new_node;
  }
}


int main() {
  hexdump(l->head, sizeof(list_node_t));
  hexdump(l->head->next, sizeof(list_node_t));
  hexdump(l->head->next->next, sizeof(list_node_t));

  printf("sizeof(list_node_t): %lu\n", sizeof(list_node_t));
  printf("sizeof(list_t): %lu\n", sizeof(list_t));
}
