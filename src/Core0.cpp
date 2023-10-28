#include "Core.h"
#include "Thread.h"
#include <SDL_error.h>
#include <SDL_rwops.h>
#include <cstdlib>
#include "UI.h"
SDL_Event Core::event;
volatile bool Core::running;
std::vector<std::function<void(SDL_Event &)>> Core::event_reactions;
Window *Core::appWindow;

void Core::setup() {
    running = true;
    appWindow = new Window( "GUI", 800, 600, SDL_WINDOW_RESIZABLE );
    UIElement::setup();
    addEventReaction([&](SDL_Event &event) mutable -> void {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        }
    }); // add the main event reaction to terminate the app when needed
    appWindow->setClearColor(0x11, 0x11, 0x11, 255);
}

void Core::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init() failed. SDL_ERROR: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init() failed. SDL_ERROR: %s", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init() failed. SDL_ERROR: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Mix_Init() failed. SDL_ERROR: %s", Mix_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_LogVerbose(SDL_LOG_CATEGORY_SYSTEM, "ALL SDL LIBRARIES HAS BEEN INITIALIZED.");
}

void Core::cleanup() {
    UIElement::cleanup();
    delete appWindow;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Core::run() {
    initSDL();
    setup();
    Thread thread0 = Thread(present, "Present_thread", NULL);
    thread0.start();

    render(NULL);

    thread0.wait();
    cleanup();
}

void Core::pollEvents() {
    while (SDL_PollEvent(&event)) {
        for (std::function<void(SDL_Event &)> &i : event_reactions) {
            i(event);
        }
    }
}

void Core::addEventReaction(std::function<void(SDL_Event &)> fn) { event_reactions.push_back(fn); }

std::string Core::get_file_content(const char *path) {
    std::string content;
    SDL_RWops *file = SDL_RWFromFile(path, "r");
    if( file == NULL ) {
        SDL_Log( "ERROR: file is NULL. SDL_ERROR: %s", SDL_GetError() );
    }
    Sint64 size = SDL_RWsize(file);
    if( size < 0 ) {
        SDL_Log("file size is less than 0. SDL_ERROR: %s", SDL_GetError());
    }
    content.resize(size);
    SDL_RWread( file, &content[0], size );
    SDL_RWclose(file);
    return content;
}

template <typename T>
bool Core::isNumber(T &str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num; // Attempt to read a double without skipping white spaces
    // Check if the entire string was consumed and the operation was successful
    return !iss.fail() && iss.eof();
}