#ifndef entities_hpp
#define entities_hpp

#include "../engine.hpp"
#include "imageHandle.hpp"
#include "../assets.hpp"
#include "animation.hpp"

class PhysicsEntities {

public:
    PhysicsEntities(std::string e_type, int initial_pos[2], int initial_size[2], std::string ID) { init(e_type, initial_pos, initial_size, ID); }
    ~PhysicsEntities() {};

    /**
     * Updates the physics entity's internal state.
     *
     * This function updates all the physics entity's state and logic.
     * 
     * @returns (void): This function does not return a value.
     */
    void update();

    /**
     *  Render the entity's animation onto the display surface.
     *
     * \returns (void): This function does not return a value.
     */ 
    void render();

    /**
     * Sets the action of the physics entity. 
     *
     * This function updates the action of the physics entity and assigns the corresponding animation.
     * 
     * @param action (std::string): The new action to be set for the physics entity.
     *
     * @returns (void): This function does not return a value.
     */
    void set_action(std::string action);



private:

    /**
     * Initializes a physics entity.
     *
     * This function initializes a physics entity with the provided properties.
     * 
     * @param e_type (std::string): The type of the physics entity.
     * @param initial_pos (int[2]): An array containing the initial x and y position of the entity.
     * @param initial_size (int[2]): An array containing the initial width and height of the entity.
     * @param ID (std::string): A unique identifier for the entity.
     *
     * @returns (void): This function does not return a value.
     */
    void init(std::string e_type, int initial_pos[2], int initial_size[2], std::string ID);

    std::string type;
    int* pos;
    int* size;
    std::string ID;
    std::string action;
    int velocity[2];
    Animation *animation;
    SDL_Rect entityRect;

}; 

#endif