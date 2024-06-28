#include <SDL2/SDL.h>
#include <iostream>

// This program opens a joystick and tells you
// when a button is pressed or an axis is moved.
// This demsontrates how to read from the joystick
// using an event-based system. In another example
// I will show how to poll the state of each button.
int main(int argc, char **argv) { 
    // Initialize the joystick subsystem for SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
    // int joysticks = SDL_Init(SDL_INIT_JOYSTICK);

    // Check how many joysticks are connected.
    int joysticks = SDL_NumJoysticks();
    printf("There are %d joysticks connected.\n", joysticks);

    auto a = SDL_GameControllerOpen(0 );
            

    int quit = 0;
    SDL_Event event;

    // An infinite loop that keeps going until we set
    // the quit variable to a non-zero value. We
    // put this loop so that we can keep on listening to
    // the joystick until we are done with it.
    while (!quit) {
        // The event variable stores a list of events.
        // The inner loop keeps reading the events
        // one-by-one until there are no events left
        // to read. SDL_PollEvent(&event) just checks
        // if any new events have happend, and stores them
        // inside of the event variable.
        while (SDL_PollEvent(&event) != 0) {
            // A switch statement conditionally runs different
            // code depending on the value it is given.
            // Here we check the type of event that happened,
            // and do something different depending on what type of
            // event it was.
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }

        std::cout << "AXIS 0 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_LEFTX)/3276.7f) << '\n';
        std::cout << "AXIS 1 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_LEFTY)/3276.7f)  << '\n';
        std::cout << "AXIS 2 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_RIGHTX)/3276.7f)  << '\n';
        std::cout << "AXIS 3 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_RIGHTY)/3276.7f)  << '\n';
        std::cout << "AXIS 4 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_TRIGGERLEFT)/3276.7f)  << '\n';
        std::cout << "AXIS 5 " << (int) (SDL_GameControllerGetAxis(a, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/3276.7f)  << '\n';

        SDL_Delay(200);
    }

    // Free up any resources that SDL allocated.
    SDL_Quit();
    return 0;
}