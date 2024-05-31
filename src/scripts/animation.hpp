#ifndef animation_hpp
#define animation_hpp

#include "../engine.hpp"

class Animation {

public:
    Animation(const std::vector<__SDL_Texture> imgs, int img_dur=5, bool loop=true) { 
        this->images = imgs;
        this->img_duration = img_dur;
        this->is_looping = loop;
        this->done = false;
        this->frame = 0;
    }
    ~Animation() {};

    /**
     * Updates the animation frame.
     *
     * \returns (void): This function does not return a value.
     *
     */
    void update();

    /**
     * Get the image that represents the current frame.
     *
     * \returns (__SDL_Texture *):
     * The image that represents the frame.
     *
     */
    __SDL_Texture img();


private:
    std::vector<__SDL_Texture> images;
    int img_duration;
    bool is_looping;
    bool done;
    int frame;
}; 

#endif