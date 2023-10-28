#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <functional>

class Window {
  public:
    Window(const char *title, int w, int h, Uint32 flags);
    Window(const char *title, Uint32 flags); // for mobile
    ~Window();

    SDL_Window *getWidnow();
    SDL_Renderer *getRenderer();
    SDL_GLContext getContext();
    int getWidth();
    int getHeight();
    SDL_WindowID getID();
    void setClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    std::function<void()> clear;
    std::function<void()> display;

  private:
    
    void _make_window( const char* title, int w, int h, Uint32 flags );
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;
    int w,h;
    SDL_WindowID id;
    Uint8 rgba[4];
};

#endif