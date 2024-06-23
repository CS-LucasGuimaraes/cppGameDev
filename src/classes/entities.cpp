//    Copyright 2024 Lucas Guimarães Fernandes
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include "classes/entities.hpp"

namespace cppGameDev {

// public:

PhysicsEntities::PhysicsEntities(std::string e_type, SDL_Rect initial_rect,
                                 SDL_Rect hitbox, std::string ID,
                                 Tilemap* tilemap) {
    this->type = e_type;
    this->entityRect = initial_rect;
    this->pos.x = this->entityRect.x;
    this->pos.y = this->entityRect.y;
    this->hitbox = this->hitbox_mod = hitbox;
    this->ID = ID;
    this->tilemap = tilemap;
    this->side = this->setted_side = "down";
    this->current_speed = 2;

    this->set_action("idle");

    this->defCollisions();
}

PhysicsEntities::~PhysicsEntities() {
    std::clog << "PhysicsEntities class (" << this->type << ':' << this->ID
              << ") successfully destroyed!\n";
}

void PhysicsEntities::update(Cord4d movement) {
    this->reset_collisions();
    this->movement_and_collide(movement);
    this->facing_side(movement);
    this->animation->update();
    this->ControlActions(movement);
}

void PhysicsEntities::render() {
        
    if (kFlags & SHOW_HITBOXES)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
    SDL_RenderFillRect(renderer, &this->hitbox);
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);

    SDL_RenderCopy(renderer, this->animation->img(), NULL, &this->entityRect);
}

// private:

void PhysicsEntities::set_action(std::string action) {
    if (action != this->action || this->setted_side != this->side) {
        this->action = action;
        this->setted_side = this->side;
        this->animation = assets::animations[this->type + this->ID + '/' +
                                             this->side + '/' + this->action];

        for (auto img : *this->animation->img_list()) {
            SDL_SetTextureColorMod(img, this->color_mod.r, this->color_mod.g,
                                   this->color_mod.b);
        }
    }
}

void PhysicsEntities::reset_collisions() {
    this->collisions = {false, false, false, false};
}

Speed PhysicsEntities::getFrameMovement(Cord4d movement) {
    Speed frame_movement = {
        (movement.r - movement.l) * (double)(this->current_speed),
        (movement.d - movement.u) * (double)(this->current_speed)};

    if ((movement.r - movement.l) && (movement.d - movement.u)) {
        frame_movement.x /= 1.41421356;
        frame_movement.y /= 1.41421356;
    }

    return frame_movement;
}

void PhysicsEntities::movement_and_collide(Cord4d movement) {
    Speed frame_movement = getFrameMovement(movement);

    this->entityRect.x = this->pos.x += frame_movement.x;
    this->updateHitboxX();

    for (tile* tile : this->tilemap->tiles_around(this->getPos())) {
        SDL_Rect tile_rect = {tile->pos.x * this->tilemap->tile_size,
                              tile->pos.y * this->tilemap->tile_size,
                              tilemap->tile_size, tilemap->tile_size};

        this->collide[tile->category + "X"](frame_movement, &tile_rect);
    }

    this->entityRect.y = this->pos.y += frame_movement.y;
    this->updateHitboxY();

    for (tile* tile : this->tilemap->tiles_around(this->getPos())) {
        SDL_Rect tile_rect = {tile->pos.x * this->tilemap->tile_size,
                              tile->pos.y * this->tilemap->tile_size,
                              tilemap->tile_size, tilemap->tile_size};

        this->collide[tile->category + "Y"](frame_movement, &tile_rect);
    }
}

void PhysicsEntities::facing_side(Cord4d movement) {
    if (this->side == "left" || this->side == "right") {
        if (movement.r - movement.l < 0) {
            this->side = "left";
        } else if (movement.r - movement.l > 0) {
            this->side = "right";
        } else if (movement.d - movement.u < 0) {
            this->side = "up";
        } else if (movement.d - movement.u > 0) {
            this->side = "down";
        }
    } else if (this->side == "up" || this->side == "down") {
        if (movement.d - movement.u < 0) {
            this->side = "up";
        } else if (movement.d - movement.u > 0) {
            this->side = "down";
        } else if (movement.r - movement.l < 0) {
            this->side = "left";
        } else if (movement.r - movement.l > 0) {
            this->side = "right";
        }
    }
}

Cord PhysicsEntities::getPos() { return {this->hitbox.x, this->hitbox.y}; }

void PhysicsEntities::defCollisions() {
    this->collide = {
        {"PhysicalX",
         [this](Speed movement, SDL_Rect* tile_rect) {
             if (CollideRect(&this->hitbox, tile_rect)) {
                 if (movement.x > 0) {
                     this->collisions.right = true;
                     this->hitbox.x = tile_rect->x - this->hitbox.w;
                 } else if (movement.x < 0) {
                     this->collisions.left = true;
                     this->hitbox.x = tile_rect->x + tile_rect->w;
                 }
                 this->pos.x = this->hitbox.x - this->hitbox_mod.x;
             }
         }
        },

        {"PhysicalY",
         [this](Speed movement, SDL_Rect* tile_rect) {
             if (CollideRect(&this->hitbox, tile_rect)) {
                 if (movement.y > 0) {
                     this->collisions.down = true;
                     this->hitbox.y = tile_rect->y - this->hitbox.h;
                 } else if (movement.y < 0) {
                     this->collisions.up = true;
                     this->hitbox.y = tile_rect->y + tile_rect->h;
                 }
                 this->pos.y = this->hitbox.y - this->hitbox_mod.y;
             }
         }
        }

    };
}

void PhysicsEntities::ControlActions(Cord4d movement) {
    if (movement.d - movement.u != 0 || movement.r - movement.l != 0) {
        this->set_action("run");
    } else {
        this->set_action("idle");
    }
}

void PhysicsEntities::updateHitbox() {
    this->hitbox = {this->entityRect.x + this->hitbox_mod.x,
                    this->entityRect.y + this->hitbox_mod.y, this->hitbox_mod.w,
                    this->hitbox_mod.h};
}

void PhysicsEntities::updateHitboxX() {
    this->hitbox.x = this->entityRect.x + this->hitbox_mod.x;
}

void PhysicsEntities::updateHitboxY() {
    this->hitbox.y = this->entityRect.y + this->hitbox_mod.y;
}

// public

Player::Player(SDL_Rect initial_rect, SDL_Rect hitbox, std::string ID,
               Tilemap* tilemap)
    : PhysicsEntities("player", initial_rect, hitbox, ID, tilemap) {
    ;
}

Player::~Player() { ; }

// private

void Player::update(Cord4d movement) { PhysicsEntities::update(movement); }

}  // namespace cppGameDev