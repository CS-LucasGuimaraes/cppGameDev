#ifndef game_hpp
#define game_hpp

#include "engine.hpp"
#include "scripts/imageHandle.hpp"
#include "scripts/entities.hpp"

class Game {

public:
    Game(const char* title, int xpos, int ypos, int widht, int height, bool fullscreen) { init(title, xpos, ypos, widht, height, fullscreen); }
    ~Game();


    /**
     * Processes user input events in the game loop.
     * 
     * \returns (bool):
     * true if the game should continue running.
     * false if the game should exit.
    */
    bool handleEvents();

    /**
     * Updates the game state and logic.
     *
     * \returns (void): This function does not return a value.
     */
    void update();

    /**
     * Renders the game state to the screen.
     *
     * \returns (void): This function does not return a value.
     */ 
    void render();

    /**
     * Deallocates resources and shuts down the game.
     *
     * \returns (void): This function does not return a value.
     */ 
    void clean();

    /**
     * Checks if the game is currently running.
     * \returns (bool):
     *  true if the game is running.
     *  false if the game has quit.
    */
    bool running() { return this->isRunning; }

private:

    /**
     * Initializes the game window, renderer, and sets up basic properties.
     * 
     * \param title (const char*): The title of the game window.
     * \param xpos (int): The x-position of the window on the screen.
     * \param ypos (int): The y-position of the window on the screen.
     * \param widht (int): The width of the game window in pixels.
     * \param height (int): The height of the game window in pixels.
     * \param fullscreen (bool): Whether to run the game in fullscreen mode.
     * \returns (void): This function does not return a value.  
    */
    void init(const char* title, int xpos, int ypos, int widht, int height, bool fullscreen);

    bool isRunning = true;
    int screen_size[2];
    PhysicsEntities* player;
};

#endif