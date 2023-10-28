#ifndef TEXT_H
#define TEXT_H
#include "UI.h"
#include <SDL3_ttf/SDL_ttf.h>

// width and height
#define FIT -1000000

class Text : public UIElement {
public:
  Text(const char *json_path);
  ~Text();
  void changeText(const char *text);

private:
  void updatePosition() override;
  void renderTexts();
  const char *text;
  TTF_Font *font;
  bool wFit, hFit;
  void writeToTexFromSur(SDL_Texture **dst, SDL_Surface *src);
};

#endif