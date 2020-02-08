#include <stdlib.h>
#include <stdio.h>

// you can also use typedef to create aliases for primitive types like int!
typedef int my_cool_int_t;

struct list_node {
  my_cool_int_t value;
  struct list_node* next;
};

// below is synonymous with wrapping the struct definition in a typedef:
// typedef struct list_node {
//   int value;
//   struct list_node* next;
// } list_node_t;
typedef struct list_node list_node_t;

typedef struct list {
  list_node_t* head;
} list_t;

int main() {
  int* ptr = (int*)malloc(sizeof(int) * 10);
  *(ptr + 0) = 1;
  *(ptr + 1) = 2;
  *(ptr + 2) = 3;

  // by pointer arithmetic, this is equivalent to:
  // int* ptr2 = &(*(ptr + 2));
  // or indeed
  // int* ptr2 = &(*((char*)ptr + sizeof(int) * 2))
  // it's just a lot easier to read!
  int* ptr2 = &ptr[2];

  printf("ptr: %p\n", ptr);
  // prints an address 8 bytes beyond `ptr`
  printf("ptr2: %p\n", ptr2);


  list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
  node->value = 123;

  // these are all different ways of accessing the "value" member of a
  // list_node_t. They struct return the same address and value.
  printf("%p: %d\n", &(node->value), node->value);
  printf("%p: %d\n", &((*node).value), (*node).value);
  // casting `node` to char* so that we can do pointer arithmetic in units of 1 byte
  printf("%p: %d\n", ((char*)node + 0), *((char*)node + 0));

  // these are all different ways of accessing the "next" member and
  // return the same address and value.
  printf("%p: %d\n", &(node->next), node->value);
  printf("%p: %d\n", &((*node).next), (*node).value);
  // byte offset is 8 due to alignment constraints on pointers!
  printf("%p: %d\n", ((char*)node + 8), *((char*)node + 8));

  free(ptr);
  free(node);
}
