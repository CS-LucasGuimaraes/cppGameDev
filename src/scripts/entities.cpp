#include "entities.hpp"

void PhysicsEntities::init(std::string e_type, int initial_pos[2], int initial_size[2], std::string ID) {
    this->type = e_type;
    this->pos = initial_pos;
    this->size = initial_size;
    this->ID = ID;
    this->action = "";
    this->velocity[0] = 1; this->velocity[1] = 1;


    this->set_action("idle");
}

void PhysicsEntities::set_action(std::string action) {
    if (action != this->action) {
        this->action = action;
        this->animation = animationAssets[this->type + this->ID + '/' + this->action];
    }
}

void PhysicsEntities::update() {
    
    this->entityRect.h = this->size[0]*10;
    this->entityRect.w = this->size[1]*10;
    this->entityRect.x = 100;
    this->entityRect.y = 100;
    this->animation->update();
}

void PhysicsEntities::render() {
    SDL_RenderCopy(display, this->animation->img(), NULL, &this->entityRect);
}