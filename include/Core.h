#ifndef CORE_H
#define CORE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <functional>
#include "Window.h"
#include <string>
class Core {
  public:
    static void run();
    static void pollEvents();
    static volatile bool running;
    static void addEventReaction( std::function<void(SDL_Event&)> fn );
    static std::string get_file_content(const char *path);
    static Window *appWindow;
    template<typename T>
    static bool isNumber(T &str);
  private:
    static void setup();
    static void initSDL();
    static void cleanup();
    static SDL_Event event;
    static int present( void *data ); // it must return int and take void *data to be compatible with SDL_Thread.
    static int render(void *data); // just to make it look clean it will return int and take void* data even though it will run on the main thread.
    static std::vector< std::function<void(SDL_Event&)> > event_reactions;
    
};

#endif