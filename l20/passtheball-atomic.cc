#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <thread>
#include <algorithm>
#include <unistd.h>
#include <atomic>

#define NUM_PLAYERS 3

struct Player {
  unsigned int id;
  std::atomic<bool> has_ball;
  Player* prev;
  Player* next;

  void pass(Player* target);
};

void Player::pass(Player* target) {
  printf("P%u tries to pass the ball to P%u ...\n", this->id, target->id);
  target->has_ball = true;
  this->has_ball = false;
  printf("... P%u caught!\n", target->id);
}

void player_threadfunc(Player* me) {
  printf("P%u joins the game!\n", me->id);
  while (true) {
    if (me->has_ball.load()) {
      me->pass(me->next);
    }
  }
}

int main() {
    Player p[NUM_PLAYERS];
    std::thread* pth[NUM_PLAYERS];

    for (unsigned int i = 0; i < NUM_PLAYERS; i++) {
      if (i == 0) {
        p[i].has_ball = true;
      }
      p[i].id = i;
      p[i].next = &p[(i + 1) % NUM_PLAYERS];
      p[i].prev = &p[(i - 1) % NUM_PLAYERS];
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
      pth[i] = new std::thread(player_threadfunc, &p[i]);
    }

    for (int i = 0; i < NUM_PLAYERS; i++) {
      pth[i]->join();
      delete pth[i];
    }
}
