#include "Core.h"
#include "Text.h"
#include "UI.h"

int Core::present(void *data) {
  while (running) {
    pollEvents();
    for (UIElement *&i : UIElement::elements) {
      i->present();
    }
  }
  return 0;
}

int Core::render(void *data) {
  
  while (running) {
    appWindow->clear();
    for (UIElement *&i : UIElement::elements) {
      i->render();
    }
    appWindow->display();
  }
  return 0;
}