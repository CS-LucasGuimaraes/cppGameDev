// Copyright (C) 2024 Lucas Guimarães
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "classes/entities.hpp"

namespace cppGameDev {

// public:

PhysicsEntities::PhysicsEntities(std::string e_type, SDL_Rect initial_rect,
                                 std::string ID, Tilemap* tilemap) {
    this->type = e_type;
    this->entityRect = initial_rect;
    this->pos.x = this->entityRect.x;
    this->pos.y = this->entityRect.y;
    this->ID = ID;
    this->tilemap = tilemap;

    this->set_action("idle");

    this->collide["PhysicalX"] =
        std::bind(&PhysicsEntities::physics_tiles_collisions_X, this,
                  std::placeholders::_1, std::placeholders::_2);

    this->collide["PhysicalY"] =
        std::bind(&PhysicsEntities::physics_tiles_collisions_Y, this,
                  std::placeholders::_1, std::placeholders::_2);
}

PhysicsEntities::~PhysicsEntities() {
    std::clog << "PhysicsEntities class (" << this->type << ':' << this->ID
              << ") successfully destroyed!\n";
}

void PhysicsEntities::update(int movement) {
    this->reset_collisions();
    this->movement_and_collide(movement);
    this->movement_physics();
    this->facing_side(movement);
    this->animation->update();
}

void PhysicsEntities::render() {
    if (this->flip)
        SDL_RenderCopyEx(renderer, this->animation->img(), NULL,
                         &this->entityRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(renderer, this->animation->img(), NULL,
                       &this->entityRect);
}

// private:

void PhysicsEntities::set_action(std::string action) {
    if (action != this->action) {
        this->action = action;
        this->animation =
            assets::animations[this->type + this->ID + '/' + this->action];

        for (auto img : *this->animation->img_list()) {
            SDL_SetTextureColorMod(img, this->color_mod.r, this->color_mod.g,
                                   this->color_mod.b);
        }
    }
}

void PhysicsEntities::reset_collisions() {
    this->collisions = {false, false, false, false};
}

void PhysicsEntities::movement_and_collide(int movement) {
    Speed frame_movement = {movement + this->speed.x, this->speed.y};

    this->pos.x += frame_movement.x;
    this->entityRect.x = this->pos.x;

    for (tile* tile : this->tilemap->tiles_around(this->getPos())) {
        SDL_Rect tile_rect = {tile->pos.x * this->tilemap->tile_size,
                              tile->pos.y * this->tilemap->tile_size,
                              tilemap->tile_size, tilemap->tile_size};

        this->collide[tile->category + "X"](frame_movement, &tile_rect);
    }
    
    this->pos.y += frame_movement.y;
    this->entityRect.y = this->pos.y;

    for (tile* tile : this->tilemap->tiles_around(this->getPos())) {
        SDL_Rect tile_rect = {tile->pos.x * this->tilemap->tile_size,
                              tile->pos.y * this->tilemap->tile_size,
                              tilemap->tile_size, tilemap->tile_size};

        this->collide[tile->category + "Y"](frame_movement, &tile_rect);
    }
}

void PhysicsEntities::movement_physics() {
    this->speed.y = std::min(5.0, this->speed.y + 0.1);  // Gravity

    if (this->speed.x > 0) {
        this->speed.x = std::max(this->speed.x - 0.1, 0.0);  // Right slowdown
    } else if (this->speed.x < 0) {
        this->speed.x = std::min(this->speed.x + 0.1, 0.0);  // Left slowdown
    }

    if (this->collisions.down || this->collisions.up) {
        this->speed.y = 0;
    }
}

void PhysicsEntities::facing_side(int movement) {
    if (movement + this->speed.x > 0) {
        this->flip = false;
    } else if (movement + this->speed.x < 0) {
        this->flip = true;
    }
}

Cord PhysicsEntities::getPos() {
    return {this->entityRect.x, this->entityRect.y};
}

void PhysicsEntities::physics_tiles_collisions_X(Speed movement,
                                                 SDL_Rect* tile_rect) {
    if (CollideRect(&this->entityRect, tile_rect)) {
        if (movement.x > 0) {
            this->collisions.right = true;
            this->entityRect.x = tile_rect->x - this->entityRect.w;
        } else if (movement.x < 0) {
            this->collisions.left = true;
            this->entityRect.x = tile_rect->x + tile_rect->w;
        }
        this->pos.x = this->entityRect.x;
    }
}

void PhysicsEntities::physics_tiles_collisions_Y(Speed movement,
                                                 SDL_Rect* tile_rect) {
    if (CollideRect(&this->entityRect, tile_rect)) {
        if (movement.y > 0) {
            this->collisions.down = true;
            this->entityRect.y = tile_rect->y - this->entityRect.h;
        } else if (movement.y < 0) {
            this->collisions.up = true;
            this->entityRect.y = tile_rect->y + tile_rect->h;
        }

        this->pos.y = this->entityRect.y;
    }
}

}  // namespace cppGameDev