#ifndef UI_H
#define UI_H
#include <SDL3/SDL.h>
#include <functional>
#include "Core.h"
#include <map>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "UI_keys.h"

using json = nlohmann::json;
#define UNDEFINED "undefined"

class UIElement {
public:
  UIElement(const char *json_path);
  virtual ~UIElement();
  virtual void present();
  virtual void render();
  static std::vector<UIElement*> elements;
  static void setup();
  static void cleanup();
  void define_procedures();
protected:
  json data;
  std::map<const char *, std::function<void(std::string)>> procedures;
  SDL_Surface *surface;
  static SDL_Cursor *pointer;
  static SDL_Cursor *arrow;
  static SDL_Cursor *text;

  
  std::vector<std::vector<SDL_Color>> colors;
  virtual void updatePosition();
  template<typename T>
  T get_property(const char *state,const char *key);
  std::function<void()> behave;
  std::function<void()> on_mousein;
  std::function<void()> on_mouseout;
  std::function<void()> on_left_click;
  std::function<void()> on_right_click;
  SDL_Texture *texture;
  SDL_Texture *normal_texture;
  SDL_Texture *hover_texture;
  SDL_Texture *pressed_texture;
  SDL_Renderer *renderer;
  SDL_FRect dst;
  bool mouse_was_in;
  Uint8 Xunit, Yunit;
  int Xpercent,Ypercent;
  int x,y;
  Uint8 hover_cursor;
  Uint8 Xinvert, Yinvert;
};
#endif