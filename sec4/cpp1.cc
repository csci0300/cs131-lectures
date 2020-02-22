#include <stdio.h>

// typedef to demonstrate that it works for C++ classes too
typedef class Animal {
 public:
   int weight_;

 private:
  char* name_;
  int age_;

 public:
  // constructor; automatically gets invoked when making a new instance
  // after memory has been set aside for it
  Animal(char* name, int age) : name_(name), age_(age) {
  }

  void setName(char* new_name) {
    this->name_ = new_name;
  }

  char* getName() {
    return this->name_;
  }
} animal_t;

int main() {
  // we're in C++, but can still do C-style I/O
  printf("hello world!\n");

  // makes a new stack-allocated instance of class Animal
  Animal stack_a("kitty", 1);

  // makes a new heap-allocated instance of class Animal
  Animal* heap_a = new Animal("bob", 5);
  heap_a->setName("bob");

  // works, because weight_ is a public member
  heap_a->weight_ = 10;

  // need to use getName() because name_ is a private member
  printf("name: %s\n", heap_a->getName());
}
