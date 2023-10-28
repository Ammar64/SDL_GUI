#include "Thread.h"


Thread::Thread( SDL_ThreadFunction fn, const char *name, void *data ) {
    this->fn = fn;
    this->name = name;
    this->data = data;
}

void Thread::start() {
    thread = SDL_CreateThread( this->fn, this->name, this->data );
}

void Thread::detach() {
    SDL_DetachThread( thread );
}

int Thread::wait() {
    int status;
    SDL_WaitThread( thread, &status );
    return status;
}
