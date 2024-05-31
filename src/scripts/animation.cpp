#include "animation.hpp"

void Animation::update() {
    
    if (this->is_looping) {
        this->frame = (this->frame + 1) % (this->img_duration *  this->images.size());
    }
    else {
        this->frame = std::min(int(this->frame + 1), int(this->img_duration * this->images.size()-1));
        if (this->frame >= int(this->img_duration * this->images.size()-1)){
            this->done = true;
        }
    }
}

__SDL_Texture Animation::img() {
     return this->images[size_t(this->frame / this->img_duration)];
}