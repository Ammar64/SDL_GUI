#include "Text.h"
#include "UI.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstddef>
#include <utility>

Text::Text(const char *json_path) : UIElement(json_path) {

}

void Text::renderTexts() {
  SDL_Color tmp = SDL_Color{0, 0, 0, 0};
  if (SDL_memcmp((void *)&colors[BACKGROUND][NORMAL], (void *)&tmp,
                 sizeof(SDL_Color)) ==
      0) // If back ground color == {0,0,0,0} don't add a background color
  {

    writeToTexFromSur(
        &normal_texture,
        TTF_RenderText_Blended(font, this->text, colors[FOREGROUND][NORMAL]));

    writeToTexFromSur(
        &hover_texture,
        TTF_RenderText_Blended(font, this->text, colors[FOREGROUND][HOVER]));

    writeToTexFromSur(
        &pressed_texture,
        TTF_RenderText_Blended(font, this->text, colors[FOREGROUND][PRESSED]));
  } else {
    writeToTexFromSur(&normal_texture,
                      TTF_RenderText_LCD(font, this->text,
                                         colors[FOREGROUND][NORMAL],
                                         colors[BACKGROUND][NORMAL]));

    writeToTexFromSur(&hover_texture,
                      TTF_RenderText_LCD(font, this->text,
                                         colors[FOREGROUND][HOVER],
                                         colors[BACKGROUND][HOVER]));

    writeToTexFromSur(&pressed_texture,
                      TTF_RenderText_LCD(font, this->text,
                                         colors[FOREGROUND][PRESSED],
                                         colors[BACKGROUND][PRESSED]));
  }
}

void Text::updatePosition() {
  int wh, hh; // wh: width handler. hh: height handler
  TTF_SizeText(font, this->text, &wh, &hh);
  if (wFit)
    this->dst.w = wh;
  if (hFit)
    this->dst.h = hh;
  UIElement::updatePosition(); // overriden function
}

void Text::changeText(const char *text) {
  this->text = text;
  updatePosition();
  renderTexts();
  texture = normal_texture;
}

void Text::writeToTexFromSur(SDL_Texture **dst, SDL_Surface *src) {
  *dst = SDL_CreateTextureFromSurface(this->renderer, src);
  SDL_DestroySurface(src);
}

Text::~Text() { TTF_CloseFont(font); }