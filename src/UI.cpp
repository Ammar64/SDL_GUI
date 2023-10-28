#include "UI.h"
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_oldnames.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <string>
SDL_Cursor *UIElement::pointer;
SDL_Cursor *UIElement::arrow;
SDL_Cursor *UIElement::text;
std::vector<UIElement *> UIElement::elements;

UIElement::UIElement(const char *json_path){
  try {
    this->data = json::parse( Core::get_file_content(json_path) );
  }catch(json::parse_error &e) {
    SDL_Log("ERROR: PARSE ERROR. NLOHMANN_JSON_ERROR: %s", e.what());
  }
  define_procedures();
  UIElement::elements.push_back(this);
}
void UIElement::setup() {
  pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
  arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  text = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
}

void UIElement::cleanup() {
  SDL_DestroyCursor(pointer);
  SDL_DestroyCursor(arrow);
  SDL_DestroyCursor(text);

}
void UIElement::render() { SDL_RenderTexture(renderer, texture, NULL, &dst); }

void UIElement::present() { this->behave(); }

UIElement::~UIElement() {
  if (surface != NULL) SDL_DestroySurface(surface);
  if( normal_texture != NULL ) SDL_DestroyTexture(normal_texture);
  if( hover_texture != NULL ) SDL_DestroyTexture(hover_texture);
  if( pressed_texture != NULL ) SDL_DestroyTexture(pressed_texture);
}

template<typename T>
T UIElement::get_property(const char *state, const char* key) {
  if( data[state].contains(key) ) {
    return data[state][key].get<T>();
  }
  return UNDEFINED;
}

void UIElement::define_procedures() {
  procedures.insert({XPOS,[&](std::string v) mutable -> void {

  }});
}