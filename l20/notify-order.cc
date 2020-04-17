#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <thread>
#include <condition_variable>

#define NUM_THREADS 10

int last_printed;
std::mutex m;
std::condition_variable is_it_my_turn_cv;

void print_threadfunc(int my_number) {
  std::unique_lock<std::mutex> guard(m);

  // ok to read shared state in condition as we hold the
  // lock on m
  while (last_printed != my_number - 1) {
    printf("%d woke, but its turn hasn't come yet\n", my_number);
    is_it_my_turn_cv.wait(guard);
  }

  printf("%d\n", my_number);

  // ok to access shared state here, since we hold the lock
  // on m
  last_printed = my_number;

  // wake up the next thread -- need to wake up all, since
  // we cannot specifically wake the thread who prints the
  // next number!
  is_it_my_turn_cv.notify_all();
  // if you replace this line with notify_one(), the program
  // will sometimes get stuck! Uncomment this line to try.
  //is_it_my_turn_cv.notify_one();
}

int main() {
  std::thread th[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    th[i] = std::thread(print_threadfunc, i + 1);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    th[i].join();
  }
}
