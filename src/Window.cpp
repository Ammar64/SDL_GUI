#include "Window.h"
#include "Core.h"
#include <SDL3/SDL_log.h>
#include <SDL_render.h>
Window::Window(const char *title, int w, int h, Uint32 flags)
    : window(nullptr), renderer(nullptr) {
  _make_window(title, w, h, flags);
}

Window::Window(const char *title, Uint32 flags) {
  SDL_DisplayID *id = SDL_GetDisplays(NULL);
  const SDL_DisplayMode *DM = SDL_GetCurrentDisplayMode(id[0]);
  SDL_free(id);
  _make_window(title, DM->w, DM->h, flags);
}

void Window::_make_window(const char *title, int w, int h, Uint32 flags) {
  window = SDL_CreateWindow(title, w, h, flags);
  if (window == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "WINDOW IS NULL. SDL_ERROR: %s",
                 SDL_GetError());
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(
      window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "WINDOW IS NULL. SDL_ERROR: %s",
                 SDL_GetError());
    exit(EXIT_FAILURE);
  }
  id = SDL_GetWindowID(window);
  this->w = w;
  this->h = h;
  rgba[0] = 0;
  rgba[1] = 0;
  rgba[2] = 0;
  rgba[3] = 0;

  if (flags & SDL_WINDOW_OPENGL) {

  } else {
    clear = [&]() mutable -> void { SDL_RenderClear(renderer); };
    display = [&]() mutable -> void {
      SDL_SetRenderDrawColor(renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
      SDL_RenderPresent(renderer);
    };
  }
  Core::addEventReaction([&](SDL_Event &event) mutable -> void {
    switch (event.type) {
    case SDL_EVENT_WINDOW_RESIZED:
      if (event.window.windowID == this->id) {
        SDL_GetWindowSize(this->window, &this->w, &this->h);
      }
      break;

    default:
      break;
    }
  });
}

void Window::setClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  rgba[0] = r;
  rgba[1] = g;
  rgba[2] = b;
  rgba[3] = a;
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

SDL_Window *Window::getWidnow() { return window; }
SDL_Renderer *Window::getRenderer() { return renderer; }
SDL_GLContext Window::getContext() { return context; }
int Window::getWidth() { return this->w; }
int Window::getHeight() { return this->h; }
SDL_WindowID Window::getID() { return this->id; }