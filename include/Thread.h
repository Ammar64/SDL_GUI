#pragma once
#include <SDL3/SDL_thread.h>

class Thread {
  public:
    Thread(SDL_ThreadFunction fn, const char *name, void *data);
    void start();
    void detach();
    int wait();

  private:
    SDL_Thread *thread;
    const char *name;
    void *data;
    SDL_ThreadFunction fn;
};
